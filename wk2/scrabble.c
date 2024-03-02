#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
const int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    //printf("score1 = %i\n", score1);
    int score2 = compute_score(word2);
    //printf("score2 = %i\n", score2);

    // print winner or tie
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    int total = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        // only alphabetic chars are counted
        if (isalpha(word[i]))
        {
            // any lowercase chars are changed to uppercase
            // their ASCII values - 65 scores each char by the POINTS array at the top of the code
            // values are tallied into a var named "total"
            total += POINTS[toupper(word[i]) - 65];
        }
        else
        {
            total += 0;
        }
    }
    // tallied total score is returned
    return total;
}
