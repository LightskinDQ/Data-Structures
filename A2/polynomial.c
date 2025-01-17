/*
 * polynomial.c
 *
 *  Created on: May 25, 2024
 *      Author: dillonquick
 */

#include <stdio.h>
#include <math.h>
#include "polynomial.h"
#define EPSILON 1e-6
#define MAXCOUNT 100

float horner(float *p, int n, float x) {
    float result = p[0];
    for (int i = 1; i < n; ++i) {
        result = result * x + p[i];
    }
    return result;
}

void derivative(float *p, float *d, int n) {
    for (int i = 0; i < n - 1; ++i) {
        d[i] = (n - 1 - i) * p[i];
    }
}

float newton(float *p, int n, float x0) {
    float d[n - 1];
    derivative(p, d, n);

    for (int i = 0; i < MAXCOUNT; ++i) {
        float f_val = horner(p, n, x0);
        float f_prime_val = horner(d, n - 1, x0);

        if (fabs(f_prime_val) < EPSILON) {
            break;
        }

        float x1 = x0 - f_val / f_prime_val;

        if (fabs(x1 - x0) < EPSILON) {
            return x1;
        }

        x0 = x1;
    }

    return x0;
}

