#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    int i = get_int("i: ");
    int j = get_int("j: ");

    if ( i == j)
    {
        printf("Same\n");

    }
    else
    {
        printf("Different\n");
    }




    char *s = get_string("s: ");
    char *t = get_string("t: ");

    if (strcmp(s, t) == 0) // campares the strings that each pointer points to
    {
        printf("Same\n");

    }
    else
    {
        printf("Different\n");
    }

    printf("&s (what s points to):                %p\n", s); // prints the address that each pointer holds
    printf("memory address of the pointer itself: %p\n", &s); // prints the print the memory address of the pointer s itself, not the address s points to.
}