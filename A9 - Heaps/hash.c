/*
 * hash.c
 *
 *  Created on: Jul. 13, 2024
 *      Author: dillonquick
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

HASHNODE *hashtable_search(HASHTABLE *ht, char *key) {
    int index = hash(key, ht->size);
    HASHNODE *current = ht->hna[index];

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int hashtable_insert(HASHTABLE *ht, char *key, int value) {
    int index = hash(key, ht->size);
    HASHNODE *current = ht->hna[index];
    HASHNODE *prev = NULL;

    // Traverse the linked list to find the correct position
    while (current != NULL && strcmp(current->key, key) < 0) {
        prev = current;
        current = current->next;
    }

    // If the key already exists, update the value
    if (current != NULL && strcmp(current->key, key) == 0) {
        current->value = value;
        return 0;
    }

    // Create a new node
    HASHNODE *new_node = (HASHNODE *)malloc(sizeof(HASHNODE));
    strcpy(new_node->key, key);
    new_node->value = value;
    new_node->next = current;

    // Insert the new node
    if (prev == NULL) {
        ht->hna[index] = new_node;
    } else {
        prev->next = new_node;
    }
    ht->count++;
    return 1;
}

int hashtable_delete(HASHTABLE *ht, char *key) {
    int index = hash(key, ht->size);
    HASHNODE *current = ht->hna[index];
    HASHNODE *prev = NULL;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (prev == NULL) {
                ht->hna[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            ht->count--;
            return 1;
        }
        prev = current;
        current = current->next;
    }
    return 0;
}

int hash(char* key, int size) {
    unsigned int hash = 0;
    while (*key) {
        hash += *key++;
    }
    return hash % size;
}

HASHTABLE *new_hashtable(int size) {
    HASHTABLE *ht = (HASHTABLE*) malloc(sizeof(HASHTABLE));
    ht->hna = (HASHNODE**) malloc(sizeof(HASHNODE*) * size);
    for (int i = 0; i < size; i++) {
        ht->hna[i] = NULL;
    }

    ht->size = size;
    ht->count = 0;
    return ht;
}

void hashtable_clean(HASHTABLE **htp) {
    if (*htp == NULL)
        return;
    HASHTABLE *ht = *htp;
    HASHNODE *p, *temp;
    for (int i = 0; i < ht->size; i++) {
        p = ht->hna[i];
        while (p) {
            temp = p;
            p = p->next;
            free(temp);
        }
        ht->hna[i] = NULL;
    }
    free(ht->hna);
    free(ht);
    *htp = NULL;
}
