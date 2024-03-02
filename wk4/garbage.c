#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int scores[1024];
    // array is not initialized so program will print garbage values
    for (int i = 0; i < 1024; i++)
    {
        printf("%i\n", scores[i]);
    }
}