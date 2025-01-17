/*
 * tree.c
 *
 *  Created on: Jun. 29, 2024
 *      Author: dillonquick
 */
/*
 * Tree Operations Implementation
 */

#include <stdio.h>
#include <stdlib.h>
#include "queue_stack.h"
#include "tree.h"

TPROPS tree_property(TNODE *root) {
    TPROPS props = {0, 0};
    if (!root) return props;

    QUEUE queue = {0};
    enqueue(&queue, root);

    int node_count = 0;
    int height = 0;
    while (queue.front) {
        int level_count = 0;
        int size = queue.rear - queue.front + 1;
        node_count += size;
        height++;

        for (int i = 0; i < size; i++) {
            TNODE *node = dequeue(&queue);
            if (node->left) {
                enqueue(&queue, node->left);
                level_count++;
            }
            if (node->right) {
                enqueue(&queue, node->right);
                level_count++;
            }
        }
    }
    props.order = node_count;
    props.height = height;
    return props;
}

void preorder(TNODE *root) {
    if (root) {
        printf("%c ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(TNODE *root) {
    if (root) {
        inorder(root->left);
        printf("%c ", root->data);
        inorder(root->right);
    }
}

void postorder(TNODE *root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        printf("%c ", root->data);
    }
}

void bforder(TNODE *root) {
    if (!root) return;

    QUEUE queue = {0};
    enqueue(&queue, root);

    while (queue.front) {
        TNODE *node = dequeue(&queue);
        printf("%c ", node->data);

        if (node->left) {
            enqueue(&queue, node->left);
        }
        if (node->right) {
            enqueue(&queue, node->right);
        }
    }
}

TNODE *bfs(TNODE *root, char val) {
    if (!root) return NULL;

    QUEUE queue = {0};
    enqueue(&queue, root);

    while (queue.front) {
        TNODE *node = dequeue(&queue);

        if (node->data == val) {
            return node;
        }

        if (node->left) {
            enqueue(&queue, node->left);
        }
        if (node->right) {
            enqueue(&queue, node->right);
        }
    }
    return NULL;
}

TNODE *dfs(TNODE *root, char val) {
    if (!root) return NULL;

    STACK stack = {0};
    push(&stack, root);

    while (stack.top) {
        TNODE *node = pop(&stack);

        if (node->data == val) {
            return node;
        }

        if (node->right) {
            push(&stack, node->right);
        }
        if (node->left) {
            push(&stack, node->left);
        }
    }
    return NULL;
}

// the following functions are given, need to add to your program.

TNODE *new_node(char val) {
    TNODE *np = (TNODE *) malloc(sizeof(TNODE));
    if (np != NULL) {
        np->data = val;
        np->left = NULL;
        np->right = NULL;
    }
    return np;
}

void tree_clean(TNODE **rootp) {
    TNODE *p = *rootp;
    if (p) {
        if (p->left)
            tree_clean(&p->left);
        if (p->right)
            tree_clean(&p->right);
        free(p);
    }
    *rootp = NULL;
}

void insert_tree(TNODE **rootp, char val) {
    if (*rootp == NULL) {
        *rootp = new_node(val);
    } else {
        QUEUE queue = { 0 };
        TNODE *p;
        enqueue(&queue, *rootp);
        while (queue.front) {
            p = dequeue(&queue);
            if (p->left == NULL) {
                p->left = new_node(val);
                break;
            } else {
                enqueue(&queue, p->left);
            }

            if (p->right == NULL) {
                p->right = new_node(val);
                break;
            } else {
                enqueue(&queue, p->right);
            }
        }
    }
}
