/*
    Modified by Wagner Morais on Sep 2023.
 */

#include "lib/piface.h"
#include <stdio.h>

int main()
{
    piface_init();
    piface_clear();
    piface_puts("Short string");
    piface_puts("This is a long string");
    piface_puts("1st line\n2nd line");
    return 0;
}
