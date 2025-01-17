/*
 * queue.c
 *
 *  Created on: Jun. 22, 2024
 *      Author: dillonquick
 */
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void enqueue(QUEUE *qp, NODE *np) {
    if (qp->rear == NULL) {
        qp->front = qp->rear = np;
    } else {
        qp->rear->next = np;
        qp->rear = np;
    }
    qp->length++;
}

NODE *dequeue(QUEUE *qp) {
    if (qp->front == NULL) {
        return NULL;
    }

    NODE *temp = qp->front;
    qp->front = qp->front->next;

    if (qp->front == NULL) {
        qp->rear = NULL;
    }

    qp->length--;
    temp->next = NULL;
    return temp;
}

void queue_clean(QUEUE *qp) {
    NODE *current = qp->front;
    NODE *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    qp->front = qp->rear = NULL;
    qp->length = 0;
}


