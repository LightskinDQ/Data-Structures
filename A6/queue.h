/*
 * queue.h
 *
 *  Created on: Jun. 22, 2024
 *      Author: dillonquick
 */

#ifndef QUEUE_H_
#define QUEUE_H_
#include "common.h"

typedef struct queue {
  int length;
  NODE *front;
  NODE *rear;
} QUEUE;

void enqueue(QUEUE *qp, NODE *np);
NODE *dequeue(QUEUE *qp);
void queue_clean(QUEUE *qp);



#endif /* QUEUE_H_ */
