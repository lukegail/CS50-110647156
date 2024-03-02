# https://cs50.harvard.edu/x/2023/problems/6/seven-day-average/

import csv
import requests


def main():
    # Read NYTimes Covid Database
    # Use the requests library's get method to fetch data from a URL and store the HTTP response in the 'download' variable.
    # 'download' is an HTTP Response object that contains the server's response to our request.
    # The 'content' attribute of this object holds the raw byte content of the response.
    ##### 'download' is the raw byte data
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )

    # Fetch raw byte content of the CSV file from the server and store it in 'download.content'.
    # Decode the bytes of the entire CSV file into a single, long UTF-8 text string called 'decoded_content'.
    ##### 'decoded_content' is a single string of text
    decoded_content = download.content.decode("utf-8")

    # We split this string into a list ('file') of strings, each representing a single line/row in the CSV.
    ##### 'file' is a list of strings (rows)
    file = decoded_content.splitlines()

    # csv.DictReader reads lines from 'file' and converts each line to a dictionary.
    # The keys for the dictionary come from the header row of the CSV.
    ##### 'reader' is an iterator of dictionaries (one per row)
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    ##### 'new_cases' is a dictionary of states and their 14 days of cases. Vermont: [5, 10, 12, ...]
    new_cases = calculate(reader)

    # Initialize an empty list to store states selected by the user
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    # Input loop for states
    while True:
        # Prompt the user for a state name.
        state = input("State: ").capitalize()

        # Check if the entered 'state' exists in the 'new_cases' dictionary.
        # If it does, add it to the 'states' list.
        if state in new_cases:
            states.append(state)

        # If the user hits Enter without providing a state name (i.e., 'state' is an empty string),
        # break out of the loop.
        if len(state) == 0:
            break

    # Output a header for the 7-day averages section.
    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
# new_cases is a dict, key is state, value is a list of 14 cases
def calculate(reader):

    new_cases = {}
    previous_cases = {}

    for row in reader:
        state = row['state']
        cases = int(row['cases'])
        if state not in new_cases:
            new_cases[state] = []
            previous_cases[state] = cases
        else:
            daily_new_cases = cases - previous_cases[state]
            new_cases[state].append(daily_new_cases)
            previous_cases[state] = cases

        if len(new_cases[state]) > 14:
            new_cases[state].pop(0)

    return new_cases


# TODO: Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):
    # loop through states specified
    for state in states:
        # 7-day average
        current_ave = sum(new_cases[state][-7:]) // 7  # sum up the LAST 7 elements in the list for the selected state, then divide this by 7. '//' is integer division, giving an integer
        previous_ave = sum(new_cases[state][0:7]) // 7  # sum up the FIRST 7 elements in the list for the selected state, then divide this by 7

        # calulate percent change
        # code under this keyword will be executed, and if any exceptions arise (in this case, a ZeroDivisionError), the code under except will run.
        try:
            percent_change = int(((current_ave - previous_ave) / previous_ave) * 100)
            if percent_change > 0:
                pos_v_neg = "an increase of"
            elif percent_change < 0:
                pos_v_neg = "a decrease of"
            else:
                pos_v_neg = "a change of"
            percent_change = abs(percent_change)
        except ZeroDivisionError:
                pos_v_neg = "following a previous 7-day average of"
                percent_change = previous_ave  # should always be 0 here

        print(f"{state} had a 7-day average of {current_ave}, {pos_v_neg} {percent_change}%.")


main()
