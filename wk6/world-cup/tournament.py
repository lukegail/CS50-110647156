# Simulate a sports tournament
"""
This script simulates a series of sports tournaments based on team ratings.
It takes a CSV file as input where each row represents a team and contains at least the team name and rating.
The number of simulations is set by the variable 'N'.
The script prints out the probability of each team winning the tournament, based on N simulations.

To run the script, use the following command:
    python tournament.py FILENAME

Where FILENAME is the name of the CSV file containing team information.
"""

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():
    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    # Open the file and read the teams into a list of dictionaries
    # Use 'with' statement to open file, ensuring it gets closed after reading
    with open(sys.argv[1]) as file:
        # Create a DictReader object for reading CSV to dictionaries
        reader = csv.DictReader(file)

        # Convert the CSV reader object to a list of dictionaries
        teams = list(reader)

    # Convert the 'rating' field from string to integer for each team
    for team in teams:
        team["rating"] = int(team["rating"])

    # Dictionary to keep track of each team's win count
    counts = {}

    # Simulate N tournaments
    for i in range(N):
        winner = simulate_tournament(teams)
        # If the team has not won before, initialize its count to 1
        if winner not in counts:
            counts[winner] = 1
        # Otherwise, increment the team's win count
        else:
            counts[winner] += 1

    # Sort teams by win count and print their winning probabilities
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    # Keep simulating rounds until only one team remains
    while True:
        # Simulate a single round and get the list of winners
        teams = simulate_round(teams)
        # If only one team is left, the tournament is over. return the team
        if len(teams) == 1:
            return teams[0]["team"]


if __name__ == "__main__":
    main()
