/*
 * stack.h
 *
 *  Created on: Jun. 22, 2024
 *      Author: dillonquick
 */

#ifndef STACK_H_
#define STACK_H_
#include "common.h"

typedef struct stack {
  int length;
  NODE *top;
} STACK;

void push(STACK *sp, NODE *np);
NODE *pop(STACK *sp);
void stack_clean(STACK *sp);


#endif /* STACK_H_ */
