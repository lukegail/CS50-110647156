'''The program prompts for change owed, converts it to cents,
and minimizes coin count by using integer division '//' to allocate
the largest possible number of higher-value coins first,
updating remaining cents at each step. It sums up the coins to get the least number required.'''

from cs50 import get_float


def get_cents():
    # get from user a non-negative float amount of change owed. convert it to int cents
    while True:
        cents = int(100 * get_float("Change owed: "))
        if cents >= 0:
            return cents


def calculate_quarters(cents):
    # integer division '//' rounds down, ensuring that you get
    # the largest whole number of quarters that can fit into the remaining cents.
    quarters = cents // 25
    return quarters


def calculate_dimes(cents):
    dimes = cents // 10
    return dimes


def calculate_nickles(cents):
    nickles = cents // 5
    return nickles


def calculate_pennies(cents):
    pennies = cents
    return pennies


def main():
    cents = get_cents()

    # Determine the maximum number of quarters that fit into
    # the remaining cents and then update the remaining cents.
    quarters = calculate_quarters(cents)
    cents = cents - quarters * 25

    dimes = calculate_dimes(cents)
    cents = cents - dimes * 10

    nickles = calculate_nickles(cents)
    cents = cents - nickles * 5

    pennies = calculate_pennies(cents)
    cents = cents - pennies * 1

    coins = quarters + dimes + nickles + pennies
    print(f"{coins}")


if __name__ == "__main__":
    main()
