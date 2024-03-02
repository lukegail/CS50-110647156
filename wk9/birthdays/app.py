import os
import sqlite3

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():

    # Handle POST requests: including form submissions for adding entries, initiating edit operations (clicking 'edit'), or finalizing edit operations (clicking 'update').
    if request.method == "POST":

        # Get birthday_id and convert it to an integer if it exists
        birthday_id = request.form.get("birthday_id")

        # Check if birthday_id is present in the form. Its presence indicates an edit operation, either initiating an edit (only birthday_id) or submitting updates (birthday_id with other data).
        if birthday_id:
            birthday_id = int(birthday_id)

        # Check if the form submission is for initiating an edit operation (clicking the edit button)
        # if 'name' is NOT in the request form, it prob means the edit button has been clicked (Only the birthday_id is sent to identify which record is to be edited.)
        if 'name' not in request.form:

            # Retrieve the birthday record of the id whose edit button was clicked, and store it in a variable
            birthday_to_edit = db.execute("SELECT * FROM birthdays WHERE id = ?", (birthday_id,))
            # if birthday_to_edit exists (indicating an edit button was clicked)
            if birthday_to_edit:

                # Fetch all birthday records to display on the page
                birthdays = db.execute("SELECT * FROM birthdays")

                # show the table with all the birthdays, plus preload the birthday_to_edit into the form fields for user to edit ([0] indicates that it's actually a list or some other iterable. we only want the one birthday--the first one on the list)
                return render_template("index.html", birthdays=birthdays, birthday_to_edit=birthday_to_edit[0])
            else:

                # if birthday_to_edit does NOT exist (tampering or db error etc occurred), redirect to the main page if the specific record is not found
                return redirect("/")

        # if 'name' IS in the request form, it means the submission was a new birthday or an updated/edited one
        else:
            # Retrieve user-submitted data for adding or editing a birthday record
            name = request.form.get("name")
            month = int(request.form.get("month"))
            day = int(request.form.get("day"))

            # if a birthday_id exists, indicates an existing record is being UPDATED
            if birthday_id:

                # Update an existing record with the user's input
                # Establish a connection to the database. (actually, creates a database connection object--sort of like a pointer with methods--and assigns it to the variable 'conn'.) (the 'with' statement automatically closes the resource when the block is exited, even if an error occurs)
                with sqlite3.connect('birthdays.db') as conn:

                    # Create a cursor object to execute database commands and manage query results
                    cursor = conn.cursor()

                    # Execute an SQL query to update the record directly with parameters
                    cursor.execute("UPDATE birthdays SET name = ?, month = ?, day = ? WHERE id = ?", (name, month, day, birthday_id))

            # if a birthday_id does NOT exist, indicates a new record is being ADDED
            else:

                # Insert a new birthday record into the database
                db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", name, month, day)

        # Redirect to the main page after processing the form submission
        return redirect("/")

    # Handle GET requests: This includes initial page load, page reload/refresh, and redirections back to the main page.
    else:
        # Retrieve all birthday records and display them on the main page
        birthdays = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", birthdays=birthdays)


@app.route('/delete', methods=['POST'])
def delete_birthday():
    birthday_id = request.form.get('birthday_id')

    # Logic to delete the entry from the database using birthday_id
    db.execute("DELETE FROM birthdays WHERE id = ?", (birthday_id,))

    # Redirect back to the main page after deletion
    return redirect('/')
