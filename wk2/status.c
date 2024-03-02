#include <stdio.h>
#include <cs50.h>

// run program with a CLI argument: ./status luke
int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Missing command-line argument\n");
        return 1;
    }
    else
    {
        printf("Hello, %s\n", argv[1]);
        return 0;
    }
}
// $ echo $? to see what the exit status the program ended with (1 or 0)