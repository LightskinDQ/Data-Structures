/*
-------------------------------------------------------
File:     edgelist_ptest.c
About:    public test driver
Author:   HBF
Version:  2024-05-24
-------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include "edgelist.h"


typedef struct edge {
  int from;
  int to;
  int weight;
} EDGE;

EDGE tests[] = {
{0, 2, 3},
{2, 1, 4},
{1, 3, 9},
{1, 4, 11}
};

EDGE delete_tests[] ={ {2, 1, 4}, {1, 3, 9}, {1, 4, 11}, {0, 2, 3}};

EDGELIST *elg = NULL;


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

void delete_edges(EDGELIST *g) {
  EDGENODE *temp, *p = g->start;
  while (p) {
    temp = p;
    p = p->next;
    free(temp);
  }
  g->start = NULL;
  g->end = NULL;
  g->size = 0;
}

void test_new_edgelist() {
	printf("------------------\n");
	printf("Test: new_edgelist\n\n");
	elg = new_edgelist();
	printf("%s(): ", "new_edgelist");
	display_edgelist(elg);
	printf("\n");
}

void test_insert_edge_start() {
	printf("------------------\n");
	printf("Test: insert_edge_start\n\n");
	int n = sizeof tests / sizeof *tests;
	for (int i=0; i<n; i++) {
		insert_edge_start(elg, tests[i].from, tests[i].to, tests[i].weight);
		printf("%s(%d %d %d): ", "insert_edge_start", tests[i].from, tests[i].to, tests[i].weight);
		display_edgelist(elg);
		printf("\n");
	}
	printf("\n");
	delete_edges(elg);
}

void test_insert_edge_end() {
	printf("------------------\n");
	printf("Test: insert_edge_end\n\n");
	int n = sizeof tests / sizeof *tests;
	for (int i=0; i<n; i++) {
		insert_edge_end(elg, tests[i].from, tests[i].to, tests[i].weight);
		printf("%s(%d %d %d): ", "insert_edge_end", tests[i].from, tests[i].to, tests[i].weight);
		display_edgelist(elg);
		printf("\n");
	}
	printf("\n");
	delete_edges(elg);
}

void test_delete_edge() {
	printf("------------------\n");
	printf("Test: delete_edge\n\n");

	int n = sizeof tests / sizeof *tests;
	for (int i=0; i<n; i++) {
		insert_edge_end(elg, tests[i].from, tests[i].to, tests[i].weight);
	}
	printf("before delete: ");
		display_edgelist(elg);
		printf("\n");

	n = sizeof delete_tests / sizeof *delete_tests;
	for (int i=0; i<n; i++) {
		delete_edge(elg, delete_tests[i].from, delete_tests[i].to);
		printf("%s(%d %d): ", "delete_edge", delete_tests[i].from, delete_tests[i].to);
		display_edgelist(elg);
		printf("\n");
	}

	delete_edges(elg);
	printf("\n");
}

void test_edgelist_weight() {
	printf("------------------\n");
	printf("Test: edgelist_weight\n\n");

	int n = sizeof tests / sizeof *tests;
	for (int i=0; i<n; i++) {
		insert_edge_end(elg, tests[i].from, tests[i].to, tests[i].weight);
	}
	printf("edgelist graph: ", edgelist_weight(elg));
	display_edgelist(elg);
	printf("\n");
	printf("%s(): %d", "weight_edgelis", edgelist_weight(elg));
	delete_edges(elg);
	printf("\n");
}

int main(){
	test_new_edgelist();
	test_insert_edge_start();
	test_insert_edge_end();
	test_delete_edge();
	test_edgelist_weight();
	edgelist_clean(&elg);
  return 0;
}