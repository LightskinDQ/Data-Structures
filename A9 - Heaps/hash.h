/*
 * hash.h
 *
 *  Created on: Jul. 13, 2024
 *      Author: dillonquick
 */

#ifndef HASH_H_
#define HASH_H_

/* Define structure HASHDATA type to represent key (string) value (int) pair.
 * char key[20] - key string
 * int value - value associated with the key.
 */
typedef struct {
    char key[20];
    int value;
} HASHDATA;

/* Define structure HASHNODE as linked list node to represent hash data the same hashed value.
 * char key[20] - key string
 * int value - value associated with the key.
 * next - pointer to the next node.
 */
typedef struct hashnode {
  char key[20];
  int  value;
  struct hashnode *next;
} HASHNODE;

/*  Define HASHTABLE structure type for linked hash table
 *  HASHNODE **hna -- pointer pointing to the array of HASHNODE pointers.
 *  int size  --  hash table size, i.e., the modular or length of index array
 *  int count --  number of data elements in the hash table
 */
typedef struct hashtable {
  HASHNODE **hna;
  int size;
  int count;
} HASHTABLE;

/* Hash function that hash key string to an integer of modular of hash table size
 * @param key - input key string
 * @param size - modular value
 * @return  - sum of ASCII code value the key string modular % size
 */
int hash(char *key, int size);

/* Create dynamically a chained hash table of the given size
 * @param size  --  hash table size, i.e., the length of index array.
 */
HASHTABLE *new_hashtable(int size);

/* Insert key value data into HASHTABLE, so that each linked list maintains the increasing order of keys.
 * @param ht - pointer to a HASHTABLE
 * @param key - key string
 * @param value - int value
 * #return - when the HASHNODE of the key exists, update its value and return 0;
 * otherwise insert into the hash table and return 1
*/
int hashtable_insert(HASHTABLE *ht, char *key, int value);


/* Search the hash table and return the pointer of found hashnode
 * @param ht - pointer to a HASHTABLE
 * @param key - input search key string
 * @return - pointer to the found HASHNODE, otherwise NULL
 */
HASHNODE *hashtable_search(HASHTABLE *ht, char *key);


/* Delete hashnode by key.
 * @param ht - pointer to a HASHTABLE
 * @param key - delete key string
 * @return - if the named hash node exists, delete it and return 1; otherwise return 0.
*/
int hashtable_delete(HASHTABLE *ht, char *key);

/* Delete all linked lists and reset the count to 0
 * @param ht - pointer to a HASHTABLE
*/
void hashtable_clean(HASHTABLE **ht);

#endif /* HASH_H_ */
