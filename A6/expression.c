/*
 * expression.c
 *
 *  Created on: Jun. 22, 2024
 *      Author: dillonquick
 */
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "queue.h"
#include "stack.h"
#include "expression.h"

QUEUE infix_to_postfix(char *infixstr) {
    STACK operator_stack = {0, NULL};
    QUEUE output_queue = {0, NULL, NULL};
    char *ptr = infixstr;
    NODE *node;

    while (*ptr != '\0') {
        int type = mytype(*ptr);

        if (type == 0) {  // Operand
            node = new_node(*ptr - '0', 0);
            enqueue(&output_queue, node);
        } else if (type == 1) {  // Operator
            while (operator_stack.length > 0 && mypriority(operator_stack.top->data) >= mypriority(*ptr)) {
                node = pop(&operator_stack);
                enqueue(&output_queue, node);
            }
            node = new_node(*ptr, 1);
            push(&operator_stack, node);
        } else if (type == 2) {  // Left parenthesis
            node = new_node(*ptr, 2);
            push(&operator_stack, node);
        } else if (type == 3) {  // Right parenthesis
            while (operator_stack.length > 0 && operator_stack.top->type != 2) {
                node = pop(&operator_stack);
                enqueue(&output_queue, node);
            }
            if (operator_stack.length > 0 && operator_stack.top->type == 2) {
                node = pop(&operator_stack);
                free(node);
            }
        }
        ptr++;
    }

    while (operator_stack.length > 0) {
        node = pop(&operator_stack);
        enqueue(&output_queue, node);
    }

    return output_queue;
}

int evaluate_postfix(QUEUE queue) {
    STACK evaluation_stack = {0, NULL};
    NODE *node;
    int operand1, operand2, result;

    while (queue.length > 0) {
        node = dequeue(&queue);

        if (node->type == 0) {
            push(&evaluation_stack, node);
        } else if (node->type == 1) {
            operand2 = pop(&evaluation_stack)->data;
            operand1 = pop(&evaluation_stack)->data;

            switch (node->data) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    result = operand1 / operand2;
                    break;
                case '%':
                    result = operand1 % operand2;
                    break;
                default:
                    result = 0;
            }
            NODE *result_node = new_node(result, 0);
            push(&evaluation_stack, result_node);
            free(node);
        }
    }

    result = pop(&evaluation_stack)->data;
    stack_clean(&evaluation_stack);

    return result;
}

int evaluate_infix(char *infixstr) {
    QUEUE postfix_queue = infix_to_postfix(infixstr);
    int result = evaluate_postfix(postfix_queue);
    queue_clean(&postfix_queue);
    return result;
}

int mypriority(char op) {
    int r = -1;
    if (op == '/' || op == '*' || op == '%')
        r = 1;
    else if (op == '+' || op == '-')
        r = 0;

    return r;
}


