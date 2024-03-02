// Include necessary libraries
#include <stdio.h>
#include <cs50.h>

// Function prototype declaration
bool is_triangle(int side[]);

int main(void)
{
    // Declare an array to hold the lengths of the sides
    int side_length[3];

    // Loop to get the lengths of the sides from the user
    int i;
    for (i = 0; i < 3; i++)
    {
        // Get the length of the side
        side_length[i] = get_int("Length of side %i: ", (i + 1));

        // If the length is invalid (less than 1), print a message and decrement the counter
        if (side_length[i] < 1)
        {
            printf("Invalid\n");
            i--;
        }
    }
    // Check if the given sides can form a triangle
    if (is_triangle(side_length))
    {
        printf("It's a triangle!\n");
    }
    else
    {
        printf("It's not a triangle\n");
    }
}

// Function to check if given sides can form a triangle
bool is_triangle(int side[])
{
    // Declare variables to hold the sides, with 'a' being the largest
    int a, b, c;

    // Check which side is the largest and assign them to a, b, and c accordingly
    if (side[0] >= side[1] && side[0] >= side[2])
    {
        a = side[0];
        b = side[1];
        c = side[2];
    }
    else if (side[1] >= side[0] && side[1] >= side[2])
    {
        a = side[1];
        b = side[0];
        c = side[2];
    }
    else
    {
        a = side[2];
        b = side[0];
        c = side[1];
    }

    // A triangle is valid if the sum of the lengths of the two smaller sides is greater than the length of the largest side
    return (b + c > a);
}