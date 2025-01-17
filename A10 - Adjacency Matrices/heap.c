/*
 * heap.c
 *
 *  Created on: Jul. 13, 2024
 *      Author: dillonquick
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

int cmp(KEYTYPE a, KEYTYPE b) {
    return (a < b) ? -1 : (a > b) ? 1 : 0;
}

HEAP *new_heap(int capacity) {
    HEAP *hp = (HEAP*) malloc(sizeof(HEAP));
    if (hp == NULL) return NULL;
    hp->hda = (HEAPDATA *) malloc(sizeof(HEAPDATA) * capacity);
    if (hp->hda == NULL) {
        free(hp);
        return NULL;
    }
    hp->capacity = capacity;
    hp->size = 0;
    return hp;
}

void swap(HEAPDATA *a, HEAPDATA *b) {
    HEAPDATA temp = *a;
    *a = *b;
    *b = temp;
}

int heapify_up(HEAPDATA *hda, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (cmp(hda[index].key, hda[parent].key) >= 0) break;
        swap(&hda[index], &hda[parent]);
        index = parent;
    }
    return index;
}

int heapify_down(HEAPDATA *hda, int n, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < n && cmp(hda[left].key, hda[smallest].key) < 0) {
        smallest = left;
    }
    if (right < n && cmp(hda[right].key, hda[smallest].key) < 0) {
        smallest = right;
    }
    if (smallest != index) {
        swap(&hda[index], &hda[smallest]);
        heapify_down(hda, n, smallest);
    }
    return index;
}

void heap_insert(HEAP *heap, HEAPDATA new_node) {
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->hda = (HEAPDATA *) realloc(heap->hda, sizeof(HEAPDATA) * heap->capacity);
    }
    heap->hda[heap->size] = new_node;
    heapify_up(heap->hda, heap->size);
    heap->size++;
}

HEAPDATA heap_find_min(HEAP *heap) {
    if (heap->size > 0) {
        return heap->hda[0];
    } else {
        HEAPDATA empty = {0, 0};
        return empty;
    }
}

HEAPDATA heap_extract_min(HEAP *heap) {
    if (heap->size > 0) {
        HEAPDATA min = heap->hda[0];
        heap->hda[0] = heap->hda[heap->size - 1];
        heap->size--;
        heapify_down(heap->hda, heap->size, 0);
        if (heap->size <= heap->capacity / 4 && heap->capacity > 4) {
            heap->capacity /= 2;
            heap->hda = (HEAPDATA *) realloc(heap->hda, sizeof(HEAPDATA) * heap->capacity);
        }
        return min;
    } else {
        HEAPDATA empty = {0, 0};
        return empty;
    }
}

int heap_change_key(HEAP *heap, int index, KEYTYPE new_key) {
    KEYTYPE old_key = heap->hda[index].key;
    heap->hda[index].key = new_key;
    if (cmp(new_key, old_key) < 0) {
        return heapify_up(heap->hda, index);
    } else {
        return heapify_down(heap->hda, heap->size, index);
    }
}

int heap_search_data(HEAP *heap, VALUETYPE val) {
    for (int i = 0; i < heap->size; i++) {
        if (heap->hda[i].value == val) {
            return i;
        }
    }
    return -1;
}

void heap_clean(HEAP **heapp) {
    if (heapp && *heapp) {
        HEAP *heap = *heapp;
        if (heap->hda) {
            free(heap->hda);
        }
        free(heap);
        *heapp = NULL;
    }
}
