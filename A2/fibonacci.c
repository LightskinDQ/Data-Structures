/*
 * fibonacci.c
 *
 *  Created on: May 25, 2024
 *      Author: dillonquick
 */

#include "fibonacci.h"

int recursive_fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    return recursive_fibonacci(n - 1) + recursive_fibonacci(n - 2);
}

int iterative_fibonacci(int n) {
    if (n <= 1) {
        return n;
    }

    int a = 0, b = 1, c;
    for (int i = 2; i <= n; ++i) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int dpbu_fibonacci(int *f, int n) {
    f[0] = 0;
    f[1] = 1;
    for (int i = 2; i <= n; ++i) {
        f[i] = f[i - 1] + f[i - 2];
    }
    return f[n];
}

int dptd_fibonacci(int *f, int n) {
    if (f[n] != -1) {
        return f[n];
    }

    if (n <= 1) {
        f[n] = n;
    } else {
        f[n] = dptd_fibonacci(f, n - 1) + dptd_fibonacci(f, n - 2);
    }

    return f[n];
}

