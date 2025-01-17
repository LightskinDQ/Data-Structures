/*
 * stack.c
 *
 *  Created on: Jun. 22, 2024
 *      Author: dillonquick
 */
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void push(STACK *sp, NODE *np) {
    if (sp->top == NULL) {
        sp->top = np;
    } else {
        np->next = sp->top;
        sp->top = np;
    }
    sp->length++;
}

NODE *pop(STACK *sp) {
    if (sp->top == NULL) {
        return NULL;
    }

    NODE *temp = sp->top;
    sp->top = sp->top->next;

    sp->length--;
    temp->next = NULL;
    return temp;
}

void stack_clean(STACK *sp) {
    NODE *current = sp->top;
    NODE *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    sp->top = NULL;
    sp->length = 0;
}


