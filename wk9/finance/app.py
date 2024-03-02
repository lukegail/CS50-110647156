import os

from cs50 import SQL
from decimal import Decimal
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
# configures Jinja with a custom “filter,” usd, a function (defined in helpers.py)
# that will make it easier to format values as US dollars (USD).
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
# configures Flask to store sessions on the local filesystem (i.e., disk)
# as opposed to storing them inside of (digitally signed) cookies, which is Flask’s default.
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


# disables caching of responses (provided you’re in debugging mode, default in code50 codespace),
# lest you make a change to some file but your browser doesn't notice
@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


""" displays user name and cash balance below the navbar on every page (see layout.html)
Context Processor: Automatically make a dict available in the context of all templates in a Flask app"""
@app.context_processor
def inject_user_details():
    if "user_id" in session:
        username = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])[0]['username']
        cash = usd(db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"])
        return dict(username=username, cash=cash)
    else:
        # Return an empty dictionary or default values when the user is not logged in
        return dict(username=None, cash=None)


""" displays an HTML table summarizing portfolio

1. for the user currently logged in, display:
    a. which stocks the user owns,
    b. the numbers of shares owned,
    c. the current price of each stock,
    d. the total value of each holding (i.e., shares times price).
    e. Also display the user’s current cash balance along with a grand total (i.e., stocks’ total value plus cash).
2. Odds are you’ll want to execute multiple SELECTs. Depending on how you implement your table(s),
    you might find GROUP BY HAVING SUM and/or WHERE of interest.
3. Odds are you’ll want to call lookup for each stock.
"""
@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    account_total = 0

    # Retrieve portfolio data for the current user, including the number of shares (sum of quantities of each stock held)
    portfolio = db.execute("SELECT symbol, SUM(quantity) as total_quantity FROM trades WHERE user_id = ? GROUP BY symbol HAVING SUM(quantity) > 0 ORDER BY symbol", session["user_id"])

    # For each holding in the portfolio (which is a list of dicts, each dict represents a holding)
    for stock in portfolio:
        # Add 'current_price' key with value from 'lookup' to each stock/holding dict. ('lookup' function returns a dict.)
        stock["current_price"] = lookup(stock["symbol"])["price"]
        # Add 'total_value' key with calculated value
        stock["total_value"] = stock["total_quantity"] * stock["current_price"]
        # increment account_total with the total value of each holding
        account_total += stock["total_value"]

        # format to usd
        stock["current_price"] = usd(stock["current_price"])
        stock["total_value"] = usd(stock["total_value"])

    # Execute SQL query to get cash column for current user,
    # then directly access the cash value from the first row's dictionary
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    # update account_total by adding user's cash
    account_total += cash

    return render_template("index.html", portfolio=portfolio, cash=usd(cash), account_total=usd(account_total))


""" enables a user to buy stocks.

1. Require that a user input a stock’s symbol, implemented as a text field whose name is symbol.
    Render an apology if the input is blank or the symbol does not exist (as per the return value of lookup).
2. Require that a user input a number of shares, implemented as a text field whose name is shares.
    Render an apology if the input is not a positive integer.
3. Submit the user’s input via POST to /buy.
4. Upon completion, redirect the user to the home page.
5. Odds are you’ll want to call lookup to look up a stock’s current price.
6. Odds are you’ll want to SELECT how much cash the user currently has in users.
7. Add one or more new tables to finance.db via which to keep track of the purchase.
    Store enough information so that you know who bought what at what price and when.
    a. Use appropriate SQLite types.
    b. Define UNIQUE indexes on any fields that should be unique.
    c. Define (non-UNIQUE) indexes on any fields via which you will search (as via SELECT with WHERE).
8. Render an apology, without completing a purchase, if the user cannot afford the number of shares at the current price.
9. You don’t need to worry about race conditions (or use transactions).

Once you’ve implemented buy correctly, you should be able to see users’ purchases in
    your new table(s) via phpLiteAdmin or sqlite3.
"""
@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        # fetch and validate symbol
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide symbol", 400)
        symbol = symbol.upper()

        # fetch and validate shares
        shares = request.form.get("shares")
        if not shares:
            return apology("must specify shares", 400)
        if not shares.isdigit() or int(shares) <= 0:
            return apology("must specify a positive number of shares", 400)
        shares = int(shares)

        # lookup current quote info (dict) for symbol
        quote_info = lookup(symbol)

        # apology if a lookup error occurs or the symbol is invalid (lookup will return None)
        if not quote_info:
            return apology("stock lookup error", 400)

        # covert price to Decimal
        price = Decimal(quote_info["price"])

        # Execute SQL query to get cash column for current user,
        # then directly access the cash value from the first row's dictionary
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        cash = Decimal(cash)

        # calculate cost of transaction and compare with user's cash
        buy_price = price * shares
        if buy_price > cash:
            return apology("you're too poor for that", 403)

        # insert transaction details into the db in the "trades" table. (convert price to str to avoid cs50 .execute error)
        db.execute("INSERT INTO trades (user_id, symbol, quantity, price_per_share, type) VALUES(?, ?, ?, ?, ?)", session['user_id'], symbol, shares, str(price), 'BUY')

        # calculate new cash balance and update "users" table. (convert balance to str to avoid cs50 .execute error)
        balance = cash - buy_price
        db.execute("UPDATE users SET cash = ? WHERE id = ?", str(balance), session["user_id"])

        return redirect("/")

    else:
        return render_template("buy.html")


""" displays an HTML table summarizing all of a user’s transactions ever,
listing row by row each and every buy and every sell.

1. For each row, make clear
    a. whether a stock was bought or sold and include the stock’s symbol,
    b. the (purchase or sale) price,
    c. the number of shares bought or sold,
    d. the date and time at which the transaction occurred.
2. You might need to alter the table you created for buy or supplement it with an additional table.
    Try to minimize redundancies.
"""
@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    trades = db.execute("SELECT * FROM trades WHERE user_id = ? ORDER BY transaction_time", session["user_id"])
    for trade in trades:
        trade["price_per_share"] = usd(trade["price_per_share"])
        trade["current_price"] = usd(lookup(trade["symbol"])["price"])
    return render_template("history.html", trades=trades)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        # uses check_password_hash to compare hashes of users’ passwords
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        # login “remembers” that a user is logged in by storing his or her user_id, an INTEGER, in session.
        # That way, any of this file’s routes can check which user, if any, is logged in.
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        # once the user has successfully logged in, login will redirect to "/",
        # taking the user to their home page.
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


""" allows a user to look up a stock’s current price.

1. Require that a user input a stock’s symbol, implemented as a text field whose name is symbol.
2. Submit the user’s input via POST to /quote.
3. Odds are you’ll want to create two new templates (e.g., quote.html and quoted.html).
    When a user visits /quote via GET, render one of those templates, inside of which should be an HTML form that
    submits to /quote via POST. In response to a POST, quote can render that second template,
    embedding within it one or more values from lookup.
"""
@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":
        # get username and password from registration form
        symbol = request.form.get("symbol").upper()

        # Ensure username was submitted
        if not symbol:
            return apology("must provide symbol", 400)

        # get quote info (dict) for symbol,
        quote_info = lookup(symbol)

        # apology if a lookup error occurs or the symbol is invalid (lookup will return None)
        if not quote_info:
            return apology("stock quote error", 400)

        # formats latest stock price as $usd.00
        price = usd(quote_info["price"])

        return render_template("quoted.html", symbol=symbol, price=price)
    else:
        return render_template("quote.html")


""" allows a user to register for an account via a form.

1. Require that a user input a username, implemented as a text field whose name is username.
    Render an apology if the user’s input is blank or the username already exists.
2. Require that a user input a password, implemented as a text field whose name is password,
    and then that same password again, implemented as a text field whose name is confirmation.
    Render an apology if either input is blank or the passwords do not match.
3. Submit the user’s input via POST to /register.
4. INSERT the new user into users, storing a hash of the user’s password, not the password itself.
    Hash the user’s password with generate_password_hash Odds are you’ll want to create
    a new template (e.g., register.html) that’s quite similar to login.html.

Once you’ve implemented register correctly, you should be able to register for an account
    and log in (since login and logout already work)! And you should be able to see your rows via phpLiteAdmin or sqlite3.
"""
@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        # get username and password from registration form
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Ensure username was submitted
        if not username:
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not password:
            return apology("must provide password", 400)

        # Ensure valid password confirmation
        elif confirmation != password:
            return apology("password confirmation failed", 400)

        # Query database for username
        matches = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        if len(matches) != 0:
            return apology("username already exists", 400)

        # hashes (encrypts) the password
        password_hash = generate_password_hash(password, method='scrypt', salt_length=16)

        # inserts the new user's data into the users table in your database
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, password_hash)

        # Retrieves and sets the session's user ID to the ID of the most recently inserted user in the database
        session["user_id"] = db.execute("SELECT last_insert_rowid()")[0]["last_insert_rowid()"]

        return redirect("/")
    else:
        return render_template("register.html")


""" enables a user to sell shares of a stock (that he or she owns).

1. Require that a user input a stock’s symbol, implemented as a select menu whose name is symbol.
    Render an apology if the user fails to select a stock or if (somehow, once submitted)
    the user does not own any shares of that stock.
2. Require that a user input a number of shares, implemented as a text field whose name is shares.
    Render an apology if the input is not a positive integer or if the user does not own that many shares of the stock.
3. Submit the user’s input via POST to /sell.
4. Upon completion, redirect the user to the home page.
5. You don’t need to worry about race conditions (or use transactions).
"""
@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # Retrieve portfolio data for the current user, including the number of shares (sum of quantities of each stock held)
    portfolio = db.execute("SELECT symbol, SUM(quantity) as total_quantity FROM trades WHERE user_id = ? GROUP BY symbol HAVING SUM(quantity) > 0 ORDER BY symbol", session["user_id"])

    if request.method == "POST":

        # fetch and validate symbol
        symbol = request.form.get("symbol")
        portfolio_symbols = {stock['symbol'] for stock in portfolio}
        if not symbol or symbol not in portfolio_symbols:
            return apology("must provide symbol of stock you own", 400)
        symbol = symbol.upper()

        # fetch and validate shares
        shares = request.form.get("shares")
        # Create a dictionary of symbols and their total quantities, so the last conditional below works to check sale against quantity of shares in portfolio
        portfolio_dict = {stock['symbol']: stock['total_quantity'] for stock in portfolio}
        if not shares or not shares.isdigit() or int(shares) <= 0 or int(shares) > portfolio_dict[symbol]:
            return apology("must specify a positive number of shares that you own", 400)
        shares = int(shares)

        # handle trade
        current_price = lookup(symbol)["price"]
        db.execute("INSERT INTO trades (user_id, symbol, quantity, price_per_share, type) VALUES(?, ?, -?, ?, ?)", session['user_id'], symbol, shares, current_price, 'SELL')

        # update user's cash
        sale_cash = shares * lookup(symbol)['price']
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", sale_cash, session['user_id'])

        return redirect("/")

    else:
        return render_template("sell.html", portfolio=portfolio)
