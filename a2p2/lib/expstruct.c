/*
    Part of the Real-Time Embedded Systems course at Halmstad University
    Copyright (c) 2017, Sebastian Kunze <sebastian.kunze@hh.se>
    All rights reserved.
 */
/*
 * Modified by Wagner Morais on Aug 2022.
 */

#include "expstruct.h"
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int factorial(unsigned int x)
{
    int fact = 1;

    for (unsigned int i = x; i > 0; i--) {
        fact *= i;
    }
    return fact;
}

ExpStruct *iexp(int x)
{
    ExpStruct *e = malloc(sizeof(ExpStruct));

    if (!e) {
        fprintf(stderr, "Error: while allocating structure");
        return NULL;
    }
    for (int i = 0; i <= x; i++) {
        e->expInt += pow(x, i) / factorial(i);
    }
    return e;
}
