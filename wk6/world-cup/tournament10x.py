"""
Simulate a Sports Tournament - Version 2

This version extends the functionality of the original version to include:
- Timing information to measure the performance of simulations.
- Only printing the top 3 teams instead of all teams.
- The ability to scale the number of simulations to assess impact on timing.

To run the script, use the following command:
    python tournament.py FILENAME

Where FILENAME is the name of the CSV file containing team information.
"""

import csv
import sys
import random
import time  # (Additional import for timing functionality)

# Number of simluations to run
N = 1


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    # Read teams into memory from file
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        teams = list(reader)

    for team in teams:
        team['rating'] = int(team['rating'])

    # (Additional variable to store timing data)
    time_data = []

    # Simulate N tournaments and keep track of win counts
    for j in range(7):

        # (Additional timing-related logic)
        # Start the timer before simulating the tournaments
        start_time = time.time()

        counts = {}
        for i in range(N * (10 ** j)):
            winner = simulate_tournament(teams)
            if winner not in counts:
                counts[winner] = 1
            else:
                counts[winner] += 1

        # Print 3 top team's chances of winning, according to simulation
        sorted_teams = sorted(counts, key=lambda team: counts[team], reverse=True)[:3]
        print(f"At {N * (10 ** j)} simulations: ", end="")
        for team in sorted_teams:
            print(f"{team} - {counts[team] * 100 / (N * (10 ** j)):.1f}%", end=", ")

        # (Additional timing-related logic)
        # Stop the timer. Calculate and print the elapsed time for the simulations
        end_time = time.time()
        elapsed_time = "{:.3f}".format(end_time - start_time)
        print(f"Time elapsed: {elapsed_time} seconds")

        # Store the timing data
        minutes, seconds = divmod(float(elapsed_time), 60)
        time_data.append(f"{N * (10 ** j)} simulations: {int(minutes)}m{seconds:.3f}s")

    # Print the collected timing data
    print("\nTimings:")
    for timing in time_data:
        print(timing)


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
    while True:
        teams = simulate_round(teams)
        if len(teams) == 1:
            return teams[0]['team']


if __name__ == "__main__":
    main()
