/*
    Part of the Real-Time Embedded Systems course at Halmstad University
    Copyright (c) 2017, Sebastian Kunze <sebastian.kunze@hh.se>
    All rights reserved.
    Wagner de Morais (Wagner.deMorais@hh.se)
*/

#include "lib/iregister.h"
#include "lib/uart.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE 80

void nameCheck()
{
    char str[LINE] = {'\0'};
    int i = 0;

    uart_puts("Enter your name: ");
    do {
        str[i] = uart_getc();
    } while (str[i++] != '\n');
    uart_puts(&str[i]);
    str[i] = '\0';
    print2uart("Welcome %s\n", str);
}

void printBinary(iRegister r, int breakl)
{
    char *str = reg2str(r);

    if (!str)
        return;
    print2uart("%s%c", str, breakl ? '\n' : '\0');
    free(str);
}

char *scan_uart()
{
    char *str = NULL;
    int i = 0;

    if (!(str = malloc(sizeof(char) * (LINE + 1))))
        return "";
    str = memset(str, '\0', LINE);
    do {
        str[i] = uart_getc();
    } while (str[i++] != '\n');
    uart_puts(str);
    str[i] = '\0';
    return str;
}

int main()
{
    iRegister r = {0};
    char *get_nb = NULL;
    int inumber, inibble, ibit, ishift = 0;
    uart_init();
    nameCheck();
    uart_puts("Enter an integer number (32-bits): ");
    get_nb = scan_uart();
    inumber = atoi(get_nb);
    free(get_nb);
    uart_puts("Enter the bit position (0<=bit<32): ");
    get_nb = scan_uart();
    ibit = atoi(get_nb);
    free(get_nb);
    uart_puts("Enter the nibble position (0<=nibble<8): ");
    get_nb = scan_uart();
    inibble = atoi(get_nb);
    free(get_nb);
    uart_puts("Enter the number of bits to shift (0<bit<32): ");
    ishift = atoi(scan_uart());
    print2uart("You entered number %d -> ", inumber);
    printBinary((iRegister){inumber}, 1);
    print2uart("Bit: %d, nibble: %d\n", ibit, inibble);
    r.content = inumber;
    setAll(&r);
    print2uart("setAll(&r) returned: %d -> ", r.content);
    printBinary(r, 1);
    resetAll(&r);
    print2uart("resetAll(&r) returned: %d -> ", r.content);
    printBinary(r, 1);
    r.content = inumber;
    setBit(ibit, &r);
    print2uart("setBit(%d, &r) returned: %d -> ", ibit, r.content);
    printBinary(r, 1);
    print2uart("getBit(%d, &r) returned: %d\n", ibit, getBit(ibit, &r));
    resetBit(ibit, &r);
    print2uart("resetBit(%d, &r) returned: %d -> ", ibit, r.content);
    printBinary(r, 1);
    r.content = inumber;
    assignNibble(inibble, 1, &r);
    print2uart("assignNibble(%d, 1, &r) returned: %d -> ", inibble, r.content);
    printBinary(r, 1);
    int res = getNibble(inibble, &r);
    print2uart("getNibble(%d, &r) returned: %d -> ", inibble, res);
    printBinary((iRegister){res}, 1);
    r.content = inumber;
    shiftLeft(ishift, &r);
    print2uart("shiftLeft(%d, &r) returned: %d -> ", ishift, r.content);
    printBinary(r, 1);
    r.content = inumber;
    shiftRight(ishift, &r);
    print2uart("shiftRight(%d, &r) returned: %d -> ", ishift, r.content);
    printBinary(r, 1);
}
