#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }
    ////////printf("Arguments check passed.\n");

    // Open input file for reading
    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL)
    {
        printf("Failed to open file\n");
        return 1;
    }

    // Read header from input file
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, input_file);

    // Use check_format to ensure WAV format
    ////////printf("header.format[0-3]: %c%c%c%c\n", header.format[0], header.format[1], header.format[2], header.format[3]);
    if (!check_format(header))
    {
        printf("Input is not a WAV file.\n");
        return 1;
    }

    // Open output file for writing
    FILE *output_file = fopen(argv[2], "w");
    if (output_file == NULL)
    {
        printf("failed to open output file\n");
        return 1;
    }

    // Write header to output file
    fwrite(&header, sizeof(header), 1, output_file);

    // Use get_block_size to calculate size of block
    int block_size = get_block_size(header);

    // allocate a buffer to hold a block of audio data
    BYTE *buffer = malloc(block_size);
    if (buffer == NULL)
    {
        printf("memory allocation failed");
        return 1;
    }

    // calculate total number of audio blocks
    fseek(input_file, 0, SEEK_END);
    int filesize = ftell(input_file);
    int total_blocks = (filesize - sizeof(header)) / block_size;

    // counts how many blocks have been written
    int block_counter = 1;

    do // read a block from the end of the file and write to the output file
    {
        fseek(input_file, -block_size * block_counter, SEEK_END); // position the input file's pointer at the end minus the size of blocks already read
        fread(buffer, block_size, 1, input_file); // read a block from the input file

        if (fwrite(buffer, sizeof(block_size), 1, output_file) != 1) // write block to output file
        {
            printf("writing to output file failed\n");
            return 1;
        }
        block_counter++;
    }
    while(block_counter <= total_blocks);
    //while (ftell(input_file) > sizeof(header));

    free(buffer);
    fclose(input_file);
    fclose(output_file);
}

// if the format field in the header is 'WAVE', then the file is in WAV format
int check_format(WAVHEADER header)
{
    if (header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int get_block_size(WAVHEADER header)
{
    // block size == number of channels multiplied by bytes per sample
    return (header.numChannels * header.bitsPerSample / 8);
}