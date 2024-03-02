"""
This program is designed to identify a person based on their DNA profile.
It takes two command-line arguments:
    argv[1]: a CSV file containing a list of individuals and their DNA sequences for a set of specific Short Tandem Repeats (STRs), and
    argv[2]: a text file containing an unknown DNA sequence.
The program will analyze the unknown DNA to count the longest consecutive sequence of each STR.
It then compares this information against the database to determine whose DNA sequence is a match.
If a match is found, the program will print the name of the matching individual. If no match is found, it will print "No match."

Usage:
python dna.py DNA_DATABASE.csv DNA_SEQUENCE.txt
"""

import csv
import sys


def main():
    # Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py DNA_DATABASE.csv DNA_SEQUENCE.txt")

    # Read database file into a variable
    # Open a handle to the database file for reading
    with open(sys.argv[1]) as database_file:
        # Create a DictReader object for reading rows into dictionaries
        reader = csv.DictReader(database_file)

        # Convert the DictReader object to a list of dictionaries, storing data in memory
        db_sequences = list(reader)

    # from csv file's first line (name,AGATC,AATG,TATC)(but exluding 'name'), make a list of subsequences
    subsequences = list(db_sequences[0].keys())[1:]

    # Read DNA sequence file into a string variable ('AAGGAGATCAGATCA...")
    with open(sys.argv[2], "r") as sequence_file:
        sequence = sequence_file.read()

    # Find longest match of each STR in DNA sequence
    subseq_counts = {}
    for subsequence in subsequences:
        subseq_counts[subsequence] = longest_match(sequence, subsequence)

    # Check database for matching profiles
    # Loop through each person's DNA sequences in the database
    for person in db_sequences:
        # Reset the match flag to True for each new person
        match = True

        # Loop through each subsequence in the user's DNA sequence
        for subseq in subseq_counts:
            # see counts for debugging: print(f"{person['name']}: subseq_counts[subseq] is {subseq_counts[subseq]}, person[subseq] is {person[subseq]}") ###########

            # Compare a single subsequence count for this person in the database to the same subsequence count for user's unknown DNA
            # Cast person's subsequence count to int for accurate comparison
            if subseq_counts[subseq] == int(person[subseq]):
                # If there is a match, do nothing and move to the next subsequence
                pass
            else:
                # If any subsequence doesn't match, set the match flag to False
                match = False
                # Break the loop as there's no point in checking the rest of the subsequences
                break

        # If all subsequences for this person match the user's DNA, print the person's name and break the loop
        if match == True:
            print(f"{person['name']}")
            break

    # If loop finishes and no match is found, print "No match"
    if match == False:
        print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
