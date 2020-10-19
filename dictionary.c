/*
 * The Hash Function is a customized version
 * of Dan Bernstein's djb2 algorithm
 * as presented on:
 * http://www.cse.yorku.ca/~oz/hash.html
 */

// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 30000;

// Hash table
node *table[N];

// Number of words variable
unsigned int num_of_words = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // convert word to lower case
    int n = strlen(word);
    char low_word[n];
    strcpy(low_word, word);
    for (int i = 0; i < n; i ++)
    {
        low_word[i] = tolower(low_word[i]);
    }

    // Hash word to obtain a hash value
    unsigned int h = hash(low_word);

    for (node *cursor = table[h]; cursor != NULL; cursor = cursor->next)
    {
        if (strcmp(low_word, cursor->word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash = 381;
    int c;

    while ((c = *word++))
    {
        hash = ((hash << 3) + c) % N;
    }
    return hash;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Reset hash table
    for (unsigned int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Open dictionary file
    FILE* dicptr = fopen(dictionary, "r");
    if (dicptr == NULL)
    {
        printf("Could not open dictionary.\n");
        return false;
    }

    char word[LENGTH + 1];
    // Read strings from file one at a time
    while (fscanf(dicptr, "%s", word) != EOF)
    {
        // Convert word to lower case
        for (int i = 0, len = strlen(word); i < len; i++)
        {
            word[i] = tolower(word[i]);
        }

        // Create a new node for each word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("No available memory on the Heap.\n");
            return false;
        }

        strcpy(n->word, word);

        // Hash word to obtain a hash value
        unsigned int h = hash(word);

        // Insert node into hash table at that location
        n->next = table[h];
        table[h] = n;
        num_of_words++;
    }
    fclose(dicptr);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return num_of_words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (unsigned int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            node* tmp = table[i];
            node* cursor = table[i];

            while (cursor != NULL)
            {
                cursor = cursor->next;
                free(tmp);
                tmp = cursor;
            }

            if (cursor != NULL)
            {
                return false;
            }
        }
    }
    return true;
}
