/*
 * tree.h
 *
 *  Created on: Jun. 29, 2024
 *      Author: dillonquick
 */

#ifndef TREE_H_
#define TREE_H_

typedef struct tnode {
    char data;
    struct tnode *left;
    struct tnode *right;
} TNODE;


typedef struct tree_props {
    int order;   // as the number of nodes in a tree
    int height;  // as the height of a tree
} TPROPS;

TPROPS tree_property(TNODE *root);

void preorder(TNODE *root);


void inorder(TNODE *root);


void postorder(TNODE *root);


void bforder(TNODE *root);


TNODE *bfs(TNODE *root, char key);

TNODE *dfs(TNODE *root, char key);


TNODE *new_node(char val);
void tree_clean(TNODE **rootp);
void insert_tree(TNODE **rootp, char val);

#endif /* TREE_H_ */
