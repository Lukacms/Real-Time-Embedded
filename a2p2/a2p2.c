/*
    Part of the Real-Time Embedded Systems course at Halmstad University
    Copyright (c) 2017, Sebastian Kunze <sebastian.kunze@hh.se>
    All rights reserved.
    Wagner de Morais (Wagner.deMorais@hh.se)
*/

#include <stdio.h>
#include <stdlib.h>

#include "expstruct.h"
#include "piface.h"
#include "rpi-systimer.h"

#define LINE 32

int main()
{

    char str[LINE];
    piface_init();
    piface_clear();

    piface_puts("DT8025 - A2P2");
    RPI_WaitMicroSeconds(2000000);
    piface_clear();

    ExpStruct *value;

    value = iexp(10);

    sprintf(str, "%d: %d.%d", 10, value->expInt, value->expFraction);
    piface_puts(str);
    free(value);

    return 0;
}
