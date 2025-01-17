/*
 * myrecord_bst.c
 *
 *  Created on: Jun. 29, 2024
 *      Author: dillonquick
 */

#include <stdio.h>
#include <math.h>
#include <string.h>
#include "queue_stack.h"
#include "bst.h"
#include "myrecord_bst.h"

void add_record(BSTDS *ds, RECORD record) {
    float old_mean = ds->mean;

    bst_insert(&ds->root, record);

    ds->count++;
    ds->mean += (record.score - ds->mean) / ds->count;
    ds->stddev = sqrt(((ds->count - 1) * ds->stddev * ds->stddev + (record.score - ds->mean) * (record.score - old_mean)) / ds->count);
}

void remove_record(BSTDS *ds, char *name) {
    BSTNODE *node = bst_search(ds->root, name);
    if (node) {
        float old_mean = ds->mean;
        RECORD record = node->data;

        bst_delete(&ds->root, name);

        if (ds->count == 1) {
            ds->count = 0;
            ds->mean = 0;
            ds->stddev = 0;
        } else {
            ds->count--;
            ds->mean -= (record.score - ds->mean) / ds->count;
            ds->stddev = sqrt((ds->stddev * ds->stddev * (ds->count + 1) - (record.score - old_mean) * (record.score - ds->mean)) / ds->count);
        }
    }
}

void bstds_clean(BSTDS *ds) {
    bst_clean(&ds->root);
    ds->count = 0;
    ds->mean = 0;
    ds->stddev = 0;
}


