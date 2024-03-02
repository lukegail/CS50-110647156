#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *x;
    int *y;

    x = malloc(sizeof(int));

    *x = 42;
    //*y = 13; this line won't work because memory hasn't yet been allocated for pointer y

    y = x; // here, y gets the address in x, so now y points to allocated memory

    *y = 13;
}