/*
 * m2.c
 *
 */

#include "test.h"
#include <stdio.h>

int global2 = 2;

int f2(int i)
{
    printf("global2 = %d\n", global2);
    printf("f2(%d)\n", i);
    return 0;
}
