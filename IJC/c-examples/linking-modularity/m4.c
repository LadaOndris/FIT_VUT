/*
 * m4.c
 *
 */

#include "test.h"
#include <stdio.h>

static void g4_private(void) {
    printf("g4_private\n");
}

int f4(void)
{
    printf("f4\n");
    g4_private();
    return 0;
}
