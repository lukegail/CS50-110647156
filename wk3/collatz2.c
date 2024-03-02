#include <stdio.h>
#include <cs50.h>

/*
Instead of using a global variable "steps" to count the number of steps,
this version of the program uses the return values of the recursive function calls themselves
to keep track of the step count.
Each call to the function collatz(n) returns 1 plus the number of steps to reach
1 from n/2 (if n is even) or 3n + 1 (if n is odd).

When the recursion reaches its base case (i.e., when n is 1), the function returns 0.
This value is then added to the return value of the previous function call in the call stack,
which is 1 plus the number of steps from the previous value of n to 1.
This process continues all the way up the call stack,
with each return value being added to the one below it, until we get back to the original function call,
which returns the total number of steps.

In other words, instead of incrementing a counter with each step,
this version of the program uses the depth of the call stack to represent the count,
and the addition of the return values to calculate the total number of steps.
This makes the function purely recursive, with no need for external state.

tl;dr - this process involves recursive calls to the Collatz function,
with each call adding a new frame to the system's call stack.
The "counter" of steps is effectively represented by the depth of this call stack.
*/

int collatz(int n);

int main(void)
{
    int start = get_int("Start: ");
    int steps = collatz(start); // Initiating the recursive function with the user-provided value.
    printf("Steps: %i\n", steps);
}

int collatz(int n)
{
    // base case: when n is 1, recursion ends and the function returns 0...
    // which will be added to the return values of all the previous function calls in the call stack.
    if (n == 1)
    {
        return 0;
    }

    // recursive case: depending on the parity of n, different recursive calls are made.
    // In both cases, 1 is added to the return value to count the current step.
    // if n is even...
    if (n % 2 == 0)
    {
        // Create a new frame on the call stack and make a recursive call with the value (n / 2)
        // The return value is the number of steps from (n / 2) to 1, plus 1 for the current step
        return 1 + collatz(n / 2);
    }
    // if n is odd, ...
    else
    {
        // Create a new frame on the call stack and make a recursive call with the value (3 * n + 1)
        // The return value is the number of steps from (3 * n + 1) to 1, plus 1 for the current step
        return 1 + collatz(3 * n + 1);
    }
}