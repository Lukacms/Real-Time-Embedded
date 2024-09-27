/*
    Part of the Real-Time Embedded Systems course at Halmstad University
    Copyright (c) 2017, Sebastian Kunze <sebastian.kunze@hh.se>
    All rights reserved.
 */
/*
 * Modified by Wagner Morais on Aug 2022.
 */

#ifndef _EXPSTRUCT_H
#define _EXPSTRUCT_H

struct expStruct {
    int expInt;
    int expFraction;
};

typedef struct expStruct ExpStruct;

/**
 * @brief calculate the approximation of the exponential value of x using
 * Taylor's serie expansion with 20 degree of precision
 *
 * method for exponential function:
 * e^n = x^0/0! + x^1/1! + x^2/2! + ... x^n/n!
 *
 * @param x int - the value to calculate the exponential of
 * @return ExpStruct * - containing the 2 != precisions results
 *
 * Pre-condition: x is a real number
 *
 * Post-condition: expInt = e^x and expFraction = e^x * 100 (for the degrees of
 * precisions)
 */
ExpStruct *iexp(int x);

#endif
