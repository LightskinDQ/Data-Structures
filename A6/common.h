/*
 * common.h
 *
 *  Created on: Jun. 22, 2024
 *      Author: dillonquick
 */

#ifndef COMMON_H_
#define COMMON_H_

/*
 * Node structure of linked list queue and stack for postfix expression operations
 * int type - 0:operand; 1:operator; 2:left parenthesis 3:right parenthesis
 * int data - represent operand, operator, or parenthesis according to the type
 * struct node *next - pinter to the next node of the linked list
 */
typedef struct node {
	int type;
	int data;
	struct node *next;
} NODE;

NODE *new_node(int data, int type);
void clean(NODE **npp);
void display(NODE *np);
/**
 * Determines the type of a char character, from a1q1
 *
 * @param c - char type
 * @return - 0 if c is a digit
             1 if c is an arithmetic operator
             2 if c is the left parenthsis (
             3 if c is the right parenthsis )
             4 if c is an English letter;
             otherwise -1.
 */
int mytype(char c);


#endif /* COMMON_H_ */
