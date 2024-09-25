/*
    Part of the Real-Time Embedded Systems course at Halmstad University
    Copyright (c) 2017, Sebastian Kunze <sebastian.kunze@hh.se>
    All rights reserved.
 */
/*
 * Modified by Wagner Morais on Aug 2023.
 */

#include "expstruct.h"
#include <stddef.h>
#include <stdlib.h>

ExpStruct *iexp(int x)
{
    ExpStruct *e = malloc(sizeof(ExpStruct));
    return e;
}