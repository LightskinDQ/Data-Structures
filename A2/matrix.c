/*
 * matrix.c
 *
 *  Created on: May 25, 2024
 *      Author: dillonquick
 */
#include <math.h>
#include "matrix.h"

float norm(float *v, int n) {
    float sum_of_squares = 0.0;
    for (int i = 0; i < n; ++i) {
        sum_of_squares += v[i] * v[i];
    }
    return sqrt(sum_of_squares);
}

float dot_product(float *v1, float *v2, int n) {
    float dot = 0.0;
    for (int i = 0; i < n; ++i) {
        dot += v1[i] * v2[i];
    }
    return dot;
}

void matrix_multiply_vector(float *m, float *vin, float *vout, int n) {
    for (int i = 0; i < n; ++i) {
        vout[i] = 0.0;
        for (int j = 0; j < n; ++j) {
            vout[i] += m[i * n + j] * vin[j];
        }
    }
}

void matrix_multiply_matrix(float *m1, float *m2, float *m3, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            m3[i * n + j] = 0.0;
            for (int k = 0; k < n; ++k) {
                m3[i * n + j] += m1[i * n + k] * m2[k * n + j];
            }
        }
    }
}


