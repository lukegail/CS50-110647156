#include "helpers.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
// This function≥ does this by iterating over each pixel in the image,
// calculating the average of the red, green, and blue color values, and then setting each color value to this average.
// This effectively removes the color from the image, leaving only shades of gray.
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // for each pixel, average the RBG values and assign that ave to each color
    // so if RGB values are 5, 10, 15, respectively, then change all of them to 10 (the average of 5, 10, 15)
    int average_color;

    for (int y = 0; y < height; y++) // iterate over each row
    {
        for (int x = 0; x < width; x++) // iterate over each pixel in a row
        {
            // Calculate the average color value by adding up the red, green, and blue values and dividing by 3.0.
            average_color = round((image[y][x].rgbtBlue + image[y][x].rgbtGreen + image[y][x].rgbtRed) / 3.0); // divide by 3.0 to get a float, and then round. otherwise, just dividing by 3 would give me a truncated int, ie a 6.67 would become 6

            // Set each color value to the average color value
            image[y][x].rgbtBlue = average_color;
            image[y][x].rgbtGreen = average_color;
            image[y][x].rgbtRed = average_color;
        }
    }
    return;
}


// Flip image horizontally
// This function does this by iterating over each row of pixels in the image,
// and then swapping each pixel with its mirror image pixel on the other side of the row.
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int y = 0; y < height; y++) // iterates through rows
    {
        // this swaps 2 pixels at a time. temp just stores 1 pixel.
        RGBTRIPLE temp;

        for (int x = 0; x < width / 2; x++) // only loop until middle of the row. if width is odd (5) then loop iterates half that, truncted down (2). this is fine because middle pixel stays the same anyway.
        {
            temp = image[y][width - x - 1]; // swapping
            image[y][width - x - 1] = image[y][x];
            image[y][x] = temp;
        }
        // this copies 1 row at a time. temp[] stores 1 row. // the chosen method above (swapping 2 pixels at a time) is better
        /* RGBTRIPLE temp[x];
        for (int x = 0; x < width; x++)
        {
            temp[x] = image[y][width - x - 1];
        }
        for (int x = 0; x < width; x++)
        {
            image[y][x] = temp[x];
        } */
    }
    return;
}


// Blur image
// This function does this by iterating over each pixel in the image,
// calculating the average color values of the pixel and its neighbors, and then setting the pixel's color values to these averages.
// The function uses a temporary image to store the blurred pixels, so that the blurring of one pixel doesn't affect the blurring of the next pixel.
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Allocate memory for a temporary image to store the blurred pixels
    RGBTRIPLE (*temp)[width] = malloc(sizeof(RGBTRIPLE) * height * width);

    int neighbor_sum_blue, neighbor_sum_green, neighbor_sum_red; // Variables to store the sum of the color values of a pixel's neighbors. Originally used 'RGBTRIPLE neighbor_sum.rgbtBlue' etc, a struct of BYTEs (only able to encode 0-255) so this datatype prohibited summing past 255. i had to use ints instead.)
    float neighbor_count; // variable to store the number of a pixel's neighbors

    for (int y = 0; y < height; y++) // iterate over rows
    {
        for (int x = 0; x < width; x++) // iterate over pixels in the row
        {
            // Reset the sums and count for each pixel
            neighbor_sum_blue = 0, neighbor_sum_green = 0, neighbor_sum_red = 0;

            neighbor_count = 0;

            // iterate of the pixel's neighbors
            for (int ymod = -1; ymod <= 1; ymod++) // iterate over 3 rows: above, on, and below target pixel
            {
                for (int xmod = -1; xmod <= 1; xmod++) // iterate over 3 pixels in the row: left, on, and right of target pixel
                {
                    // if the neighbor is within the image dimensions
                    if ((y + ymod) >= 0 && (y + ymod) < height && (x + xmod) >= 0 && (x + xmod) < width)
                    {
                        // Add the neighbor's color values to the sums
                        neighbor_sum_blue += image[y + ymod][x + xmod].rgbtBlue;
                        neighbor_sum_green += image[y + ymod][x + xmod].rgbtGreen;
                        neighbor_sum_red += image[y + ymod][x + xmod].rgbtRed;

                        // Increment the count of neighbors
                        neighbor_count++;
                    }
                }
            }

            // Set the pixel's color values in the temporary image to the new blurred pixel values (the averages of the sums)
            temp[y][x].rgbtBlue = round(neighbor_sum_blue / neighbor_count);
            temp[y][x].rgbtGreen = round(neighbor_sum_green / neighbor_count);
            temp[y][x].rgbtRed = round(neighbor_sum_red / neighbor_count);
        }
    }

    // Update the original image with the blurred pixels from the temporary image
    for (int y = 0; y < height; y++) // iterate over rows
    {
        for (int x = 0; x < width; x++) // iterate over pixels in each row
        {
            image[y][x].rgbtBlue = temp[y][x].rgbtBlue;
            image[y][x].rgbtGreen = temp[y][x].rgbtGreen;
            image[y][x].rgbtRed = temp[y][x].rgbtRed;
        }
    }
    free(temp);
    return;
}


// Detect edges
// This function does this by iterating over each pixel in the image,
// calculating the gradient in the x and y directions using the Sobel operator, and then setting the pixel's color values based on these gradients.
// The function uses a temporary image to store the edge-detected pixels, so that the edge detection of one pixel doesn't affect the edge detection of the next pixel.

int clamped(int color_value); // prototype for function that clamps values at 255

void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // create temp image array that will be populated with modified pixels
    RGBTRIPLE (*temp)[width] = malloc(sizeof(RGBTRIPLE) * height * width);
    if (temp == NULL)
    {
        printf("Unable to allocate memory for image\n");
        return;
    }

    // sobel kernels
    int Gx_kernel[3][3] = {
    {-1, 0, 1},
    {-2, 0, 2},
    {-1, 0, 1}};

    int Gy_kernel[3][3] = {
    {-1, -2, -1},
    {0, 0, 0},
    {1, 2, 1}};

    // Variables to store the sum of the color values of a pixel's neighbors, weighted by the Sobel operator
    int Gx_sum_blue, Gx_sum_green, Gx_sum_red;
    int Gy_sum_blue, Gy_sum_green, Gy_sum_red;

    // choose pixel to modify
    for (int y = 0; y < height; y++) // iterate over rows
    {
        for (int x = 0; x < width; x++) // iterate over pixels in the row
        {
            // Reset the sums for each pixel
            Gx_sum_blue = 0, Gx_sum_green = 0, Gx_sum_red = 0;
            Gy_sum_blue = 0, Gy_sum_green = 0, Gy_sum_red = 0;

            // Iterate over 3x3 kernel around the pixel
            for (int ymod = -1; ymod <= 1; ymod++)
            {
                for (int xmod = -1; xmod <= 1; xmod++)
                {
                    // INNER PIXELS
                    if ((y + ymod) >= 0 && (y + ymod) < height && (x + xmod) >= 0 && (x + xmod) < width) // Check if the neighboring pixel is within the image bounds.
                    {
                        // Compute Gx weighted sum for each color channel using corresponding kernel values
                        Gx_sum_blue += image[y + ymod][x + xmod].rgbtBlue * Gx_kernel[ymod+1][xmod+1];
                        Gx_sum_green += image[y + ymod][x + xmod].rgbtGreen * Gx_kernel[ymod+1][xmod+1];
                        Gx_sum_red += image[y + ymod][x + xmod].rgbtRed * Gx_kernel[ymod+1][xmod+1];

                        // Compute Gy weighted sum for each color channel using corresponding kernel values
                        Gy_sum_blue += image[y + ymod][x + xmod].rgbtBlue * Gy_kernel[ymod+1][xmod+1];
                        Gy_sum_green += image[y + ymod][x + xmod].rgbtGreen * Gy_kernel[ymod+1][xmod+1];
                        Gy_sum_red += image[y + ymod][x + xmod].rgbtRed * Gy_kernel[ymod+1][xmod+1];
                    }
                    // EDGE PIXELS: If the neighboring pixel is out of bounds, it's treated as black (value 0), it doesn't contribute to the sum and no operation is needed.
                }
            }

            // ASSIGNED CALCULATED VALUES sqrt(Gy^2 + Gx^2)) to TEMP[][]  // can't assign directly back to image because it would screw up calculations for other pixels.
            temp[y][x].rgbtBlue = clamped(round(sqrtf(pow(Gy_sum_blue, 2) + pow(Gx_sum_blue, 2))));
            temp[y][x].rgbtGreen = clamped(round(sqrtf(pow(Gy_sum_green, 2) + pow(Gx_sum_green, 2))));
            temp[y][x].rgbtRed = clamped(round(sqrtf(pow(Gy_sum_red, 2) + pow(Gx_sum_red, 2))));
        }
    }

    //update image
    memcpy(image, temp, sizeof(RGBTRIPLE) * height * width); // Copies 'temp' image data to 'image' for 'height * width' number of RGBTRIPLE units.

    free(temp);
    return;
}

int clamped(int color_value) // function that clamps values at 255
{
    if (color_value > 255)
    {
        return 255;
    }
    return color_value;
}