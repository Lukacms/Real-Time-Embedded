/*
    Part of the Real-Time Embedded Systems course at Halmstad University
    Copyright (c) 2017, Sebastian Kunze <sebastian.kunze@hh.se>
    All rights reserved.
 */
/*
 * Modified by Wagner Morais on Aug 2022.
 */

#include "expstruct.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define Precision 20

static int factorial(unsigned int x)
{
    int fact = 1;

    for (unsigned int i = x; i > 0; i--) {
        fact *= i;
    }
    return fact;
}

static double ipow(int x, int power)
{
    double res = 1.0;

    for (int i = 0; i < power; i++) {
        res *= x;
    }
    return res;
}

ExpStruct *iexp(int x)
{
    ExpStruct *e = malloc(sizeof(ExpStruct));

    if (!e) {
        fprintf(stderr, "Error: while allocating structure");
        return NULL;
    }
    e->expFraction = 0;
    for (int i = 0; i <= Precision; i++) {
        e->expFraction += (ipow(x, i) / factorial(i)) * 100;
    }
    e->expInt = e->expFraction / 100;
    e->expFraction %= 100;
    if (e->expFraction < 0)
        e->expFraction *= -1;
    return e;
}
