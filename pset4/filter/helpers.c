#include "helpers.h"
#include <math.h>
// Convert image to grayscale

void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/ 3.00);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width)/2; j++)
        {
            int temp1 = image[i][j].rgbtRed;
            int temp2 = image[i][j].rgbtGreen;
            int temp3 = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;

            image[i][width - j - 1].rgbtRed = temp1;
            image[i][width - j - 1].rgbtGreen = temp2;
            image[i][width - j - 1].rgbtBlue = temp3;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    /*
    psuedocode used:
    http://amritamaz.net/blog/understanding-box-blur
    for each row
        for each col
            set count to 0
            for every neighboring pixel within the radius m in the x direction
            for every neighboring pixel within the radius m in the y direction
                add the color to the total
                count++
            final_color = total/count
            setpixel(current x, current y, final_color)
    */
    // duplicate image
    RGBTRIPLE copy[height][width];
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            copy[row][col] = image[row][col];
        }
    }

    //go through every pixel of copy
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            //count is for how many boxes we have averaged
            int count = 0;
            //literally make a box around the pixel
            int rowCoords[] = {row - 1, row, row + 1};
            int colCoords[] = {col - 1, col, col + 1};
            float totalRed = 0, totalGreen = 0, totalBlue = 0;
            //loop through that box itself and add total red, green, and blue values.
            for(int r = 0; r < 3; r++)
            {
                for (int c = 0; c < 3; c++)
                {
                    int currRow = rowCoords[r];
                    int currCol = colCoords[c];
                    //check to see if the pixels are in the image. if they are edge cases, then that pixel will be out of the actual image and we will not average that pixel
                    if(currRow >= 0 && currRow < height && currCol >=0 && currCol < width)
                    {
                        RGBTRIPLE currPixel = image[currRow][currCol];
                        totalRed += currPixel.rgbtRed;
                        totalGreen+= currPixel.rgbtGreen;
                        totalBlue += currPixel.rgbtBlue;
                        count++;
                    }
                }
            }
            //give the new averaged values for each pixel
            copy[row][col].rgbtRed = round(totalRed / count);
            copy[row][col].rgbtGreen = round(totalGreen / count);
            copy[row][col].rgbtBlue = round(totalBlue / count);

        }
    }
    //copy everything back to original image
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            image[row][col] = copy[row][col];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0,  0,  0}, {1,  2,  1}};
    //copy
    RGBTRIPLE copy[height][width];

    for(int row = 0; row < height; row++)
    {
        for(int col = 0; col < width; col++)
        {
            int rowCoords[] = {row - 1, row, row + 1};
            int colCoords[] = {col - 1, col, col + 1};
            float Gx_red = 0, Gx_green = 0, Gx_blue = 0, Gy_red = 0, Gy_green = 0, Gy_blue = 0;
            for(int r = 0; r < 3; r++)
            {
                for (int c = 0; c < 3; c++)
                {
                    int currRow = rowCoords[r];
                    int currCol = colCoords[c];
                    //check to see if the pixels are in the image. if they are edge cases, then that pixel will be out of the actual image and we will not average that pixel
                    if(currRow >= 0 && currRow < height && currCol >=0 && currCol < width)
                    {
                        RGBTRIPLE currPixel = image[currRow][currCol];

                        Gx_red += currPixel.rgbtRed * Gx[r][c];
                        Gx_green += currPixel.rgbtGreen * Gx[r][c];
                        Gx_blue += currPixel.rgbtBlue * Gx[r][c];

                        Gy_red += currPixel.rgbtRed * Gy[r][c];
                        Gy_green += currPixel.rgbtGreen * Gy[r][c];
                        Gy_blue += currPixel.rgbtBlue * Gy[r][c];
                    }
                }
            }
            int red = round(sqrt(Gx_red * Gx_red + Gy_red * Gy_red));
            int green = round(sqrt(Gx_green * Gx_green + Gy_green * Gy_green));
            int blue = round(sqrt(Gx_blue * Gx_blue + Gy_blue * Gy_blue));
            //cap at 255
            if(red > 255)
            {
                red = 255;
            }
            if(green > 255)
            {
                green = 255;
            }
            if(blue > 255)
            {
                blue = 255;
            }
            copy[row][col].rgbtRed = red;
            copy[row][col].rgbtGreen = green;
            copy[row][col].rgbtBlue = blue;

        }
    }
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            image[row][col] = copy[row][col];
        }
    }

    return;
}


