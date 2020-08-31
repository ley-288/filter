#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int row = 0; row < height; row++) //move along the rows
    {
        for(int col = 0; col < width; col++) //the columns
        {
            float average = (image[row][col].rgbtBlue + image[row][col].rgbtGreen + image[row][col].rgbtRed) / 3.00; //float has an issue if you dont assign as a decimal
            int avg = round(average); //we need a float, called average. by adding the RGB and dividing by 3
            //this number is an int. we will call avg, by rounding up the average.
            image[row][col].rgbtBlue = avg;//application. row and column, apply the avg int.
            image[row][col].rgbtGreen = avg;
            image[row][col].rgbtRed = avg;
         }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++) //i height
    {
        for(int j = 0; j < width; j++) //j width
        {
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue); //the cs50 calculations for sepia
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue); //round the numbers w/ round
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            //we just need to change to our image, i,j.
            image[i][j].rgbtBlue = (sepiaBlue > 255) ? 255 : sepiaBlue; //if the numbers exceed 255, we cap them at 255.
            image[i][j].rgbtGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
            image[i][j].rgbtRed = (sepiaRed > 255) ? 255: sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++) //cycle through the pixels, height
    {
        for(int j = 0; j < width / 2; j++) //columns, but here we use / 2 to stop the pixel count halfway. hold onto half of the pixels.
        {
            int blue = image[i][j].rgbtBlue; //assign temporary values to keep them in memory. we dont want to lose the count.
            int green = image[i][j].rgbtGreen;
            int red = image[i][j].rgbtRed;

            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue; //we want to overwrite what is on one side with the other
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen; //the minus 1 moves us in that direction. until the width /2 from earlier
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed; //

            image[i][width - j - 1].rgbtBlue = blue; //now we replace the temporary values with new ones. copy and paste.
            image[i][width - j - 1].rgbtGreen = green;
            image[i][width - j - 1].rgbtRed = red;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //temp is copy of image
    RGBTRIPLE temp[height][width];

    for(int i = 0; i < height; i++) //move along the pixels..
    {
        for(int j = 0; j < width; j++)
        {
            int sumBlue = 0; //keep track of an average sum
            int sumGreen = 0;
            int sumRed = 0;
            float counter = 0.00 ; //assign a counter because we wont always divide by 9

            //create two more variables to keep track of all this

            for(int w = -1; w < 2; w++) //-1 for the pixel previous. h < 2, to move only one dot more
            {
                for(int h = -1; h < 2; h++)
                {
                    if(i + w < 0 || i + w > height -1 || j + h < 0 || j + h > width -1) //we need to take into account the edge and corner pieces. these are not / 9
                    { //so we set a boundary to make sure the counter doesnt go outside the bounds of the picture.
                        continue; //if this happens. we dont want the for loop so continue.
                    }

                    sumBlue += image[i+w][j+h].rgbtBlue; //if none of that is true we want to add up the sums
                    sumGreen += image[i+w][j+h].rgbtGreen;
                    sumRed += image[i+w][j+h].rgbtRed;

                    counter++; //add to the counter to hold what number to divide by
                }
            }

            temp[i][j].rgbtBlue = round(sumBlue/counter); //store the math here rounded. the sum of each colour didvided by counter
            temp[i][j].rgbtGreen = round(sumGreen/counter);
            temp[i][j].rgbtRed = round(sumRed/counter);
        }
    }

    for(int i = 0; i < height; i++) //lastly apply what is stored in the temp array into the image
    {
        for(int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }

    return;
}
