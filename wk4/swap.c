#include <stdio.h>

void swap(int a, int b);

int main(void)
{
    int a = 23;
    int b = 37;
    swap(a, b);
}

void swap(int a, int b)
{
    int tmp = a;
    a = b;
    b = tmp;

    printf("a: %i\nb: %i\n", a, b);
}