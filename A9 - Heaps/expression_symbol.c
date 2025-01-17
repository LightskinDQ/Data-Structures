/*
 * expression_symbol.c
 *
 *  Created on: Jul. 13, 2024
 *      Author: dillonquick
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common_queue_stack.h"
#include "expression_symbol.h"
#include "hash.h"

QUEUE infix_to_postfix_symbol(HASHTABLE *ht, char *infixstr) {
    QUEUE queue = {0};
    STACK stack = {0};
    char *p = infixstr;
    int sign = 1;
    int num = 0;
    char symbol[20] = {0};

    while (*p) {
        if (*p == '-' && (p == infixstr || *(p-1) == '(')) {
            sign = -1;
        }
        else if (mytype(*p) == 0) {
            num = *p-'0';
            while ((*(p+1) >= '0' && *(p+1) <= '9')) {
                num = num*10 + *(p+1)-'0';
                p++;
            }
            enqueue(&queue, new_node(sign*num, 0));
            sign = 1;
        }
        else if (mytype(*p) == 2) { // p*== '('
            push(&stack, new_node('(', 2));
        }
        else if (mytype(*p) == 3) {  // p*== ')'
            while (stack.top){
                if (stack.top->type == 2) {
                    free(pop(&stack));
                    break;
                }
                enqueue(&queue, pop(&stack));
            }
        } else if (mytype(*p) == 1)  {
            while (stack.top && stack.top->type==1 && mypriority(stack.top->data) >= mypriority(*p))
                enqueue(&queue, pop(&stack));
            push(&stack, new_node(*p, 1));
        }
        else if (mytype(*p) == 4) {
            // scan to get the symbol
            int i = 0;
            while (mytype(*p) == 4 && i < 19) {
                symbol[i++] = *p++;
            }
            symbol[i] = '\0';
            p--;

            // get the value of the symbol from the hash table
            HASHNODE *node = hashtable_search(ht, symbol);
            if (node) {
                enqueue(&queue, new_node(node->value, 0));
            } else {
                fprintf(stderr, "Undefined symbol: %s\n", symbol);
                exit(1);
            }
        }
        p++;
    }

    while (stack.top) {
        enqueue(&queue, pop(&stack));
    }

    return queue;
}

int evaluate_infix_symbol(HASHTABLE *ht, char *infixstr) {
    QUEUE postfix_queue = infix_to_postfix_symbol(ht, infixstr);
    return evaluate_postfix(postfix_queue);
}

int evaluate_postfix(QUEUE queue) {
    STACK stack = {0};
    NODE *node;

    while (queue.front) {
        node = dequeue(&queue);
        if (node->type == 0) { // operand
            push(&stack, node);
        } else if (node->type == 1) { // operator
            int b = pop(&stack)->data;
            int a = pop(&stack)->data;
            int result;

            switch (node->data) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': result = a / b; break;
                default: result = 0;
            }
            push(&stack, new_node(result, 0));
            free(node);
        }
    }
    int final_result = pop(&stack)->data;
    return final_result;
}

HASHDATA evaluate_statement(HASHTABLE *ht, char* statement) {
    HASHDATA hd = {0};
    char line[80] = {0};
    strcpy(line, statement);
    char *p = line, *dp = line;
    while (*p) {
        if (*p != ' ') {
            *dp = *p;
            dp++;
        }
        p++;
    }
    char name[20] = {0};
    char *eqp = strstr(line, "=");
    if (eqp) {
        //*eqp='\0'; strcpy(name, line);
        for (p = line, dp = name; p != eqp; p++)
            *dp = *p;
        if ((name[0] >= 'a' && name[0] <= 'z') || (name[0] >= 'A' && name[0] <= 'Z')) {
            int value = evaluate_infix_symbol(ht, eqp + 1);
            hashtable_insert(ht, name, value);
            strcpy(hd.key, name);
            hd.value = value;
        }
    } else {
        strcpy(name, line);
        if ((name[0] >= 'a' && name[0] <= 'z') || (name[0] >= 'A' && name[0] <= 'Z')) {
            HASHNODE *hnp = hashtable_search(ht, name);
            if (hnp) {
                strcpy(hd.key, name);
                hd.value = hnp->value;
            }
        }
    }
    return hd;
}

int mypriority(char op) {
    int r = -1;
    if (op == '/' || op == '*' || op == '%')
        r = 1;
    else if (op == '+' || op == '-')
        r = 0;

    return r;
}

