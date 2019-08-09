// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

void destroy(node* node);

// Represents a hash table
node *hashtable[N];

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        // TODO
        node* newWord = (node*)malloc(sizeof(node));
        strcpy(newWord->word, word);
        newWord->next = NULL;

        int index = hash(word);
        if (!hashtable[index]) {
            hashtable[index] = newWord;
        }
        else {
            if (!hashtable[index]) {
                hashtable[index] = newWord;
            }
            else {
                newWord->next = hashtable[index];
                hashtable[index] = newWord;
            }
        }
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int count = 0;
    node* temp;
    for (int i = 0; i < N; i++) {
        temp = hashtable[i];
        while (temp != NULL) {
            count++;
            temp = temp->next;
        }
    }
    return count;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node* temp = hashtable[hash(word)];
    while (temp) {
        if (strcasecmp(word, temp->word) == 0) return true;
        temp = temp->next;
    }
    return false;
}

// Function for unload
void destroy(node* node) {
    if (!node) return;
    else destroy(node->next);
    free(node);
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++) {
        destroy(hashtable[i]);
        hashtable[i] = NULL;
    }
    return true;
}
