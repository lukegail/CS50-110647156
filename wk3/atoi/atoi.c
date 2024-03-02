#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input, int n, int index, int mult);

int main(void)
{
    string input = get_string("Enter a positive integer: ");
    int n = strlen(input);

    for (int i = 0; i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    int index = n - 1; // index is initialized to the last element in input[]
    int mult = 1;

    // Convert string to int
    printf("%i\n", convert(input, n, index, mult));
}

int convert(string input, int n, int index, int mult)
{
    // base case: returns 0 after processing input[0], finishing recursion; 0 populates previous convert() call.
    if (index < 0)
    {

        return 0;
    }

    // recursive case: multiply the current digit by its position's multiplier,
    // then add the result of the recursive call to process the rest of the digits
    else
    {
        // pow function gets (base, exponent) and returns value.
        // Calculate the multiplier based on the position of the digit in the number
        mult = pow(10, (n - 1) - index);
        // (input[index] - 48) is the char -> int ascii converter
        // last digit will be * 1
        // 2nd to last digit will be *10
        // 3rd to last digit will be *100, etc.
        // convert() call decrements index, so it can process the next digit, right to left.
        return ((input[index] - 48) * mult) + convert(input, n, index - 1, mult);
    }
}