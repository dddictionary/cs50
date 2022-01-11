#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    int sum = 0;
    // TODO: Compute and return score for string
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        /*If the letter is uppercase, finds its relative position on the
        points array by subtracting from the letter 'A'.*/
        if (isupper(word[i]))
        {
            int positionUpper = word[i] - 'A';
            sum += POINTS[positionUpper];
        }
        /*If the letter is lowercase, finds its relative position on the
        points array by subtracting from the letter 'a'.*/
        else if (islower(word[i]))
        {
            int positionLower = word[i] - 'a';
            sum += POINTS[positionLower];
        }
    }
    return sum;
}