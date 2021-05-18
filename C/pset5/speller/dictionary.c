// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"




typedef struct node                                          // Represents a node in a hash table
{
    char word[LENGTH + 1];
    struct node *next;
}
node;



const int N = 5381;                                // Number of buckets in hash table
node *table[N];                                     // Hash table

unsigned long wordcount = 0;                        // Keep track of number of words in dictionary
unsigned long hash_function(char *str);             // Hash function prototype





bool check(const char *word)                        // Returns true if word is in dictionary else false
{

    int length = strlen(word);                      // Change letters to lowercase
    char copy[length + 1];                          // initialise lower case word called copy

    for (int i = 0 ; i < length + 1 ; i++)
    {
        copy[i] = tolower(word[i]);
    }

    unsigned long copy_index = hash_function(copy);           // copy_index is the hash value for the hash word(copy)

    node *cursor = table[copy_index];            // Set cursor to start pointing to head
    if (cursor == NULL)
    {
        return false;
    }


    while (cursor != NULL)                          // Traverse list, looking for word in dictionary
    {
        if (strcasecmp(copy, cursor -> word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor -> next;
        }
    }


    return false;
}




bool load(const char *dictionary)                   // Loads dictionary into memory, returning true if successful else false
{

    FILE *file =  fopen(dictionary, "r");
    if (file == NULL)
    {
        fprintf(stderr, "File does not exist \n");
        return false;
    }
    
    
    
    char buffer[LENGTH + 1];
    while (fscanf(file, "%s", buffer) != EOF)
    {
        //fscanf(file,"%s",buffer);
        node *n = malloc(sizeof(node));             // Create a new node for each word, allocate memory
        if (n == NULL)
        {
            unload();
            fprintf(stderr, "Out of memory \n");
            return false;
        }
        else
        {
            strcpy(n->word, buffer);                    // Copy word into node using strcpy
     
            int index = hash_function(n->word);          // Call hash function to return hash value(index) for hash word
     
            if (table[index] == NULL)                   // Check if already some word written in same bucket
            {
                table[index] = n;
            }
            else
            {
                n -> next = table[index];
                table[index] = n;
            } 
        }
    
        wordcount++;
    }
    
    fclose(file);
    return true;
}




unsigned int size(void)                             // Returns number of words in dictionary if loaded, else 0 if not yet loaded
{

    return wordcount;
}




bool unload(void)                                   // Unloads dictionary from memory, returning true if successful else false
{
    // iterate through hashtable
    for (int i = 0; i < N; i++)
    {
        // set pointer to head of list
        node *cursor = table[i];

        // traverse list
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
        free(cursor);
    }
    return true;
}



//Hash words(strings) to obtain hash value(index)
unsigned long hash_function(char *str)              // Hash function from http://www.cse.yorku.ca/~oz/hash.html
{
    unsigned long hash = 5381;
    int c = 0;

    while (c == (*str++))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
        

    return hash;
}
