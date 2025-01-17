/*
 * mychar.c
 *
 *  Created on: May 15, 2024
 *      Author: dillonquick
 */

// your program signature

#include "mychar.h"

int mytype(char c) {
    if (c >= '0' && c <= '9') { 
        return 0;
    } 

    else if (c == '+' || c == '-' || c == '*' || c == '/') { 
        return 1;
    } 

    else if (c == '(') { 
        return 2;
    } 

    else if (c == ')') { 
        return 3;
    } 

    else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) { 
        return 4;
    } 

    else { 
        return -1;
    }
}

char case_flip(char c) {
    if (c >= 'a' && c <= 'z') { 
        return c - 32; 

    } 
    else if (c >= 'A' && c <= 'Z') { 
        return c + 32; 
    } 

    else { 
        return c;
    }
}

int digit_char_to_int(char c) {
    return c - 'O';
}


