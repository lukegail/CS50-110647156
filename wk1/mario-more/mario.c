#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // gets height from user, from 1 to 8
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // loop for each row, with /n at the end of each
    for (int row = 0; row < height; row++)
    {
        // spaces to the left
        for (int space = 0; space < height - 1 - row; space++)
        {
            printf(" ");
        }
        // hashes on the left
        for (int hash = row + 1; hash > 0; hash--)
        {
            printf("#");
        }
        // spaces in the center
        {
            printf("  ");
        }
        // hashes to the right
        for (int hash = row + 1; hash > 0; hash--)
        {
            printf("#");
        }
        printf("\n");
    }
}