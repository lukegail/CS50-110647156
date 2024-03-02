#include <stdio.h>

void swap(int *a, int *b);

int main(void)
{
    int x = 1;
    int y = 2;

    printf("x is %i, y is %i\n", x, y);
    swap(&x, &y); //the memory addresses of x and y are passed to the swap function.
    printf("x is %i, y is %i\n", x, y);
}

void swap(int *a, int *b) // &x and &y memory addresses are stored in the pointers a and b.
{
    //the function swap() uses pointers so it can modify the original variables x and y in the main function.
    //Without pointers, swap() would only get copies of x and y,
    //and any modifications would not affect the original variables.
    int tmp = *a;
    *a = *b;
    *b = tmp;
}