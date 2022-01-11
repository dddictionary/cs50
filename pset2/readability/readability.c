#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


int count_letters(string text);
float count_words(string text);
int count_sentences(string text);
float index(string text);


int main(void)
{
    string input = get_string("Text: ");
    int grade = round(index(input));
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

//Finds the number of letters in the input
int count_letters(string text)
{
    int n = strlen(text);
    int c = 0;
    for (int i = 0; i < n; i++)
    {
        if (isalpha(text[i]))
        {
            c++;
        }
    }
    return c;
}

//Finds hte number oif words
float count_words(string text)
{
    int n = strlen(text);
    int words = 1;
    for (int i = 0; i < n; i++)
    {
        if (text[i] == ' ')
        words++;
    }
    return words;
}

//Count the number of sentences
int count_sentences(string text)
{
    int n = strlen(text);
    int sentences = 0;
    for (int i = 0; i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }
    return sentences;
}

//Determine the grade level. index = 0.0588 * L - 0.296 * S - 15.8
float index(string text)
{
    float grade = 0;
    float L, S;
    //L is the average number of letters per 100 words in the text
    L = count_letters(text) * 100 / count_words(text);

    //S is the average number of sentences per 100 words in the text
    S = count_sentences(text) * 100 / count_words(text);

    //Find the grade level
    grade = 0.0588 * L - 0.296 * S - 15.8;

    return grade;
}