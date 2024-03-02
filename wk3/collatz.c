#include <stdio.h>
#include <cs50.h>

/*
This program calculates the number of steps it takes to reach 1 using the Collatz conjecture, which is defined as follows:

- Start with any positive integer n.
- If n is even, the next term is n / 2.
- If n is odd, the next term is 3n + 1.
- Repeat the process indefinitely for its sequence of numbers.

The conjecture states that no matter what value of n, the sequence will always reach 1 eventually.

The program prompts the user to input a starting integer. It then uses the Collatz function to calculate
how many steps it takes to reach 1, following the rules of the Collatz conjecture. The result is then printed
to the console.
*/

int collatz(int n);
int steps = 0;    // global variable to act as a counter

int main(void)
{
    int start = get_int("Start: ");
    collatz(start); // Initiating the recursive function with the user-provided value.
    printf("Steps: %i\n", steps);
}

int collatz(int n)
{
    // base case - when n is 1, recursion ends and...
    // the function returns the count of steps to the original function call in main
    if (n == 1)
    {
        return steps;
    }

    // recursive case - depending on the parity of n, different recursive calls are made.
    // if n is even, increment "steps" and
    // make a recursive call with the value (n / 2)
    if (n % 2 == 0)
    {
        steps++;
        return collatz(n / 2);
    }
    // if n is odd, increment "steps" and
    // make a recursive call with the value (3 * n + 1)
    else
    {
        steps++;
        return collatz(3 * n + 1);
    }
}