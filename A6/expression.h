/*
 * expression.h
 *
 *  Created on: Jun. 22, 2024
 *      Author: dillonquick
 */

#ifndef EXPRESSION_H_
#define EXPRESSION_H_
#include "common.h"
#include "queue.h"


QUEUE infix_to_postfix(char *infixstr);

int evaluate_postfix(QUEUE queue);

int evaluate_infix(char *infixstr);

int mypriority(char op);


#endif /* EXPRESSION_H_ */
