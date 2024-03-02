/*
This program creates a new, empty file with the name provided as a command-line argument.
This program takes a filename as a command-line argument, allocates memory to store this filename, and then creates a new, empty file with this name.
The program will print a usage message and exit if not exactly one command-line argument is provided.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Check for improper usage, otherwise, get filename length
    if (argc != 2)
    {
        printf("Wrong usage: Try ./create [filename]\n");
        return 1;
    }
    int filename_length = strlen(argv[1]);

    // Create a new block of memory to store filename
    char *filename = malloc(sizeof(char) * filename_length + 1);

    // Copy argv[1] into block of memory for filename
    sprintf(filename, "%s", argv[1]); // copy the string from argv[1] into filename.

    // Open new file under the name stored at filename
    FILE *new_file = fopen(filename, "w");
    
    if (new_file == NULL)
    {
        printf("file unable to be opened\n");
    }

    free(filename);
    fclose(new_file); //Closes the file pointed to by the given file pointer.
}