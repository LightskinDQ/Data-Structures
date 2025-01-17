/*
 * expression_symbol.h
 *
 *  Created on: Jul. 13, 2024
 *      Author: dillonquick
 */

#ifndef EXPRESSION_SYMBOL_H_
#define EXPRESSION_SYMBOL_H_

#include "common_queue_stack.h"
#include "hash.h"

QUEUE infix_to_postfix_symbol(HASHTABLE *ht, char *infixstr);

int evaluate_infix_symbol(HASHTABLE *ht, char *infixstr);

int evaluate_postfix(QUEUE queue);

HASHDATA evaluate_statement(HASHTABLE *ht, char* statement);

int mypriority(char op);


#endif /* EXPRESSION_SYMBOL_H_ */
