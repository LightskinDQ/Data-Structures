/*
 * myrecord_avl.h
 *
 *  Created on: Jul. 4, 2024
 *      Author: dillonquick
 */

#ifndef MYRECORD_AVL_H_
#define MYRECORD_AVL_H_
#include "avl.h"

/* This structure holds the root pointer of AVL tree data structure,
 * and count, mean and stddev of the data.score in the AVL tree.
 */
typedef struct {
    AVLNODE *root;
    int count;
    float mean;
    float stddev;
} AVLDS;

void merge_avl(AVLNODE **dest_rootp, AVLNODE **source_rootp);

void merge_avlds(AVLDS *dest, AVLDS *source);

void avlds_clean(AVLDS *ds);

void add_record(AVLDS *ds, RECORD data);

void remove_record(AVLDS *ds, char *name);




#endif /* MYRECORD_AVL_H_ */
