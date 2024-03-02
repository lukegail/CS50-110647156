#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
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
    int result = 0;
    for (int i = 0; i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid input!\n");
            return -1;
        }
        result = result * 10 + (input[i] - '0');
    }
    return result;
}