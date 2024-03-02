#include <stdio.h>
#include <cs50.h>
#include <string.h>



//    introducing strcmp



int main(void)
{
    string strings[] = {"battleship", "boot", "cannon", "iron", "thimble", "top hat"};

    string s = get_string("String: ");
    for (int i = 0; i < 6; i++)
    // re i < 6, if n is more than number of elements in the array, i will get a seg fault / core dump
    {
        if (strcmp(strings[i], s) == 0)
        // can't use (string[i] == s) to compare each char in each string.
        // strcmp takes 2 strings and if each char is the same, returns 0.
        // if str1 is alphabetically earlier or later than str2, returns ±n.
        {
            printf("Found\n");
            return 0;
        }
    }
    printf("Not found\n");
    return 1;
}
