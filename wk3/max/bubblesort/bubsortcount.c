// This program prompts the user for five integer inputs,
// prints them out in their original (unsorted) order,
// sorts them using the bubble sort algorithm, and then prints out the sorted list.

// this version of bubble sort counts the number of sorted pairs...
// and exits the loop when the count == the number of pairs (n - 1)

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
    int swap; // temporary variable for holding elements when doing swaps
    int sorted = 0; // counts sorted elements. "= 0" gives it a value before it is used by the while loop.
    while (sorted < n - 1) // loop while not all elements are sorted
    {
        sorted = 0;
        for (i = 0; i < n - 1; i++)
        {
            if (array[i] > array[i + 1]) // if the next element is smaller, swap them
            {
                swap = array[i + 1];
                array[i + 1] = array[i];
                array[i] = swap;
            }
            else
            {
                sorted++; // if the current element is smaller or equal, count it as sorted
            }
        }
    }

    // print sorted array
    printf("sorted: ");
    for (i = 0; i < n; i++)
    {
        printf("%i", array[i]);
    }
    printf("\n");
}