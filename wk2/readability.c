#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// function prototypes
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int coleman_liau(int let, int wor, int sen);

// this program prompts user for a string of text
// and prints the grade level of the writing.
// it counts the number of letters, words, and sentences/
// longer words and longer sentences ~= higher grade level.
int main(void)
{
// user is prompted for text
    string text = get_string("Text: ");

// the text is passed into functions that count the letters, words, and sentences
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);
    //printf("let: %i\nwor: %i\nsen: %i\n", let, wor, sen);

// calls a function which accepts the prior counts as arguments
// and returns an int that initializes a variable named index
    int index = coleman_liau(letters, words, sentences);
    //printf("Index: %i\n", index);

// prints grade level
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

// LETTERS
// iterates through the string and tallies alphabetic chars into a variable names letters
int count_letters(string text)
{
    int letters = 0;
    for (int i = 0; i <= strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }
    return letters;
}

// WORDS
// tallies the number of spaces (null chars)
int count_words(string text)
{
    int words = 0;
    for (int i = 0; i <= strlen(text); i++)
    {
        if (isspace(text[i]) || text[i] == '\0')
        {
            words++;
        }
    }
    return words;
}

// SENTENCES
// tallies sentences, including those that end with... or?" (for example)
int count_sentences(string text)
{
    int sentences = 0;
    for (int i = 0; i <= strlen(text); i++)
    {
// tallies (. ! ?)
        if ((text[i] == '.' || text[i] == '!' || text[i] == '?'))
        {
// ...with a space or \0 after it
            if (isspace(text[i + 1]) || text[i + 1] == '\0')
            {
                sentences++;
            }
        }
// same again but now considering sentences that end with " or )
// (. ! ?)
        else if ((text[i - 1] == '.' || text[i - 1] == '!' || text[i - 1] == '?'))
        {
// ...with " or ) after it...
            if (text[i] == '"' || text[i] == ')')
            {
// ...with a space or \0 after it
                if (isspace(text[i + 1]) || text[i + 1] == '\0')
                {
                    sentences++;
                }
            }
        }
    }
    return sentences;
}

// the next few lines find L (letters per 100 words) and S (sentences per 100 words)
// L and S are plugged into the Coleman-Liau index (index = 0.0588 * L - 0.296 * S - 15.8)
// index, rounded, == grade level
int coleman_liau(int let, int wor, int sen)
{
    float L = (let / (float) wor * 100);
    //printf("L: %.3f\n", L);
    float S = (sen / (float) wor * 100);
    //printf("S: %.3f\n", S);
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    return index;
}