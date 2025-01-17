/*
 * polynomial.h
 *
 *  Created on: May 25, 2024
 *      Author: dillonquick
 */

#ifndef POLYNOMIAL_H_
#define POLYNOMIAL_H_

float horner(float *p, int n, float x);

void derivative(float *p, float *d, int n);

float newton(float *p, int n, float x0);


#endif /* POLYNOMIAL_H_ */
