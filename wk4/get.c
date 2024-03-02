#include <stdio.h>

int main(void)
{
    // like get_int
    int x;
    printf("x: ");
    scanf("%i", &x); // scans user's input (expecting an int), and assigns it to the supplied address &x
    printf("x: %i\n", x);

    //like get_string
    // getting user input is difficult in c.
    char s[4]; // get_string calls malloc for each character typed, allocating extra memory as needed
    printf("s: ");
    scanf("%s", s);
    printf("s: %s\n", s);
}