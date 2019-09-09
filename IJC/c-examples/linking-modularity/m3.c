/*
 * m3.c
 *
 */

#include "test.h"
#include <stdio.h>

static int global3_private = 3;

int f3(void)
{
    printf("global3_private = %d\n", global3_private);
    printf("f3\n");
    return 0;
}
