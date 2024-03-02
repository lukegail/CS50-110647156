#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    // Create buffer to read into
    char buffer[7]; // holds 1 plate (plus \0)

    // Create array to store plate numbers
    char (*plates)[7] = malloc(8 * sizeof(buffer)); // note that the number of chars in each string [7] is specified, NOT the number of strings in the array.
                                                    // also note that () are needed around the pointer >> char (*plates)[7] << because [] take precedent over * oherwise...
                                                    // ...so without () this would parsed as char *(plates[7]);, i.e., an array of 7 pointers to char.

    FILE *infile = fopen(argv[1], "r");

    int idx = 0;

    while (fread(buffer, 1, 7, infile) == 7) // keep doing the loop as long as fread is able to successfully read 7 items of data from infile into buffer
    {
        // Replace '\n' with '\0'
        buffer[6] = '\0'; // 7th char of each line is \n

        // Save plate number in array
        strcpy(plates[idx], buffer); // use strcpy to avoid having to iterate over every char
        idx++;
    }

    fclose(infile);

    for (int i = 0; i < 8; i++)
    {
        printf("%s\n", plates[i]);
    }

    free(plates);
}
