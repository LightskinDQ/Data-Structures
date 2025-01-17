/*
 * mystring.h
 *
 *  Created on: May 31, 2024
 *      Author: dillonquick
 */

#ifndef MYSTRING_H_
#define MYSTRING_H_

/**
 * Count the number of words in a given simple string. A word starts with an
 * English charactor ends with a charactor of space, tab, comma, or period.
 *
 * @param s - char pointer to a str
 * @return - return the number of words.
 */
int str_wc(char *s);

/**
 * Change every upper case English letter to its lower case of string passed by s
 *
 * @param s - char pointer to a str
 * @return - return the number of actual flips.
 */
int str_lower(char *s);

/**
 * Remove unnecessary space characters in a simple string passed by `s`
 *
 * @param s - char pointer to a str
 */
void str_trim(char *s);

/**
 * Check if string s1 contains string s2 as substring, return the pointer to
 *  the position of the first matched substring, otherwise NULL value 0.
 *
 * @param s1 - pointer to string s1
 * @param s2 - pointer to string s2
 * @return - char pointer to the first matched substing in s1.
 */
char *str_str(char *s1, char *s2);


#endif /* MYSTRING_H_ */
