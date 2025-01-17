/*
 * powersum.c
 *
 *  Created on: May 15, 2024
 *      Author: dillonquick
 */

#include "quadratic.h"
#include <math.h>
#define EPSILON 1e-6

int solution_type(float a, float b, float c) {
    int t = -1;
    if (fabs(a) < EPSILON)
        t = 0;
    else {
        float discriminant = b * b - 4 * a * c;
        if (discriminant > 0)
            t = 2; 
        else if (fabs(discriminant) < EPSILON)
            t = 1; 
        else
            t = 3; 
    }
    return t;
}


float real_root_big(float a, float b, float c) {
    int type = solution_type(a, b, c);
    if (type != 1 && type != 2) {
        return 0; 
    }
    float discriminant = b * b - 4 * a * c;
    return (-b + sqrt(discriminant)) / (2 * a);
}


float real_root_small(float a, float b, float c) {
    int type = solution_type(a, b, c);
    if (type != 1 && type != 2) {
        return 0; 
    }
    float discriminant = b * b - 4 * a * c;
    return (-b - sqrt(discriminant)) / (2 * a);
}


