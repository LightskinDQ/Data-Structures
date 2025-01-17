/*
 * bst.c
 *
 *  Created on: Jun. 29, 2024
 *      Author: dillonquick
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

BSTNODE *new_node(RECORD data);
BSTNODE *extract_smallest_node(BSTNODE **rootp);

BSTNODE *bst_search(BSTNODE *root, char *key) {
    if (root == NULL || strcmp(root->data.name, key) == 0) {
        return root;
    }
    if (strcmp(key, root->data.name) < 0) {
        return bst_search(root->left, key);
    } else {
        return bst_search(root->right, key);
    }
}

void bst_insert(BSTNODE **rootp, RECORD data) {
    if (*rootp == NULL) {
        *rootp = new_node(data);
    } else if (strcmp(data.name, (*rootp)->data.name) < 0) {
        bst_insert(&(*rootp)->left, data);
    } else {
        bst_insert(&(*rootp)->right, data);
    }
}

void bst_delete(BSTNODE **rootp, char *key) {
    BSTNODE *node = *rootp;
    if (node == NULL) {
        return;
    }
    if (strcmp(key, node->data.name) < 0) {
        bst_delete(&node->left, key);
    } else if (strcmp(key, node->data.name) > 0) {
        bst_delete(&node->right, key);
    } else {
        if (node->left == NULL) {
            *rootp = node->right;
            free(node);
        } else if (node->right == NULL) {
            *rootp = node->left;
            free(node);
        } else {
            BSTNODE *smallest = extract_smallest_node(&node->right);
            smallest->left = node->left;
            smallest->right = node->right;
            *rootp = smallest;
            free(node);
        }
    }
}

BSTNODE *new_node(RECORD data) {
    BSTNODE *np = (BSTNODE *) malloc(sizeof(BSTNODE));
    if (np) {
        memcpy(&np->data, &data, sizeof(RECORD));
        np->left = NULL;
        np->right = NULL;
    }
    return np;
}

BSTNODE *extract_smallest_node(BSTNODE **rootp) {
    BSTNODE *p = *rootp, *parent = NULL;
    if (p) {
        while (p->left) {
            parent = p;
            p = p->left;
        }
        if (parent == NULL) {
            *rootp = p->right;
        } else {
            parent->left = p->right;
        }
        p->left = NULL;
        p->right = NULL;
    }
    return p;
}

void bst_clean(BSTNODE **rootp) {
    BSTNODE *root = *rootp;
    if (root) {
        if (root->left) {
            bst_clean(&root->left);
        }
        if (root->right) {
            bst_clean(&root->right);
        }
        free(root);
    }
    *rootp = NULL;
}

