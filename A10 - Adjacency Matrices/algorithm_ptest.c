/*
 -------------------------------------------------------
 Project:  cp264-a10q3
 File:     algorithm_ptest.c
 About:    public test driver
 Author:   HBF
 Version:  2023-12-18
 -------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "edgelist.h"
#include "graph.h"
#include "algorithm.h"
#include "heap.h"

int order = 5;

typedef struct vertex {
	int nid;
	char name[10];
} VERTEX;

typedef struct edge {
	int from;
	int to;
	int weight;
} EDGE;

VERTEX node_tests[] = { { 0, "A" }, { 1, "B" }, { 2, "C" }, { 3, "D" },
		{ 4, "E" } };

EDGE edge_tests[] = { { 0, 1, 8 }, { 1, 0, 8 }, { 0, 2, 3 }, { 2, 0, 3 }, { 1,
		2, 4 }, { 2, 1, 4 }, { 2, 3, 10 }, { 3, 2, 10 }, { 1, 3, 9 },
		{ 3, 1, 9 }, { 1, 4, 11 }, { 4, 1, 11 } };

GRAPH *g = NULL;


void display_edgelist(EDGELIST *g) {
	if (g == NULL)
		return;
	printf("size %d ", g->size);
	printf("(from to weight) ");
	EDGENODE *p = g->start;
	while (p) {
		printf("(%d %d %d) ", p->from, p->to, p->weight);
		p = p->next;
	}
}

void display_graph(GRAPH *g) {
  if (g ) {
  printf("order %d ", g->order);
  printf("size %d ", g->size);
  printf("(from to weight) ");
  int i;
  ADJNODE *ptr;
  for (i = 0; i < g->order; i++) {
    //printf("\n%d:", g->nodes[i]->nid);
    ptr = g->nodes[i]->neighbor;
    while (ptr != NULL) {
      printf("(%d %d %d) ", i,  ptr->nid, ptr->weight);
      ptr = ptr->next;
    }
  }
  }
}

void test_start() {
	g = new_graph(order);
	int n = sizeof node_tests / sizeof *node_tests;
	for (int i = 0; i < n; i++) {
		if (node_tests[i].nid < order)
			strcpy(g->nodes[node_tests[i].nid]->name, node_tests[i].name);
	}
	n = sizeof edge_tests / sizeof *edge_tests;
	for (int i = 0; i < n; i++) {
		insert_edge_graph(g, edge_tests[i].from, edge_tests[i].to,
				edge_tests[i].weight);
	}

	printf("graph: ");
	display_graph(g);
	printf("\n");
}

void test_end() {
	graph_clean(&g);
}

void test_mst_prim() {
	printf("------------------\n");
	printf("Test: mst_prim\n\n");

	EDGELIST *t = mst_prim(g, 0);

	printf("%s(%d): ", "mst_prim", 0);
	display_edgelist(t);
	printf("\n");

	printf("\nmst weight:%d\n", edgelist_weight(t));

	printf("\n");
}

void test_spt_dijkstra() {
	printf("------------------\n");
	printf("Test: spt_dijkstra\n\n");

	EDGELIST *t = spt_dijkstra(g, 0);

	printf("%s(%d): ", "spt_dijkstra", 0);
	display_edgelist(t);
	printf("\n");

	printf("\nspt weight:%d\n", edgelist_weight(t));

	printf("\n");
}

void test_sp_dijkstra() {
	printf("------------------\n");
	printf("Test: sp_dijkstra\n\n");

	EDGELIST *t = sp_dijkstra(g, 0, 4);

	printf("%s(%d %d): ", "sp_dijkstra", 0, 4);
	display_edgelist(t);
	printf("\n");

	printf("\nsp length:%d\n", edgelist_weight(t));

	printf("\n");
}

int main(int argc, char* args[]) {
	test_start();
	test_mst_prim();
	test_spt_dijkstra();
	test_sp_dijkstra();
	test_end();
	return 0;
}
