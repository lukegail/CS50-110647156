# This script is used to populate the 'assignments' table in 'roster.db'
# with student IDs and corresponding house IDs.
# It reads student data from a CSV file named 'students.csv',
# and maps this data to existing house IDs in the 'houses' table.
# Finally, it inserts these mapped values into the 'assignments' table.

# https://cs50.harvard.edu/x/2023/problems/7/prophecy/


# Import the SQL class from the CS50 library and the csv module
from cs50 import SQL
import csv


# Initialize the database connection to 'roster.db'
# 'db' will be the handle for this database connection
db = SQL("sqlite:///roster.db")

# Read the 'students.csv' file into a list of dictionaries
# Open the file for reading
with open("students.csv", "r") as infile_handle:
    # Use the DictReader class to read each row into a dictionary
    reader = csv.DictReader(infile_handle)

    # Convert the reader object to a list of dictionaries for easier manipulation
    student_roster = list(reader)

# Initialize an empty dictionary to map house names to their IDs
house_dict = {}

# Query the 'houses' table to get the mapping of house names to IDs
houses_rows = db.execute("SELECT id, house FROM houses")

# Populate 'house_dict' using the results of the query
for row in houses_rows:
    house_dict[row['house']] = row['id']

# Loop through the list of student dictionaries to populate the 'assignments' table
for student in student_roster:
    # Get the student ID and house name from the current dictionary
    student_id = student['id']
    house = student['house']

    # Insert a new row into the 'assignments' table with the student ID and corresponding house ID
    db.execute("INSERT INTO assignments (student_id, house_id) VALUES (?, ?)", student_id, house_dict[house])






