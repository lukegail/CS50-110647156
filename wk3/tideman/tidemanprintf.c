#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

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

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("preferences[%i][%i]: %i\n", i, j, preferences[i][j]);
        }
    }
    printf("\n");


    add_pairs();
    /* for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("pairs[%i].winner: %i, .loser: %i\n", i, pairs[j].winner, pairs[j].loser);
        }
    } */

    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // loops through a voter's prefs, starting with ranks[0]
    // voter's pref is represented by [i]

    for (int i = 0; i < candidate_count; i++)
    {
        // loops thru comparisons between a voter's pref [i] and her less preferred prefs [j]
        // ex.: 1st pref vs 2nd pref (i = ranks[0], j = ranks[1])
        for (int j = i + 1; j < candidate_count; j++)
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
            // as main loops through voters, this array will continue to tally all of their preferences.
            preferences[ranks[i]][ranks[j]]++;
            printf("[ranks[%i]][ranks[%i]]: %i\n", ranks[i], ranks[j], preferences[ranks[i]][ranks[j]]);
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int pair_num = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_num].winner = i;
                pairs[pair_num].loser = j;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_num].winner = j;
                pairs[pair_num].loser = i;
            }
            printf("unsorted Pair %d Winner, Loser = %d, %d\n", pair_num, pairs[pair_num].winner, pairs[pair_num].loser);
            pair_num++;
        }
    }
    printf("\n");
    // update the global variable pair_count to be the number of pairs of candidates.
    pair_count = pair_num + 1;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair swap; // temporary variable holds values during swaps
    bool swapped; // flags swaps
    do
    {
        swapped = false;
        int i;
        for (i = 0; i < pair_count - 1; i++)
        {
            printf("sorting pairs[%i].winner strength: %i\n", i, preferences[pairs[i].winner][pairs[i].loser]);
        }
        printf("\n");

        for (i = 0; i < pair_count - 1; i++)
        {
            int strength = preferences[pairs[i].winner][pairs[i].loser];
            int strength_next = preferences[pairs[i + 1].winner][pairs[i + 1].loser];

            // if current element is larger than the next, swap them and set swapped to true
            if (strength < strength_next)
            {
                swap = pairs[i + 1];
                pairs[i + 1] = pairs[i];
                pairs[i] = swap;
                swapped = true;
            }
        }
    }
    while (swapped); // loop until there are no swaps. ("== true" is assumed.)
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
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = i + 1; j < pair_count - 1; j++)
        {
            if (!(pairs[i].winner == pairs[j].loser && pairs[i].loser == pairs[j].winner))
            {
                locked[i][j] = true;
            }
            printf("locked[%i][%i] = %i\n", i, j, locked[i][j]);
        }
    }
}












// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
            if(locked[i][j] == 1)
            {
                printf("%s\n", candidates[i]);
                return;
            }
        }
    }
}