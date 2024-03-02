#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    char *s = get_string("s: ");
    if (s == NULL) // Check if s is NULL (memory allocation failed or no input was received)
    {
        return 1;
    }

    char *t = malloc(strlen(s) + 1);
    if (t == NULL) // Check if t is NULL (memory allocation failed or no input was received)
    {
        return 1;
    }

    strcpy(s, t); // function copies strings properly

    if (strlen(t) > 0) // Check pointer validity and data size before use to avoid segmentation faults.
    {
        t[0] = toupper(t[0]);
    }

    printf("s: %s\n", s);
    printf("t: %s\n", t);

    free(t);

    return 0; // signifiy that everything is successful
}