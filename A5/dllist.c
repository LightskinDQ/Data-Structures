/*
 * dllist.c
 *
 *  Created on: Jun. 15, 2024
 *      Author: dillonquick
 */

#include <stdio.h>
#include <stdlib.h>
#include "dllist.h"

NODE *new_node(char data) {
  NODE *np = (NODE *)malloc(sizeof(NODE));
  np->data = data;
  np->prev = NULL;
  np->next = NULL;
  return np;
}

void dll_insert_start(DLL *dllp, NODE *np) {
  if (dllp->start == NULL) {
    dllp->start = np;
    dllp->end = np;
  } else {
    np->next = dllp->start;
    dllp->start->prev = np;
    dllp->start = np;
  }
  dllp->length++;
}

void dll_insert_end(DLL *dllp, NODE *np) {
  if (dllp->end == NULL) {
    dllp->start = np;
    dllp->end = np;
  } else {
    np->prev = dllp->end;
    dllp->end->next = np;
    dllp->end = np;
  }
  dllp->length++;
}

void dll_delete_start(DLL *dllp) {
  if (dllp->start == NULL) {
    return;
  }

  NODE *temp = dllp->start;
  if (dllp->start == dllp->end) {
    dllp->start = NULL;
    dllp->end = NULL;
  } else {
    dllp->start = dllp->start->next;
    dllp->start->prev = NULL;
  }
  free(temp);
  dllp->length--;
}

void dll_delete_end(DLL *dllp) {
  if (dllp->end == NULL) {
    return;
  }

  NODE *temp = dllp->end;
  if (dllp->start == dllp->end) {
    dllp->start = NULL;
    dllp->end = NULL;
  } else {
    dllp->end = dllp->end->prev;
    dllp->end->next = NULL;
  }
  free(temp);
  dllp->length--;
}

void dll_clean(DLL *dllp) {
  NODE *current = dllp->start;
  NODE *next_node;

  while (current != NULL) {
    next_node = current->next;
    free(current);
    current = next_node;
  }

  dllp->start = NULL;
  dllp->end = NULL;
  dllp->length = 0;
}


