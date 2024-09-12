//  Created by Mohammadreza Mousavi [mohmou] on 9/5/14.
//  Updated by Masoumeh Taromirad on 11/08/16.
//  Updated by Wagner Morais and Johannes van Esch on 28/08/18.
//  Updated by Wagner Morais and Hazem Ali on 26/08/21.
//  Copyright (c) 2014 by Mohammadreza Mousavi [mohmou]. All rights reserved.

#include "iregister.h"
#include <stdio.h>
#include <stdlib.h>

void resetAll(iRegister *r)
{
    // pre-condition
    if (r == NULL) {
        fprintf(stderr, "Error: A NULL pointer was given to resetBit\n");
        return;
    }
    for (int i = 0; i < 32; i++) {
        r->content &= (1 << i);
    }

    // post-condition
    if (r->content != 0) {
        fprintf(stderr, "Error: Failed to reset Bits\n");
        return;
    }
}

void resetBit(int i, iRegister *r)
{
    // pre-condition
    if (r == NULL) {
        fprintf(stderr, "Error: A NULL pointer was given to resetBit\n");
        return;
    }
    // pre-condition
    if (i < 0 || i > 31) {
        fprintf(stderr, "Error: Invalid bit\n");
        return;
    }

    r->content &= ~(1 << i);

    // post-condition
    if ((r->content & (1 << i)) != 0) {
        fprintf(stderr, "Error: Failed to reset Bit\n");
        return;
    }
}
