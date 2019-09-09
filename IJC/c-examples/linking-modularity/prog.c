/*
 * prog.c
 *
 * main module of test program
 *
 */

#include "m1.h"
#include "test.h"
#include <stdio.h>

int main()
{
    printf("\nprogram start\n");

    /* module */
    f1(1);

    /* library */
    f2(2);
    f3();
    f4();

    printf("program end\n\n");
    return 0;
}
