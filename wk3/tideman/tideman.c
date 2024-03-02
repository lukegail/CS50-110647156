/*Tideman algorithm. go to https://cs50.harvard.edu/x/2023/psets/3/tideman/ */

#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define MAX 9 // Max number of candidates

typedef struct
{
    int winner; // Each pair has a winner and a loser
    int loser;
}
pair;

// Global variables
pair pairs[MAX * (MAX - 1) / 2]; // array of all pairs of candidates
int pair_count; // total number of pairs
string candidates[MAX]; // array of all candidates
int candidate_count; // total number of candidates
int preferences[MAX][MAX]; // preferences[i][j] is number of voters who prefer candidate i over j
bool locked[MAX][MAX]; // locked[i][j] means i is locked in over j

// Function prototypes
bool vote(int rank, string name, int ranks[]); // update ranks given a new vote
void record_preferences(int ranks[]); // Update preferences given one voter's ranks
void add_pairs(void); // Record pairs of candidates where one is preferred over the other
void sort_pairs(void); // Sort pairs in decreasing order by strength of victory
void lock_pairs(void); // Lock pairs into the candidate graph in order, without creating cycles
bool detect_cycle(int c, pair chain[], bool checked_pairs[], int i, pair temp_current); // Detect if locking the pair would result in cycle
void print_winner(void); // Print the winner of the election

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes // LOOPS through voters
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank // LOOPS through a voter's 1st, 2nd, 3rd choice, etc
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);
        printf("\n");

    }

    /* for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("preferences[%i][%i]: %i\n", i, j, preferences[i][j]);
        }
    }
    printf("\n"); */

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
/*This function takes a rank and candidate name, then updates the ranks array to reflect the voter's preference.
It uses a loop to go through all the candidates and checks if the given name matches a candidate.
If it does, the function records the vote by assigning the candidate's index in the ranks array at the position corresponding to the rank.
If the name does not match any candidate, the function returns false to signify that the vote could not be recorded.*/
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0) // If the given name matches with a candidate's name
        {
            ranks[rank] = i; // Store the candidate's index in the ranks array at the position of the rank
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
/*The function record_preferences updates the preferences matrix based on each voter's ranked preferences.
It first iterates through all the candidates preferred by a voter.
For each preferred candidate (ranks[i]), it then compares this candidate with all other less-preferred candidates (ranks[j]).
The function then increments the preference count of the more preferred candidate over the less preferred one in the preferences matrix.
This process accumulates all the voters' preferences over multiple rounds of voting.*/
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++) // loops through a voter's prefs, starting with ranks[0]. voter's pref is represented by [i]
    {
        for (int j = i + 1; j < candidate_count; j++) // loops thru comparisons between a voter's pref [i] and her less preferred prefs [j] (ex.: 1st pref vs 2nd pref (i = ranks[0], j = ranks[1]))
        {
            // 2D array has x/y coordinates ranks[i] and ranks[j]
            // every combo of i and j that the above loops cycle through, this increments the value at that spot on the graph/array.
            // with 4 candidates, it will look like this:
            /*
            1st pref vs 2nd pref (i = ranks[0], j = ranks[1]) --> preferences[ranks[0]][ranks[1]] ++
            1st pref vs 3rd pref (i = ranks[0], j = ranks[2]) --> preferences[ranks[0]][ranks[2]] ++
            1st pref vs 4th pref (i = ranks[0], j = ranks[3]) --> preferences[ranks[0]][ranks[3]] ++
            2nd pref vs 3rd pref (i = ranks[1], j = ranks[2]) --> preferences[ranks[1]][ranks[2]] ++
            2nd pref vs 4th pref (i = ranks[1], j = ranks[3]) --> preferences[ranks[1]][ranks[3]] ++
            3rd pref vs 4th pref (i = ranks[2], j = ranks[3]) --> preferences[ranks[2]][ranks[3]] ++
            */
            preferences[ranks[i]][ranks[j]]++; // as main loops through voters, this array will continue to tally all of their preferences.

            //printf("[ranks[%i]][ranks[%i]]: %i\n", ranks[i], ranks[j], preferences[ranks[i]][ranks[j]]);
        }
    }
}

// Record pairs of candidates where one is preferred over the other
// create 'pairs' array, which is a struct of type 'pair'
/*This function add_pairs populates the pairs array with pairs of candidates where one candidate is preferred over the other.
The pairs are represented by their indices in the candidates array.
For each pair of candidates (i,j), if candidate i is preferred over candidate j, then i is recorded as the winner and j as the loser of the pair.
If j is preferred over i, then j is recorded as the winner and i as the loser.
This process is repeated for all pairs of candidates.
The total number of pairs is stored in the global variable pair_count.*/
void add_pairs(void)
{
    int pair_num = 0; // counter for the pairs
    for (int i = 0; i < candidate_count; i++) // iteretates thru each candidate
    {
        for (int j = i + 1; j < candidate_count; j++) // compares each candidate i with other candidates j
        {
            if (preferences[i][j] > preferences[j][i]) // if candididate i is preferred over candidate j...
            {
                pairs[pair_num].winner = i; // Record candidate i as the winner and j as the loser in the pairs array
                pairs[pair_num].loser = j;
                // printf("unsorted Pair %d Winner, Loser = %d, %d\n", pair_num, pairs[pair_num].winner, pairs[pair_num].loser);
                pair_num++; // increment pair counter
            }
            else if (preferences[i][j] < preferences[j][i]) // if j > i...
            {
                pairs[pair_num].winner = j; // record j as winner and i as loser in pairs array
                pairs[pair_num].loser = i;
                // printf("unsorted Pair %d Winner, Loser = %d, %d\n", pair_num, pairs[pair_num].winner, pairs[pair_num].loser);
                pair_num++;
            }
            // if i == j, no pair is created
        }
    }
    // printf("\n");
    pair_count = pair_num; // update the global variable pair_count to be the number of pairs of candidates.
}

// Sort pairs in decreasing order by strength of victory
/*The sort_pairs function sorts the array of pairs in decreasing order of the strength of victory.
The strength of victory for a pair is calculated as the number of voters who prefer the winner over the loser.
This sorting is done using a bubble sort algorithm, which compares each pair with the next and swaps them if the next pair's strength of victory is greater.
The process is repeated until no more swaps are needed, indicating that the array is sorted.*/
void sort_pairs(void)
{
    pair swap; // temporary variable holds values during swaps
    bool swapped; // flags swaps
    do // loop that continues until no swaps are needed (i.e., the array is sorted)
    {
        swapped = false;
        for (int i = 0; i < pair_count - 1; i++)
        {
            int strength = preferences[pairs[i].winner][pairs[i].loser]; // Calculate the strength of victory for the current pair (stength)...
            int strength_next = preferences[pairs[i + 1].winner][pairs[i + 1].loser]; // ...and the next pair (next_strength)

            if (strength < strength_next) // if current pair's strength of victory is less than the next...
            {
                swap = pairs[i + 1]; // ..., swap them...
                pairs[i + 1] = pairs[i];
                pairs[i] = swap;
                swapped = true; // ...and indicate that a swap has occurred
            }
        }
    }
    while (swapped); // If a swap occurred in the last pass, make another pass. ("== true" is assumed.)
    // Debugging prints can be uncommented to verify sorted order
    /*
    for (int i = 0; i < pair_count - 1; i++)
        {
            printf("sorted pairs[%i].winner strength: %i\n", i, preferences[pairs[i].winner][pairs[i].loser]);
        }
        printf("\n");

    for (int i = 0; i < pair_count - 1; i++)
    {
        printf("sorted Pair %d Winner, Loser = %d, %d\n", i, pairs[i].winner, pairs[i].loser);
    }
    printf("\n");
    */
}

// Lock pairs into the candidate graph in order, without creating cycles
/*This lock_pairs function locks pairs into a directed graph in order, while ensuring that no cycles are formed
(which would represent a circular argument of who is preferred).
The function maintains an array (declare_chain) that stores the sequences of connected pairs being considered,
and a boolean array (declare_checked_pairs) that flags pairs that have already been checked for downstream connections.
If a pair does not create a cycle when added, it is locked in.*/
void lock_pairs(void)
{
	pair declare_chain[pair_count]; // These arrays will store the chains of connected pairs and...
    int declare_chain_index = 0;
	bool declare_checked_pairs[pair_count]; // flags pairs that have been checked for downstream connections

	for (int i = 0; i < pair_count; i++) // i determines which “parent” pair is under investigation
	{
		for(int k = 0; k < pair_count; k++) // Reset checked_pairs and chain arrays at the start of each iteration of checking a pair for cycles
		{
    		declare_chain[k].winner = MAX; // (MAX/9 is invalid value, signifies empty state)
    		declare_chain[k].loser = MAX;
    		declare_checked_pairs[k] = false;
		}

		declare_chain[0] = pairs[i]; // Add the current pairs[i] to the chain and mark it as checked
		declare_checked_pairs[i] = true;

		pair declare_temp_current = pairs[i]; // temp_current is used represent the upstream/source pair in every connection of the chain. it starts as the parent pair.

		if (!detect_cycle(declare_chain_index, declare_chain, declare_checked_pairs, i, declare_temp_current)) //// if current pair doesn't create a cycle...
		{
            locked[pairs[i].winner][pairs[i].loser] = true; // lock it in
		}
	}
    // Uncomment the following block to print out the locked pairs for debugging
    /*
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            printf("locked[%i][%i] = %i\n", i, j, locked[i][j]);
            printf("locked[%i][%i] = %i\n", j, i, locked[j][i]);
        }
    }
    */
}

// Detect if locking the pair would result in cycle
/*The detect_cycle function is a recursive function that is used to detect cycles in the directed graph of locked pairs.
It follows potential chains of pairs in the graph, starting from a given pair.
When it reaches a pair that has already been visited, it has detected a cycle.
If it cannot find any more connections and has investigated all connections of the original pair, a cycle does not exist.
If no connection could be found and we are not back to the original pair, it backtracks by one pair in the chain.
detect_cycle is an implementation of depth-first search.
DFS is a common algorithm for traversing or searching tree or graph data structures.
It uses a stack (in this case, the function call stack due to recursion) to remember to get back to nodes (or "points") at the next level down.*/
bool detect_cycle(int c, pair chain[], bool checked_pairs[], int i, pair temp_current)
{
    while (true) // The loop continues indefinitely until it's broken by one of the return statements
    {
        int j; // variable declared outside the j loop because it's used outside the j loop

        // Look for potential connections among locked pairs that have not been checked yet
        for (j = 0; j < pair_count; j++)
        {
            if (locked[pairs[j].winner][pairs[j].loser] && !checked_pairs[j] && temp_current.loser == pairs[j].winner) // The potential connection is where the loser of the current pair is the winner of another pair
            {
                // If such a pair is found...
                checked_pairs[j] = true; // pair is flagged as ‘checked’
                c++; // next link in chain now waiting to be assigned
                chain[c] = pairs[j]; // add it to the chain (the next pair in the chain is pair[j])
                temp_current = pairs[j]; // comparison is moved along one link

// BASE CASE 1 - cycle found
                if (temp_current.loser == pairs[i].winner) // If we have reached the starting pair again, we have found a cycle
                {
                    // Uncomment the following line for debugging
                    // printf("cycle found: pairs[%i]\n", i);
                    return true;
                }

// RECURSIVE CASE - look for the next connecting pair
                else if (detect_cycle(c, chain, checked_pairs, i, temp_current)) // If the recursive call to detect_cycle() returns true, propagate the result upwards
                            // recursively call function...
                            // ...starting with temp_current
                            // ...keeping chain intact, plus chain counter i
                            // ...keeping checked_pairs intact
                            // reset j
                {
                    return true;
                }

                return false; // If the recursive call did not find a cycle, the current connection does not lead to a cycle
            }
        }

// BASE CASE 2 - cycle not found
        // if backtracked to the beginning (pairs[i]) and all connections investigated...
        if (temp_current.winner == pairs[i].winner && temp_current.loser == pairs[i].loser && j == pair_count)
        {
            return false;
        }

// If no connection could be found and we are not back to the original pair, backtrack by one pair in the chain
        c--; // decrements the chain index
	    temp_current = chain[c]; // goes back to previous pair to look for other forks (while loop)
    }
}

// Print the winner of the election
/*This function works by keeping track of all the candidates who have "lost" at least once in the locked pairs graph.
It then prints out the names of the candidates who have not lost, who are thus the winners of the election.*/
void print_winner(void)
{
    bool losers[candidate_count]; // array of candidates who have lost to any other candidate

    for (int i = 0; i < candidate_count; i++) // Initialize the array to false (no losers yet)
    {
        losers[i] = 0;
    }

    for (int i = 0; i < candidate_count; i++) // Mark the candidate on the receiving end of a locked edge as a loser
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (locked[i][j])
            {
                losers[j] = true;
            }
            if (locked[j][i])
            {
                losers[i] = true;
            }
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (!losers[i]) // If a candidate has no losses, they are the winner
        {
            printf("%s\n", candidates[i]);
        }
    }
}