/*
 * myrecord_bst.h
 *
 *  Created on: Jun. 29, 2024
 *      Author: dillonquick
 */

#ifndef MYRECORD_BST_H_
#define MYRECORD_BST_H_

/* Define structure data type BSTSD contains pointer to the root BST
 * and stats fileds: count, mean, and stddev.
 */
typedef struct {
  BSTNODE *root;
  int count;
  float mean;
  float stddev;
} BSTDS;

/* Add a record data into the BSTDS and update its statistic fields
 * using increamental algorithm.
 * @parame ds - pointer to the BSTDS.
 * @parama record - RECORD data to be added.
 */
void add_record(BSTDS *ds, RECORD record);

/* Delete a node from BSTDA with data.name matching with the given name
 * and stats fields using increamental algorithm.
 * @parame ds - pointer to the BSTDS.
 * @parama name - node data.name to be removed.
 */
void remove_record(BSTDS *ds, char *name);


/* Clean the BST of BSTDS and reset count, mean, stddev
 * @parame ds - pointer to the BSTDS.
 */
void bstds_clean(BSTDS *ds);


#endif /* MYRECORD_BST_H_ */
