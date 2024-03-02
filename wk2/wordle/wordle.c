#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// each of our text files contains 1000 words
#define LISTSIZE 1000

// values for colors and score (EXACT == right letter, right place; CLOSE == right letter, wrong place; WRONG == wrong letter)
#define EXACT 2
#define CLOSE 1
#define WRONG 0

// ANSI color codes for boxed in letters
#define GREEN   "\e[38;2;255;255;255;1m\e[48;2;106;170;100;1m"
#define YELLOW  "\e[38;2;255;255;255;1m\e[48;2;201;180;88;1m"
#define RED     "\e[38;2;255;255;255;1m\e[48;2;220;20;60;1m"
#define RESET   "\e[0;39m"

// user-defined function prototypes
string get_guess(int wordsize);
int check_word(string guess, int wordsize, int status[], string choice);
void print_word(string guess, int wordsize, int status[]);

//   1. The program starts with checking the command-line arguments. It needs to receive one argument that is the size of the word to be guessed (5, 6, 7, or 8).
//   2. The program opens a file with the corresponding word size. The file contains 1000 words of that size. If the file cannot be opened, it throws an error message.
//   3. It loads the words from the file into an array. Then it pseudorandomly selects one word from this array to be the word the user has to guess.
//   4. The game loop starts. It will iterate wordsize + 1 times. In each iteration:
//      a. It asks the user for a guess of the right size.
//      b. It checks the guess against the chosen word, scoring points for exact and close matches. This score and the status of each letter (exact, close, or wrong) are stored.
//      c. The guess is printed with color-coding for the status of each letter.
//      d. If the guess is exactly correct, it sets won to true and breaks the loop.
//   5. After the game loop, the program checks the value of won. If it's false, the chosen word is printed. If it's true, a winning message is printed.

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./wordle wordsize\n");
        return 1;
    }

    // ensure argv[1] is either 5, 6, 7, or 8 and store that value in wordsize instead
    int wordsize = atoi(argv[1]);
    if (wordsize != 5 && wordsize != 6 && wordsize != 7 && wordsize != 8)
    {
        printf("Error: wordsize must be either 5, 6, 7, or 8\n");
        return 1;
    }

    // open correct file, each file has exactly LISTSIZE words
    char wl_filename[6];
    sprintf(wl_filename, "%i.txt", wordsize);
    FILE *wordlist = fopen(wl_filename, "r");
    if (wordlist == NULL)
    {
        printf("Error opening file %s.\n", wl_filename);
        return 1;
    }

    // load word file into an array of size LISTSIZE
    char options[LISTSIZE][wordsize + 1];

    for (int i = 0; i < LISTSIZE; i++)
    {
        fscanf(wordlist, "%s", options[i]);
    }

    // pseudorandomly select a word for this game
    srand(time(NULL));
    string choice = options[rand() % LISTSIZE];

    // allow one more guess than the length of the word
    int guesses = wordsize + 1;

    // This line initializes a boolean variable 'won' to false. This variable is likely used to track whether the player has won the game or not. It starts as false because the player hasn't won the game at the start. Presumably, there will be code later on in your program that sets 'won' to true when the player correctly guesses the word.
    bool won = false;

    // print greeting, using ANSI color codes to demonstrate
    printf(GREEN"This is WORDLE50"RESET"\n");
    printf("You have %i tries to guess the %i-letter word I'm thinking of\n", guesses, wordsize);

    // main game loop, one iteration for each guess
    for (int i = 0; i < guesses; i++)
    {
        // obtain user's guess
        string guess = get_guess(wordsize);

        // array to hold guess status, initially set to zero
        int status[wordsize];

        // Calculate score for the guess
        int score = check_word(guess, wordsize, status, choice);

        // Print the guess
        printf("Guess %i: ", i + 1);
        print_word(guess, wordsize, status);

        // if they guessed it exactly right, set terminate loop
        if (score == EXACT * wordsize)
        {
            won = true;
            break;
        }
    }

    // Print the game's result
    if (won == false)
    {
        printf("%s\n", choice);
    }
    else
    {
        printf("You won!\n");
    }

    return 0;
}

// ensure users actually provide a guess that is the correct length
string get_guess(int wordsize)
{
    string guess;
    do
    {
        guess = get_string("Input a %i-letter word: ", wordsize);
    }
    while (strlen(guess) != wordsize);
    return guess;
}

// compare guess to choice and score points as appropriate, storing points in status
int check_word(string guess, int wordsize, int status[], string choice)
{
    int score = 0;

    for (int i = 0; i < wordsize; i++)
    {
        status[i] = 0;
    }

    for (int i = 0; i < wordsize; i++)
    {
        for (int j = 0; j < wordsize; j++)
        {
            if (guess[i] == choice[i])
            {
                score += EXACT;
                status[i] = EXACT;
                break;
            }
            if (guess[i] == choice[j])
            {
                score += CLOSE;
                status[i] = CLOSE;
            }
        }
    }

    return score;
}

// print word character-for-character with correct color coding, then reset terminal font to normal
void print_word(string guess, int wordsize, int status[])
{
    for (int i = 0; i < wordsize; i++)
    {
        if (status[i] == 2)
        {
            printf(GREEN"%c", guess[i]);
        }
        else if (status[i] == 1)
        {
            printf(YELLOW"%c", guess[i]);
        }
        else
        {
            printf(RED"%c", guess[i]);
        }
    }
    printf(RESET"\n");
}
