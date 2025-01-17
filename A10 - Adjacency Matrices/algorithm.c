/*
 * algorithm.c
 *
 *  Created on: Jul. 27, 2024
 *      Author: dillonquick
 */


#include <stdio.h>
#include <stdlib.h>
#include "algorithm.h"
#include "heap.h"
#include "edgelist.h"

#define INF 1000000

EDGELIST *mst_prim(GRAPH *g, int start) {
    EDGELIST *mst = new_edgelist();
    int *key = malloc(g->order * sizeof(int));
    int *parent = malloc(g->order * sizeof(int));
    int *inMST = malloc(g->order * sizeof(int));

    for (int i = 0; i < g->order; i++) {
        key[i] = INF;
        parent[i] = -1;
        inMST[i] = 0;
    }

    HEAP *minHeap = new_heap(g->order); // specify capacity
    HEAPDATA hd = {key[start], start};
    heap_insert(minHeap, hd);

    key[start] = 0;

    while (minHeap->size > 0) {
        HEAPDATA minData = heap_extract_min(minHeap);
        int u = minData.value;
        inMST[u] = 1;

        ADJNODE *adj = g->nodes[u]->neighbor;
        while (adj != NULL) {
            int v = adj->nid;
            int weight = adj->weight;

            if (!inMST[v] && key[v] > weight) {
                key[v] = weight;
                parent[v] = u;
                HEAPDATA hd = {key[v], v};
                heap_insert(minHeap, hd);
            }
            adj = adj->next;
        }
    }

    for (int i = 1; i < g->order; i++) {
        if (parent[i] != -1) {
            insert_edge_end(mst, parent[i], i, key[i]);
        }
    }

    free(key);
    free(parent);
    free(inMST);
    heap_clean(&minHeap);

    return mst;
}

EDGELIST *spt_dijkstra(GRAPH *g, int start) {
    EDGELIST *spt = new_edgelist();
    int *dist = malloc(g->order * sizeof(int));
    int *parent = malloc(g->order * sizeof(int));
    int *visited = malloc(g->order * sizeof(int));

    for (int i = 0; i < g->order; i++) {
        dist[i] = INF;
        parent[i] = -1;
        visited[i] = 0;
    }

    HEAP *minHeap = new_heap(g->order); // specify capacity
    HEAPDATA hd = {dist[start], start};
    heap_insert(minHeap, hd);

    dist[start] = 0;

    while (minHeap->size > 0) {
        HEAPDATA minData = heap_extract_min(minHeap);
        int u = minData.value;
        visited[u] = 1;

        ADJNODE *adj = g->nodes[u]->neighbor;
        while (adj != NULL) {
            int v = adj->nid;
            int weight = adj->weight;

            if (!visited[v] && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                HEAPDATA hd = {dist[v], v};
                heap_insert(minHeap, hd);
            }
            adj = adj->next;
        }
    }

    for (int i = 1; i < g->order; i++) {
        if (parent[i] != -1) {
            insert_edge_end(spt, parent[i], i, dist[i] - dist[parent[i]]);
        }
    }

    free(dist);
    free(parent);
    free(visited);
    heap_clean(&minHeap);

    return spt;
}

EDGELIST *sp_dijkstra(GRAPH *g, int start, int end) {
    EDGELIST *sp = new_edgelist();
    int *dist = malloc(g->order * sizeof(int));
    int *parent = malloc(g->order * sizeof(int));
    int *visited = malloc(g->order * sizeof(int));

    for (int i = 0; i < g->order; i++) {
        dist[i] = INF;
        parent[i] = -1;
        visited[i] = 0;
    }

    HEAP *minHeap = new_heap(g->order); // specify capacity
    HEAPDATA hd = {dist[start], start};
    heap_insert(minHeap, hd);

    dist[start] = 0;

    while (minHeap->size > 0) {
        HEAPDATA minData = heap_extract_min(minHeap);
        int u = minData.value;
        visited[u] = 1;

        if (u == end) break;

        ADJNODE *adj = g->nodes[u]->neighbor;
        while (adj != NULL) {
            int v = adj->nid;
            int weight = adj->weight;

            if (!visited[v] && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                HEAPDATA hd = {dist[v], v};
                heap_insert(minHeap, hd);
            }
            adj = adj->next;
        }
    }

    int current = end;
    while (current != start) {
        int p = parent[current];
        if (p == -1) {
            free(dist);
            free(parent);
            free(visited);
            heap_clean(&minHeap);
            return sp; // No path found
        }
        insert_edge_end(sp, p, current, dist[current] - dist[p]);
        current = p;
    }

    free(dist);
    free(parent);
    free(visited);
    heap_clean(&minHeap);

    return sp;
}

void print_edgelist(EDGELIST *el) {
    EDGENODE *current = el->start;
    printf("size %d ", el->size);
    while (current != NULL) {
        printf("(from %d to %d weight %d) ", current->from, current->to, current->weight);
        current = current->next;
    }
    printf("\n");
}

