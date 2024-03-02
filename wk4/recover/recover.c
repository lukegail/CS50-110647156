#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE; // buffer datatype (blocks are 512B each)
char filename[8]; // variable to store filename

int main(int argc, char *argv[])
{
    // correct number of arguments?
    if (argc != 2)
    {
        printf("correct usage: ./recover filename\n");
        return 1;
    }

    // open input file
    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL)
        {
            printf("failed to open file\n");
            return 1;
        }

    // allocate memory to buffer
    BYTE *buffer = malloc(512 * sizeof(BYTE));
    if (buffer == NULL)
        {
            printf("memory allocation failed\n");
            fclose(input_file);
            return 1;
        }

    int jpg_counter = 0; // counter for the number of jpg files created
    FILE *jpg_file; // file pointer for current file being processed

    // loop through input file, reading 512 bytes at a time until there are no more full blocks (less than 512 bytes)
    while (fread(buffer, 1, 512, input_file) == 512)
    {
        // look for jpg header
        if (buffer [0] == 0xff && buffer [1] == 0xd8 && buffer [2] == 0xff && (buffer [3] & 0xf0) == 0xe0)
        {
            if (jpg_counter == 0) // if the first jpg
            {
                // make a new jpg file
                // name new file
                sprintf(filename, "%03i.jpg", jpg_counter); // with a three-digit number (e.g., "001.jpg")

                // open new file
                jpg_file = fopen(filename, "w");

                // start writing data to new file
                fwrite(buffer, 1, 512, jpg_file);

                jpg_counter++; // increment counter for next jpg file
            }
            else // not the first jpg
            {
                fclose(jpg_file); // close previous jpg file

                // update filename for next jpg
                sprintf(filename, "%03i.jpg", jpg_counter);

                // open new file
                jpg_file = fopen(filename, "w");

                // start writing data to new file
                fwrite(buffer, 1, 512, jpg_file);

                jpg_counter++;
            }
        }
        else // if block does NOT start with jpg header
        {
            if (jpg_counter != 0) // ...and if a jpg file has already been created
            {
                // continue writing data to current file
                fwrite(buffer, 1, 512, jpg_file);
            }
        }
    }
// close input and output files. free memory
fclose(input_file);
fclose(jpg_file);
free(buffer);
}