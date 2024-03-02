#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // gets height of pyramid from user, accepting 1-8
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1);

    // starts new line after each row
    for (int row = 0; row < height; row++)
    {
        // spaces before pyramid
        for (int space = 0; space < height - 1 - row; space++)
        {
            printf(" ");
        }
        // hashes
        for (int hash = row + 1; hash > 0; hash--)
        {
            printf("#");
        }
        printf("\n");
    }
}