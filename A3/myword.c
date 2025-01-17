/*
 * myword.c
 *
 *  Created on: May 31, 2024
 *      Author: dillonquick
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Define enumeration type BOOLEAN with value FALSE = 0 and TRUE = 1.
typedef enum { FALSE, TRUE } BOOLEAN;

// Define structure type WORD
typedef struct {
    char word[20];
    int count;
} WORD;

// Define structure type WORDSTATS
typedef struct {
    int line_count;
    int word_count;
    int keyword_count;
} WORDSTATS;

// Function to load word data from file and insert words into a dictionary
int create_dictionary(FILE *fp, char *dictionary) {
    int word_count = 0;
    char word[20];
    while (fscanf(fp, "%s", word) != EOF) {
        strcat(dictionary, word);
        strcat(dictionary, " ");
        word_count++;
    }
    return word_count;
}

// Function to determine if a given word is contained in the given dictionary
BOOLEAN contain_word(char *dictionary, char *word) {
    char *found = strstr(dictionary, word);
    if (found) {
        // Check if the found word is a separate word in the dictionary
        if ((found == dictionary || isspace(*(found - 1))) && isspace(*(found + strlen(word)))) {
            return TRUE;
        }
    }
    return FALSE;
}

// Function to process text data from a file for word statistics
WORDSTATS process_words(FILE *fp, WORD *words, char *dictionary) {
    WORDSTATS stats = {0, 0, 0};
    char line[256];
    char word[20];
    int found;

    while (fgets(line, sizeof(line), fp)) {
        stats.line_count++;
        char *token = strtok(line, " \t\n,.");
        while (token != NULL) {
            stats.word_count++;
            if (!contain_word(dictionary, token)) {
                found = 0;
                for (int i = 0; i < stats.keyword_count; i++) {
                    if (strcmp(words[i].word, token) == 0) {
                        words[i].count++;
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    strcpy(words[stats.keyword_count].word, token);
                    words[stats.keyword_count].count = 1;
                    stats.keyword_count++;
                }
            }
            token = strtok(NULL, " \t\n,.");
        }
    }
    return stats;
}


