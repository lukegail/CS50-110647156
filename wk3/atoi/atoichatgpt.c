#include <stdio.h>
#include <cs50.h>
#include <string.h>

int convert(const string input, int n);

int main()
{
    string input = get_string("Enter a positive integer: ");
    int n = strlen(input);
    printf("%d\n", convert(input, n));
    return 0;
}

int convert(const string input, int n)
{
    // Base case: when all digits have been processed, return 0
    if (n == 0)
    {
        return 0;
    }
    // Recursive case: get the rightmost digit and add it to 10 times the result
    // of the recursive call on the rest of the string
    int digit = input[n - 1] - '0';
    return digit + 10 * convert(input, n - 1);
}