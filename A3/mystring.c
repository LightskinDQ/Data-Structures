/*
 * mystring.c
 *
 *  Created on: May 31, 2024
 *      Author: dillonquick
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Function to count the number of words in a given string
int str_wc(char *s) {
    int count = 0;
    int inWord = 0;

    while (*s) {
        if (isalpha(*s)) {
            if (!inWord) {
                count++;
                inWord = 1;
            }
        } else if (*s == ' ' || *s == '\t' || *s == ',' || *s == '.') {
            inWord = 0;
        }
        s++;
    }
    return count;
}

// Function to change every upper case English letter to its lower case
int str_lower(char *s) {
    int flips = 0;
    while (*s) {
        if (isupper(*s)) {
            *s = tolower(*s);
            flips++;
        }
        s++;
    }
    return flips;
}

// Function to remove unnecessary space characters in a simple string
void str_trim(char *s) {
    char *d = s; // Destination pointer to construct the trimmed string
    int inSpace = 0;

    while (*s) {
        if (*s == ' ' || *s == '\t') {
            if (!inSpace) {
                *d++ = ' ';
                inSpace = 1;
            }
        } else {
            *d++ = *s;
            inSpace = 0;
        }
        s++;
    }
    *d = '\0'; // Null-terminate the trimmed string
}

// Function to check if string s1 contains string s2 as substring
char *str_str(char *s1, char *s2) {
    return strstr(s1, s2);
}

