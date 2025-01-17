/*
 * powersum.c
 *
 *  Created on: May 15, 2024
 *      Author: dillonquick
 */

#include "powersum.h"
#include <stdio.h>
#include <limits.h>

int power_overflow(int b, int n) {
    if (n < 0) return 1; 
    if (b == 0 && n == 0) return 1; 
    if (b == 0 || b == 1) return 0; 
    if (b == -1) return 0; 
    if (n == 0) return 0; 
    
    long long result = 1;
    for (int i = 0; i < n; i++) {
        result *= b;
        if (result > INT_MAX || result < INT_MIN) {
            return 1; 
        }
    }
    return 0; 
}

int mypower(int b, int n) {
    if (power_overflow(b, n)) {
        return 0; 
    }
    long long result = 1;
    for (int i = 0; i < n; i++) {
        result *= b;
    }
    return result;
}

int powersum(int b, int n) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        int power = mypower(b, i);
        if (power == 0 && power_overflow(b, i)) {
            return 0; 
        }
        sum += power;
        if (sum > INT_MAX || sum < INT_MIN) {
            return 0; 
        }
    }
    return (sum + 1);
}

