#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>

int main(void)
{
    long long input;
    do
    {
        input = get_long("Number: ");
    }
    while (input < 0);

    long secondToLast, last;
    int i;
    long length = 0;
    long sum1 = 0;
    long sum2 = 0;
    long totalSum = 0;
    long firstNum, secondNum;
    int mc;

    //Finds the length of the input
    long temp = input;
    while (temp > 0)
    {
        temp /= 10;
        length++;
    }
    //For loop goes through every 2 digits in
    //input and takes out the ones we want.
    for (i = 0; i <= length; i += 2)
    {
        secondToLast = input / (long)pow(10, i + 1);
        secondToLast = secondToLast % 10;
        last = input / (long)pow(10, i);
        last = last % 10;

        //This is to separate the digits into individual digits.
        if (secondToLast * 2 > 9)
        {
            firstNum = secondToLast * 2 / 10;
            secondNum = secondToLast * 2 % 10;
            sum1 = sum1 + firstNum + secondNum - (secondToLast * 2);
        }
        //Add the digits we get
        sum1 = sum1 + secondToLast *  2;
        sum2 = sum2 + last;
    }

    totalSum = sum1 + sum2;
    //Final step of checksum to see if the last digit is 0 or not.
    if (totalSum % 10 == 0)
    {
        //AMEX Cards start with 34 or 37 and have 15 digits
        if (length == 15)
        {
            if (input / (long)pow(10, 13) == 34 || input / (long)pow(10, 13) == 37)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }

        //MasterCard and VISA both have 16 digits (Their other conditions are also put here)
        mc = input / (long)pow(10, 14);

        if (length == 16)
        {
                if (mc > 50 && mc < 56)
                {
                    printf("MASTERCARD\n");
                }
                else
                {
                    printf("INVALID\n");
                }


            if (input / (long)pow(10, 15) == 4)
            {
                printf("VISA\n");
            }
        }

        //VISA uses 13 or 16 digits and start with 4
        if (length == 13)
        {
            if (input / (long)pow(10, 12) == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
    }
    else
    {
        printf("INVALID\n");
    }
    // If it is valid but it's not the right length, print invalid.
    if (totalSum % 10 == 0)
    {
        if (length < 13 || length == 14 || length > 16)
        {
            printf("INVALID\n");
        }
    }

}
