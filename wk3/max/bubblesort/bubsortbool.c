// This program prompts the user for five integer inputs,
// prints them out in their original (unsorted) order,
// sorts them using the bubble sort algorithm, and then prints out the sorted list.

// This version of bubble sort uses a bool flag to keep track of whether any swaps were made.
// the first loop that doesn't require a swap exits the loop.
// a do while loop is used to ensure the loop runs at least once.

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n = 5; // size of the array
    int array[n]; // declare the array
    int i;

    // get array from user
    for (i = 0; i < n; i++)
    {
        array[i] = get_int("enter number %i: ", i + 1);
    }

    // print unsorted array
    printf("unsorted: ");
    for (i = 0; i < n; i++)
    {
        printf("%i", array[i]);
    }
    printf("\n");

    // bubble sort
    int swap; // temporary variable holds values during swaps
    bool swapped; // flags swaps
    do
    {
        swapped = false;
        for (i = 0; i < n - 1; i++)
        {
            // if current element is larger than the next, swap them and set swapped to true
            if (array[i] > array[i + 1])
            {
                swap = array[i + 1];
                array[i + 1] = array[i];
                array[i] = swap;
                swapped = true;
            }
        }
    }
    while (swapped); // loop until there are no swaps. ("== true" is assumed.)

    // print sorted array
    printf("sorted: ");
    for (i = 0; i < n; i++)
    {
        printf("%i", array[i]);
    }
    printf("\n");
}