/*
 * graph.c
 *
 *  Created on: Jul. 26, 2024
 *      Author: dillonquick
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue_stack.h"
#include "graph.h"

GRAPH *new_graph(int order) {
    GRAPH *gp = malloc(sizeof(GRAPH));
    gp->nodes = malloc(order * sizeof(GNODE*));
    
    for (int i = 0; i < order; i++) {
        gp->nodes[i] = malloc(sizeof(GNODE));
        gp->nodes[i]->nid = i;
        strcpy(gp->nodes[i]->name, "null");
        gp->nodes[i]->neighbor = NULL;
    }
    
    gp->order = order;
    gp->size = 0;  // Initialize size to 0
    
    return gp;
}

void insert_edge_graph(GRAPH *g, int from, int to, int weight) {
    ADJNODE *new_node = malloc(sizeof(ADJNODE));
    new_node->nid = to;
    new_node->weight = weight;
    new_node->next = NULL;

    ADJNODE *current = g->nodes[from]->neighbor;
    ADJNODE *prev = NULL;

    while (current != NULL && current->nid != to) {
        prev = current;
        current = current->next;
    }

    if (current != NULL) {
        current->weight = weight; // Update weight if edge exists
        free(new_node);
    } else {
        if (prev == NULL) {
            g->nodes[from]->neighbor = new_node;
        } else {
            prev->next = new_node;
        }
        g->size++;  // Increment the size when a new edge is added
    }
}

void delete_edge_graph(GRAPH *g, int from, int to) {
    ADJNODE *current = g->nodes[from]->neighbor;
    ADJNODE *prev = NULL;

    while (current != NULL && current->nid != to) {
        prev = current;
        current = current->next;
    }

    if (current != NULL) {
        if (prev == NULL) {
            g->nodes[from]->neighbor = current->next;
        } else {
            prev->next = current->next;
        }
        free(current);
        g->size--;  // Decrement the size when an edge is removed
    }
}

int get_edge_weight(GRAPH *g, int from, int to) {
    ADJNODE *current = g->nodes[from]->neighbor;

    while (current != NULL) {
        if (current->nid == to) {
            return current->weight;
        }
        current = current->next;
    }
    return -1; // Assuming -1 indicates INFINITY
}

void traverse_bforder(GRAPH *g, int nid) {
    int visited[g->order];
    for (int i = 0; i < g->order; i++) {
        visited[i] = 0;
    }

    QUEUE q = {NULL, NULL};
    enqueue(&q, &nid);
    visited[nid] = 1;

    while (q.front != NULL) { // Check if queue is not empty
        int *node = (int *)dequeue(&q);
        printf("(%d %s) ", *node, g->nodes[*node]->name);

        ADJNODE *neighbor = g->nodes[*node]->neighbor;
        while (neighbor != NULL) {
            if (!visited[neighbor->nid]) {
                enqueue(&q, &(neighbor->nid));
                visited[neighbor->nid] = 1;
            }
            neighbor = neighbor->next;
        }
    }
    clean_queue(&q);
}

void traverse_dforder(GRAPH *g, int nid) {
    int visited[g->order];
    for (int i = 0; i < g->order; i++) {
        visited[i] = 0;
    }

    STACK s = {NULL};
    push(&s, &nid);

    while (s.top != NULL) { // Check if stack is not empty
        int *node = (int *)pop(&s);
        if (!visited[*node]) {
            printf("(%d %s) ", *node, g->nodes[*node]->name);
            visited[*node] = 1;

            ADJNODE *neighbor = g->nodes[*node]->neighbor;
            while (neighbor != NULL) {
                if (!visited[neighbor->nid]) {
                    push(&s, &(neighbor->nid));
                }
                neighbor = neighbor->next;
            }
        }
    }
    clean_stack(&s);
}

void graph_clean(GRAPH **gp) {
    int i;
    GRAPH *g = *gp;
    ADJNODE *temp, *ptr;
    for (i = 0; i < g->order; i++) {
        ptr = g->nodes[i]->neighbor;
        while (ptr != NULL) {
            temp = ptr;
            ptr = ptr->next;
            free(temp);
        }
        free(g->nodes[i]);
    }
    free(g->nodes);
    free(g);
    *gp = NULL;
}
