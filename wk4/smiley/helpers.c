#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing
    for (int i = 0; i < height; i++) // interate though rows, top to bottom
    {
        for (int j = 0; j < width; j++) // iterate through each pixel of a row, from left to right
        {
            // if the RGB values of a pixel at image [i][j] are all 0, then...
            if (image[i][j].rgbtBlue == 0 && image[i][j].rgbtGreen == 0 && image[i][j].rgbtRed == 0)
            {
                // change the RGB values of that pixel
                image[i][j].rgbtBlue = 0xff;
                image[i][j].rgbtGreen = 0xe0;
                image[i][j].rgbtRed = 0x48;
            }
        }
    }
}
