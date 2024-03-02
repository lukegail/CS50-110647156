#include <cs50.h>
#include <stdio.h>

bool nonprime(int number);

int main(void)
{
    int min;
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    int max;
    do
    {
        max = get_int("Maximum: ");
    }
    while (min >= max);

    for (int i = min; i <= max; i++)
    {
        if (nonprime(i))
        {
            printf("%i\n", i);
        }
    }
}

bool nonprime(int number)
{
    // low values 1-3
    if (number == 1)
    {
        return true;
    }
    if (number == 2 || number == 3)
    {
        return false;
    }

    // all higher values
    for (int d = 2; d < number; d++)
    {
        if (number % d == 0)
        {
            return true;
        }
    }
    return false;
}