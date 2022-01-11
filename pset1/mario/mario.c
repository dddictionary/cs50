#include <stdio.h>
#include <cs50.h>

int main (void)
{
    int height;
    do
    {
        height = get_int ("Height: ");
    }
    while(height < 1 || height > 8 );

    /*Goes througheach row and executes the other
    loops that draw the hash*/
    for(int row = 1; row <= height; row++)
    {
        //makes the left pyramid
        /*The number of spaces needed is equal to the height we give
        given minus the row we are currently on which is implemented here*/
        for(int space = 1; space <= height - row; space++)
        {
            printf(" ");
        }
        for(int hash = 1; hash <= row; hash++)
        {
            printf("#");
        }
        printf("  ");
        //Makes the right Pyramid
        //As you go down each row, you add one more # each time.
        for (int right = 1; right <= row; right++)
        {
            printf("#");
        }
        printf("\n");
    }
}