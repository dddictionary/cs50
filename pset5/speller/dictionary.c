// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

unsigned int count_size = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 5612;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);
    //cursor has to be a node in order to use cursor = cursor->next
    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor -> word, word) == 0)
        {
            return true;
        }
        cursor = cursor -> next;
    }
    return false;
}

// Hashes word to a number

//this is the djb2 hash function taken from: http://www.cse.yorku.ca/~oz/hash.html
unsigned int hash(const char *word)
{
    // TODO
    unsigned int hashNum = 5381;
    int c;

    while ((c = tolower(*word++)))
    {
        hashNum = ((hashNum << 5) + hashNum) + c; /* hashNum * 33 + c */
        hashNum = hashNum % N;
    }
    return hashNum;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    //open the dictionary
    FILE *load_dict = fopen(dictionary, "r");
    if (load_dict == NULL)
    {
        return false;
    }
    //scan throug hdictionary
    char dictword[LENGTH + 1];
    while (fscanf(load_dict, "%s", dictword) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        //copy string to node
        strcpy(n -> word, dictword);
        n -> next = NULL;

        //insert into hash table
        int index = hash(dictword);

        //if the current spot in the hash table is not taken, put the word there
        if (table[index] == NULL)
        {
            table[index] = n;
        }
        else //else if the spot is taken, insert the word to the front of that has table index.
        {
            n -> next = table[index];
            table[index] = n;
        }

        count_size++; //for size function below.
    }
    fclose(load_dict);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return count_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i] ->next;
            free(table[i]);
            table[i] = tmp;
        }

    }
    return true;
}
