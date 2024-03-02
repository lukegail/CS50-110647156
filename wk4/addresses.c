#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n = 50;
    printf("%i\n", n); // this is what i've been doing so far


    printf("%p\n", &n); // print the address of variable n


    int *p = &n;
    printf("%p\n", p); // print the address that p points at


    printf("%i\n", *p); // print the thing that p points at. dereference p and print it





    string s = "Hi!"; // we need cs50.h to use 'string'
    printf("%s\n", s); // this is what i've been doing so far


    char *c = "Hi!";
    printf("%p\n", c); // print the address that p points at


    printf("%s\n", c); // print the thing that c points at. dereference c and print it
                        // don't need cs50.h to use %s

    printf("%p\n", &c[0]); // %p means i'm printing out the pointer/address (&c)
    printf("%p\n", &c[1]);
    printf("%p\n", &c[2]);
    printf("%p\n", &c[3]);

/*
when you see…

printf(“%c\n”, c[0]);
printf(“%c\n”, c[1]);
printf(“%c\n”, c[2]);

what’s going on under the hood is…
*/
    printf("%c\n", *c); // %c means i'm printing out the char, and refers to *c (the thing at c)
    printf("%c\n", *(c + 1));
    printf("%c\n", *(c + 2));



    printf("%s\n", c);     // prints everything from c to \0:   Hi!
    printf("%s\n", c + 1); // prints everything from c+1 to \0: i!
    printf("%s\n", c + 2); // prints everything from c+2 to \0: !

}