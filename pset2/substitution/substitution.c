#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    string key = argv[1];
    //Gets valid input
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if(strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    //Checks to see if key is alphabetical
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if(!isalpha(argv[1][i])) //isalpha works on one character at a time.
        {
            printf("Usage: ./substitution key\n");
            return 1;
            break;
        }
    }
    //Finds duplicates
    int count = 0;
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (key[j] == key[i])
            {
            count++;
            }

        }
    }


    if (count != strlen(key))
    {
        printf("Key must not contain repeated characters\n");
        return 1;
    }



    string plaintext = get_string("plaintext: ");

    //Actual ciphering
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isalpha(plaintext[i]))
        {
            if (isupper(plaintext[i]))
            {
                plaintext[i] = toupper(key[plaintext[i] - 65]);

            }
            else if (islower(plaintext[i]))
            {
                plaintext[i] = tolower(key[plaintext[i] - 97]);
            }
            printf("%c", plaintext[i]);
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
    return 0;
}