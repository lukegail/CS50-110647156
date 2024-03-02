// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>

// declares function that accepts a string as argument and returns a string
string replace(string word);

int main(int argc, string argv[])
{
    // program will only accept one command-line argument
    if (argc != 2)
    {
        // prints "Error" if user doesn't enter just one command-line argument
        // returns 0 to indicate an error has occured
        printf("Error\n");
        return 1;
    }
    // prints the modified word
    // returns 0 to indicate successful execution of program
    printf("%s\n", replace(argv[1]));
    return 0;
}

// defines the replace function
string replace(string word)
{
    // iterates through each letter until the end of the word (NUL character)
    for (int i = 0; word[i] != '\0'; i++)
    {
        // switch statement replacing some vowels with numbers
        switch (word[i])
        {
            case 'a':
                word[i] = '6';
                break;

            case 'e':
                word[i] = '3';
                break;

            case 'i':
                word[i] = '1';
                break;

            case 'o':
                word[i] = '0';
                break;

            // if the char is not one of these vowels, do nothing
            default:
                break;
        }
    }
    // returns the modified word
    return word;
}