#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // needed for uint8_t. Library that provides a set of typedefs that specify exact-width integer types

int main(int argc, string argv[]) //argc is argument count, argv is an array of argument strings.
{
    if (argc != 2)
    {
        printf("improper usage");
        return 1;
    }

    //open file
    string filename = argv[1]; // The second argument from the command line is used as the filename.

    FILE *file = fopen(filename, "r"); // A file is opened with read ("r") permissions...
                                       //...and a pointer to this file is returned and stored in 'file'.

    //check if file exists
    if (file == NULL)
    {
        printf("no such file found\n");
        return 1;
    }


    uint8_t buffer[4]; // Buffer is a temporary storage area.
                       // here the buffer is used to hold the first four bytes read from the file.
                       // an array of 4 bytes is created, each of type uint8_t (an unsigned 8-bit integer, which is effectively a byte).
    uint8_t signature[] = {37, 80, 68, 70}; // byte sequence that PDF files start with (in ASCII, "%PDF").

    fread(buffer, 1, 4, file); // Reads 4 units of data, each 1 byte long, from the 'file' and stores it in 'buffer'.
    fclose(file);

    //does the buffer signature match?
    for (int i = 0; i < 4; i++)
    {
        if (buffer[i] != signature[i])
        {
            printf("likely not a pdf\n");
            return 0;
        }
    }
    printf("likely a pdf\n");
    return 0;
}