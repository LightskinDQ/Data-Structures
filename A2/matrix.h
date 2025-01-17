/*
 * matrix.h
 *
 *  Created on: May 25, 2024
 *      Author: dillonquick
 */

#ifndef MATRIX_H_
#define MATRIX_H_

float norm(float *v, int n);

float dot_product(float *v1, float *v2, int n);

void matrix_multiply_vector(float *m, float *v, float *vout, int n);

void matrix_multiply_matrix(float *m1, float *m2, float *m3, int n);


#endif /* MATRIX_H_ */
