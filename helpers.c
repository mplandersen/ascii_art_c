#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round(round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)) / 3);
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
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        int k = 0;
        for (int j = width - 1; j >= 0; j--, k++)
        {
            temp[i][k] = image[i][j];
        }
    }


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Declare copy image
    RGBTRIPLE copy[height][width];

    // Loop for each row
    for (int i = 0; i < height; i++)
    {
        // Loop for each column
        for (int j = 0; j < width; j++)
        {
            float sumBlue = 0;
            float sumGreen = 0;
            float sumRed = 0;
            int divider = 0;

            // Loop for each row
            for (int row = i - 1; row <= i + 1; row++)
            {
                // Check if row is within boundaries
                if (row >= 0 && row < height)
                {
                    //Loop the column
                    for (int col = j - 1; col <= j + 1; col++)
                    {
                        if (col >= 0 && col < width)
                        {
                            sumBlue += image[row][col].rgbtBlue;
                            sumGreen += image[row][col].rgbtGreen;
                            sumRed += image[row][col].rgbtRed;
                            divider++;
                        }
                    }
                }
            }

            int averageBlue = 0;
            int averageGreen = 0;
            int averageRed = 0;

            //get averages
            if (divider != 0)
            {
                averageBlue = round(sumBlue / divider);
                averageGreen = round(sumGreen / divider);
                averageRed = round(sumRed / divider);
            }

            copy[i][j].rgbtBlue = averageBlue;
            copy[i][j].rgbtGreen = averageGreen;
            copy[i][j].rgbtRed = averageRed;
        }
    }

    // Copy to form image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Declare copy image
    RGBTRIPLE copy[height][width];

    int xyBlue = 0;
    int xyGreen = 0;
    int xyRed = 0;
    int Gx[3][3] = {
            {-1,  0,  1},
            {-2,  0,  2},
            {-1,  0,  1}
            };
    int Gy[3][3] = {
            {-1, -2, -1},
            { 0,  0,  0},
            { 1,  2,  1}
            };


    // Loop for each row
    for (int i = 0; i < height; i++)
    {
        // Loop for each column
        for (int j = 0; j < width; j++)
        {

            int xBlue = 0;
            int xGreen = 0;
            int xRed = 0;
            int yBlue = 0;
            int yGreen = 0;
            int yRed = 0;

            int rowCount = 0;

            // After pixel is found loop for surrounding rows
            for (int row = i - 1; row <= i + 1; row++)
            {
                // Check if pixel is within the boundaries of the image
                if (row >= 0 && row < height)
                {
                    int colCount = 0;

                    // Column in row
                    for (int col = j - 1; col <= j + 1; col++)
                    {
                        if (col >= 0 && col < width)
                        {
                            // Calculate individiual Gx Values
                            xBlue += image[row][col].rgbtBlue * Gx[rowCount][colCount];
                            xGreen += image[row][col].rgbtGreen * Gx[rowCount][colCount];
                            xRed += image[row][col].rgbtRed * Gx[rowCount][colCount];

                            // Calculate individual Gy Values
                            yBlue += image[row][col].rgbtBlue * Gy[rowCount][colCount];
                            yGreen += image[row][col].rgbtGreen * Gy[rowCount][colCount];
                            yRed += image[row][col].rgbtRed * Gy[rowCount][colCount];
                        }

                        colCount++;
                    }
                }

                rowCount++;
            }

            // Function sqrt Gx^2 * Gy^2 for each colour
            xyBlue = round(sqrt((xBlue * xBlue) + (yBlue * yBlue)));
            xyGreen = round(sqrt((xGreen * xGreen) + (yGreen * yGreen)));
            xyRed = round(sqrt((xRed * xRed) + (yRed * yRed)));

            //Cap the max at 255
            if (xyBlue > 255)
            {
                xyBlue = 255;
            }

            if (xyGreen > 255)
            {
                xyGreen = 255;
            }

            if (xyRed > 255)
            {
                xyRed = 255;
            }

            copy[i][j].rgbtBlue = xyBlue;
            copy[i][j].rgbtGreen = xyGreen;
            copy[i][j].rgbtRed = xyRed;
        }
    }

    // Copy to form image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
            image[i][j].rgbtRed = copy[i][j].rgbtRed;
        }
    }


    return;
}

//ASCII conversion
void ascii(int height, int width, RGBTRIPLE image[height][width])
{
    //convert image to greyscale
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round(round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)) / 3);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }

    // ascii list
    char ascii[] = {' ','.', '`', '^', '"', ',', ':', ';', 'I', 'l', '!', 'i', '>', '<', '~', '+', '_', '-', '?', ']', '[', '}', '{', '1', ')', '(', '|', '\\', '/', 't', 'f', 'j', 'r', 'x', 'n', 'u', 'v', 'c', 'z', 'X', 'Y', 'U', 'J', 'C', 'L', 'Q', '0', 'O', 'Z', 'm', 'w', 'q', 'p', 'd', 'b', 'k', 'h', 'a', 'o', '*', '#', 'M', 'W', '&', '8', '%', 'B', '@'};

    // create 2D array to 
    char art[height][width];


    // print ascii symbols based on greyscale
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = image[i][j].rgbtBlue;
            int n = (68 * average)/255;
            art[i][j] = ascii[n];

        }
    }

    // set newline 
    char newline = '\n';

    // export art 2D array to txt
    FILE *file = fopen("output.txt", "w");
    if (file != NULL)
    {
        for (int i = height - 1; i > 0; i--)
        {
            for (int j = 0; j < width; j++)
            {
                fprintf(file, "%c", art[i][j]);

                // bring cursor to new line in the file when it reaches the end of the width
                if (j == (width - 1))
                {
                    fprintf(file, "%c", newline);
                }
            }
        }
    }
    fclose(file);


    return;
}