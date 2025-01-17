/*
 * mysort.h
 *
 *  Created on: Jun. 4, 2024
 *      Author: dillonquick
 */

#ifndef MYSORT_H_
#define MYSORT_H_

/**
 * Use selection sort algorithm to sort array of float pointers such that
 * their pointed values are in decreasing order.
 *
 * @param *a[] - array of float pointers.
 * @param left - the start index of float pointer in array.
 * @param right - the end index of float pointer in array
 */
void selection_sort(float *a[], int left, int right);


/**
 * Use quick sort algorithm to sort array of float pointers such that
 * their pointed values are in decreasing order.
 *
 * @param *a[] - array of float pointers.
 * @param left - the start index of float pointer in array.
 * @param right - the end index of float pointer in array
 */
void quick_sort(float *a[], int left, int right);

#endif /* MYSORT_H_ */
