/*
 * edgelist.h
 *
 *  Created on: Jul. 26, 2024
 *      Author: dillonquick
 */

#ifndef EDGELIST_H_
#define EDGELIST_H_

typedef struct edgenode {
  int from;
  int to;
  int weight;
  struct edgenode *next;
} EDGENODE;

typedef struct edgelist {
  int size;    
  EDGENODE *start;
  EDGENODE *end;
} EDGELIST;

EDGELIST *new_edgelist();

void insert_edge_start(EDGELIST *g, int from, int to, int weight);

void insert_edge_end(EDGELIST *g, int from, int to, int weight);

void delete_edge(EDGELIST *g, int from, int to);

int edgelist_weight(EDGELIST *g); // Declare it here

void edgelist_clean(EDGELIST **gp);

#endif /* EDGELIST_H_ */
