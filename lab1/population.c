#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    /*Make an int called start that asks for a starting
    population which only takes in values bigger than 9*/
    int start;
    do
    {
        start = get_int("Start size: ");
    }
    while(start < 9);


    // TODO: Prompt for end size
    /*Make a int called end that takes in the ending
    population and only takes in values if it is bigger than start*/

    int end;
    do
    {
        end = get_int("End size: ");
    }
    while(end < start);

    // TODO: Calculate number of years until we reach threshold
    int years = 0;
    while(start < end)
    {
        start = start + (start / 3) - (start / 4);
        years++;
    }

    // TODO: Print number of years

    printf("Years: %i\n", years);
}


