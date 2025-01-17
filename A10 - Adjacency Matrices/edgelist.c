/*
 * edgelist.c
 *
 *  Created on: Jul. 26, 2024
 *      Author: dillonquick
 */


#include "edgelist.h"
#include <stdlib.h>

EDGELIST *new_edgelist() {
    EDGELIST *tp = malloc(sizeof(EDGELIST));
    tp->size = 0;
    tp->start = NULL;
    tp->end = NULL;
    return tp;
}

void insert_edge_end(EDGELIST *g, int from, int to, int weight) {
    EDGENODE *new_node = malloc(sizeof(EDGENODE));
    new_node->from = from;
    new_node->to = to;
    new_node->weight = weight;
    new_node->next = NULL;
    
    if (g->size == 0) {
        g->start = new_node;
    } else {
        g->end->next = new_node;
    }
    g->end = new_node;
    g->size++;
}

void insert_edge_start(EDGELIST *g, int from, int to, int weight) {
    EDGENODE *new_node = malloc(sizeof(EDGENODE));
    new_node->from = from;
    new_node->to = to;
    new_node->weight = weight;
    new_node->next = g->start;
    
    g->start = new_node;
    if (g->size == 0) {
        g->end = new_node;
    }
    g->size++;
}

void delete_edge(EDGELIST *g, int from, int to) {
    EDGENODE *current = g->start;
    EDGENODE *previous = NULL;
    
    while (current) {
        if (current->from == from && current->to == to) {
            if (previous) {
                previous->next = current->next;
            } else {
                g->start = current->next;
            }
            if (current == g->end) {
                g->end = previous;
            }
            free(current);
            g->size--;
            return;
        }
        previous = current;
        current = current->next;
    }
}

int edgelist_weight(EDGELIST *g) {
    int total_weight = 0;
    EDGENODE *current = g->start;
    
    while (current) {
        total_weight += current->weight;
        current = current->next;
    }
    return total_weight;
}

void edgelist_clean(EDGELIST **gp) {
    EDGELIST *g = *gp;
    EDGENODE *temp, *p = g->start;
    
    while (p) {
        temp = p;
        p = p->next;
        free(temp);
    }
    free(g);
    *gp = NULL;
}
