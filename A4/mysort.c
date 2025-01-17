/*
 * mysort.c
 *
 *  Created on: Jun. 4, 2024
 *      Author: dillonquick
 */
#include <stdio.h>
#include "mysort.h"

void selection_sort(float *a[], int left, int right) {
    for (int i = left; i < right; i++) {
        int maxIdx = i;
        for (int j = i + 1; j <= right; j++) {
            if (*a[j] > *a[maxIdx]) {
                maxIdx = j;
            }
        }
        if (maxIdx != i) {
            float *temp = a[i];
            a[i] = a[maxIdx];
            a[maxIdx] = temp;
        }
    }
}

void quick_sort(float *a[], int left, int right) {
    if (left < right) {
        float *pivot = a[right];
        int i = left - 1;

        for (int j = left; j < right; j++) {
            if (*a[j] >= *pivot) {
                i++;
                float *temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
        float *temp = a[i + 1];
        a[i + 1] = a[right];
        a[right] = temp;

        int pi = i + 1;

        quick_sort(a, left, pi - 1);
        quick_sort(a, pi + 1, right);
    }
}
