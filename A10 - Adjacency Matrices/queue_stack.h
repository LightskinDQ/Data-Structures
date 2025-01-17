/*
 * queue_stack.h
 *
 *  Created on: Jun. 29, 2024
 *      Author: dillonquick
 */

#ifndef QUEUE_STACK_H_
#define QUEUE_STACK_H_

typedef struct node {
	void *data;
	struct node *next;
} NODE;

typedef struct queue {
	NODE *front, *rear;
} QUEUE;

void enqueue(QUEUE *qp, void *data);
void *dequeue(QUEUE *qp);
void clean_queue(QUEUE *qp);

typedef struct stack {
	NODE *top;
} STACK;

void push(STACK *sp, void *data);
void *pop(STACK *sp);
void clean_stack(STACK *sp);


#endif /* QUEUE_STACK_H_ */
