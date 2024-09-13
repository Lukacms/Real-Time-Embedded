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
        fprintf(stderr, "Error: Failed to reset all Bits\n");
        return;
    }
}

void setBit(int i, iRegister *r)
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

    r->content |= (1 << i);

    // post-condition
    if ((r->content & (1 << i)) == 0) {
        fprintf(stderr, "Error: Failed to set Bit\n");
        return;
    }
}

void setAll(iRegister *r)
{
    // pre-condition
    if (!r) {
        fprintf(stderr, "Error: A NULL pointer was given to resetBit\n");
        return;
    }
    for (int i = 0; i < 32; i++) {
        r->content &= (1 << i);
    }

    // post-condition NOTE: to change
    if (r->content == 0) {
        fprintf(stderr, "Error: Failed to set all Bits\n");
        return;
    }
}

int getBit(int i, iRegister *r)
{
    return ((r->content << (32 - 1 - i)) >> (32 - 1)) ? 1 : 0;
}

void assignNibble(int pos, int i, iRegister *r)
{
    iRegister s = {i};

    // pre-condition
    if (pos <= 0 || pos > 2 || !r) {
        fprintf(stderr, "Error: wrong parameters.");
        return;
    }
    for (int j = pos == 1 ? 0 : 8; j < 8 * pos; j++) {
        if (getBit(j, &s) == 1) {
            setBit(j, r);
        } else {
            resetBit(j, r);
        }
    }
}

int getNibble(int pos, iRegister *r)
{
    iRegister nibble = {0};
    int ind = 0;

    // pre-condition
    if (pos <= 0 || pos > 2 || !r) {
        fprintf(stderr, "Error: wrong parameters.");
        return -1;
    }
    for (int j = pos == 1 ? 0 : 8; j < 8 * pos; j++) {
        if (getBit(j, r) == 1) {
            setBit(ind, &nibble);
        } else {
            resetBit(ind, &nibble);
        }
        ind++;
    }
    return nibble.content;
}

char *reg2str(iRegister r)
{
    char *str = malloc(sizeof(char) * (32 + 1));
    int mask = 0;

    // pre-condition
    if (!str) {
        return NULL;
    }
    for (int i = 0; i < 32; i++) {
        mask = ((r.content << i) >> (32 - 1));
        str[i] = '0' + (mask ? 1 : 0);
    }
    str[32] = '\0';
    return str;
}

void shiftRight(int n, iRegister *r)
{
    // pre-condition
    if (n < 0 || n >= 32 || !r) {
        fprintf(stderr, "Error: wrong parameters");
        return;
    }
    r->content <<= n;
}

void shiftLeft(int n, iRegister *r)
{
    // pre-condition
    if (n < 0 || n >= 32 || !r) {
        fprintf(stderr, "Error: wrong parameters");
        return;
    }
    r->content >>= n;
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
