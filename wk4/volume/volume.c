// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    uint8_t header[44]; // array of 44 uint8_t's used to store a WAV's 44 byte header.

    fread(header, sizeof(uint8_t), 44, input); // read 44 uint8_t's of input and store them in header[]
    fwrite(header, sizeof(uint8_t), 44, output); // write 44 uint8_t's from header[] to output

    // TODO: Read samples from input file and write updated data to output file
    int16_t buffer; // a single-element variable of type int16_t

    while (fread(&buffer, sizeof(int16_t), 1, input) == 1) // reads one int16_t sample from input for each loop and stores it in buffer...
                                                           // ...until fread doesn't return 1 (meaning there are no more samples to read)
                                                           // (fread returns the the number of elements successfully read)
    {
        //adjust volume of each int16_t
        buffer *= factor; // each int16_t in the buffer is multiplied by 'factor'

        fwrite(&buffer, sizeof(int16_t), 1, output); // writes one int16_t sample from the address of buffer into output
    }

    // Close files
    fclose(input);
    fclose(output);
}
