#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int length;
    do
    {
        length = get_int("Length: ");
    }
    while (length < 1 || length > 32);

    int numbers[length];
    int value = 1;
    for (int i = 0; i < length; i++)
    {
        numbers[i] = value;
        printf("%i\n", numbers[i]);
        value *= 2;
    }
}