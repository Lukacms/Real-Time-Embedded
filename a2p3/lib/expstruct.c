/*
    Part of the Real-Time Embedded Systems course at Halmstad University
    Copyright (c) 2017, Sebastian Kunze <sebastian.kunze@hh.se>
    All rights reserved.
 */
/*
 * Modified by Wagner Morais on Aug 2022.
 */

#include "expstruct.h"
#include "led.h"
#include "rpi-systimer.h"
#include <math.h>
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

ExpStruct *iexp(int x)
{
    ExpStruct *e = malloc(sizeof(ExpStruct));
    static int j = 0;
    int i = 0;

    if (!e) {
        fprintf(stderr, "Error: while allocating structure");
        return NULL;
    }
    for (; i <= Precision; i++, j++) {
        e->expFraction += pow(x, i) / factorial(i) * 100;
        if (j % 5 == 0)
            led_toggle();
        RPI_WaitMicroSeconds(100000);
    }
    e->expInt = e->expFraction / 100;
    e->expFraction %= 100;
    if (e->expFraction < 0)
        e->expFraction *= -1;
    return e;
}
