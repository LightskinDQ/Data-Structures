/*
 * myrecord_sllist.c
 *
 *  Created on: Jun. 15, 2024
 *      Author: dillonquick
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char name[40];
  float score;
} RECORD;

typedef struct node {
  RECORD data;
  struct node *next;
} NODE;

typedef struct sllist {
  int length;
  NODE *start;
} SLL;

NODE *sll_search(SLL *sllp, char *name) {
  NODE *current = sllp->start;
  while (current != NULL) {
    if (strcmp(current->data.name, name) == 0) {
      return current;
    }
    current = current->next;
  }
  return NULL;
}

void sll_insert(SLL *sllp, char *name, float score) {
  NODE *new_node = (NODE *)malloc(sizeof(NODE));
  strcpy(new_node->data.name, name);
  new_node->data.score = score;
  new_node->next = NULL;

  if (sllp->start == NULL || strcmp(sllp->start->data.name, name) > 0) {
    new_node->next = sllp->start;
    sllp->start = new_node;
  } else {
    NODE *current = sllp->start;
    while (current->next != NULL && strcmp(current->next->data.name, name) < 0) {
      current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;
  }
  sllp->length++;
}

int sll_delete(SLL *sllp, char *name) {
  if (sllp->start == NULL) {
    return 0;
  }

  NODE *current = sllp->start;
  NODE *previous = NULL;

  while (current != NULL && strcmp(current->data.name, name) != 0) {
    previous = current;
    current = current->next;
  }

  if (current == NULL) {
    return 0;
  }

  if (previous == NULL) {
    sllp->start = current->next;
  } else {
    previous->next = current->next;
  }

  free(current);
  sllp->length--;
  return 1;
}

void sll_clean(SLL *sllp) {
  NODE *current = sllp->start;
  NODE *next_node;

  while (current != NULL) {
    next_node = current->next;
    free(current);
    current = next_node;
  }

  sllp->start = NULL;
  sllp->length = 0;
}

