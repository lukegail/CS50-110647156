// Implements a dictionary's functionality

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Choose number of buckets in hash table
const unsigned int N = 143091;

// Hash table
node *table[N];

unsigned int loaded_words = 0; // updated in 'load' function, utilized in 'size' function, reported in speller.c as "WORDS IN DICTIONARY:  %d\n"

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node *cursor = table[hash(word)]; // hash the word to obtain a hash index, and set a pointer 'cursor' to it.

    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0) // case-insensitive string comparison between the word and the cursor node's word
        {
            return true; // returns true if they are are the same
        }
        cursor = cursor->next; // else, move cursor to the next node to compare again
    }

    return false; // return false if word not in dictionary (linked list at the hash index is search without returning true)
}

// hashes word to a number
unsigned int hash(const char *word)
{
    int word_length = strlen(word); // calculate the length of the word
    int hash_calc = 0; // initialize the intermediate hash value

    for (int i = 0; i < 8; i++) // loop through the first 8 characters of the word
    {
        if (word_length > i) // check if there is a character at the i-th position in the word
        {
            /* adds a value calculated from the character to the intermediate hash value. to do this...
            Convert character to lowercase and then 'a' is subtracted to make it 0-based.
            Multiply by 10^(7-i) to place the character at the appropriate "decimal" place.
            1 is added at the end (so "a" and "aa" aren't both hashed to zero).*/
            hash_calc += (tolower(word[i]) - 'a') * pow(10, 7 - i) + 1;
        }
    }
    return hash_calc % N; // return the hash value, which is the intermediate hash value modulo the size of the hash table
}

// Loads dictionary into memory
bool load(const char *dictionary)
{
    FILE *dict_file = fopen(dictionary, "r"); // open dictionary file, set a pointer to it

    if (dict_file == NULL) //check if return value is NULL
    {
        printf("failed to open file.\n");
        return false;
    }

    char word_buffer[LENGTH + 1]; // declare a buffer to read words into

    // read strings from file one at a time
    while (fscanf(dict_file, "%s", word_buffer) == 1) // from 'dict_file' (the dictionary), scan one string ('%s') at a time, into a char array ('word_buffer')
    {

        // create a new node for each word
        node *n = malloc(sizeof(node)); // allocate memory for a node, set pointer 'n' to it.
        if (n == NULL) // check if return value is NULL
        {
            printf("failed to allocate memory for a node.\n");
            return false;
        }

        // hash the word
        int hash_value = hash(word_buffer);

        strcpy(n->word, word_buffer); // initialize node's 'word' field (put a word into the node)
        n->next = table[hash_value] == NULL ? NULL : table[hash_value]; // initialize node's 'next' field. set n->next to NULL if the list is empty, or set it to point to the existing head of the list at table[hash_value] if there's already a node in the list.

        table[hash_value] = n; // update head of list to new node

        loaded_words++; // counts words loaded from dictionary. utilized in 'size' function
    }

    fclose(dict_file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return loaded_words; // reported in speller.c as "WORDS IN DICTIONARY:  %d\n"
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++) // Loop through each element in the hash table array
    {
        while (table[i] != NULL) // search in the linked list at table[i]
        {
            node *cursor = table[i]->next; // Store the next node in a temporary cursor variable
            free(table[i]); // free the node at the head of the linked list
            table[i] = cursor; // make that next node the new head of the linked list
        }
    }

    return true;
}