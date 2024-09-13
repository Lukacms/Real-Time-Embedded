/*
    Part of the Real-Time Embedded Systems course at Halmstad University
    Copyright (c) 2017, Sebastian Kunze <sebastian.kunze@hh.se>
    All rights reserved.
    Wagner de Morais (Wagner.deMorais@hh.se)
*/

#include "lib/iregister.h"
#include <stdio.h>
#include <stdlib.h>

#define LINE 80

void nameCheck()
{
    char str[LINE] = {'\0'};
    printf("Enter your name: ");
    scanf("%s", str);
    printf("Welcome %s\n", str);
}

void printBinary(iRegister r, int breakl)
{
    char *str = reg2str(r);

    if (!str)
        return;
    printf("%s%c", str, breakl ? '\n' : '\0');
    free(str);
}

int main()
{
    iRegister r = {0};
    char str[LINE] = {'\0'};
    char *rep = NULL;
    char c = '\0';
    int inumber, inibble, ibit, ishift = 0;
    nameCheck();
    printf("Enter an integer number (32-bits): ");
    scanf("%d", &inumber);
    printf("Enter the bit position (0<=bit<32): ");
    scanf("%d", &ibit);
    printf("Enter the nibble position (0<=nibble<8): ");
    scanf("%d", &inibble);
    printf("Enter the number of bits to shift (0<bit<32): ");
    scanf("%d", &ishift);
    printf("You entered number %d -> ", inumber);
    printBinary((iRegister){inumber}, 1);
    printf("Bit: %d, nibble: %d\n", ibit, inibble);
    r.content = inumber;
    setAll(&r);
    printf("setAll(&r) returned: %d -> ", r.content);
    printBinary(r, 1);
    resetAll(&r);
    printf("resetAll(&r) returned: %d -> ", r.content);
    printBinary(r, 1);
    r.content = inumber;
    setBit(ibit, &r);
    printf("setBit(%d, &r) returned: %d -> ", ibit, r.content);
    printBinary(r, 1);
    printf("getBit(%d, &r) returned: %d\n", ibit, getBit(ibit, &r));
    resetBit(ibit, &r);
    printf("resetBit(%d, &r) returned: %d -> ", ibit, r.content);
    printBinary(r, 1);
    r.content = inumber;
    assignNibble(inibble, 1, &r);
    printf("assignNibble(%d, 1, &r) returned: %d -> ", inibble, r.content);
    printBinary(r, 1);
    int res = getNibble(inibble, &r);
    printf("getNibble(%d, &r) returned: %d -> ", inibble, res);
    printBinary((iRegister){res}, 1);
    r.content = inumber;
    shiftLeft(ishift, &r);
    printf("shiftLeft(%d, &r) returned: %d -> ", ishift, r.content);
    printBinary(r, 1);
    r.content = inumber;
    shiftRight(ishift, &r);
    printf("shiftRight(%d, &r) returned: %d -> ", ishift, r.content);
    printBinary(r, 1);
}
