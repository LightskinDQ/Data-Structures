/*
 * graph.h
 *
 *  Created on: Jul. 26, 2024
 *      Author: dillonquick
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#define INFINITY 99999

typedef struct adjnode  {
    int nid;
    int weight;
    struct adjnode *next;
} ADJNODE;

typedef struct gnode  {
    int nid;
    char name[10];
    ADJNODE *neighbor;
} GNODE;

typedef struct graph {
    int order;
    int size;
  GNODE **nodes;
} GRAPH;

GRAPH *new_graph(int n);

void insert_edge_graph(GRAPH *g, int from, int to, int weight);

void delete_edge_graph(GRAPH *g, int from, int to);

int get_edge_weight(GRAPH *g, int from, int to);

void traverse_bforder(GRAPH *g, int start);

void traverse_dforder(GRAPH *g, int start);

void graph_clean(GRAPH **gp);

#endif /* GRAPH_H_ */
