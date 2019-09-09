// hdump.c --- hexdump of memory conents
// use gcc -std=c99 
// Author: P. Peringer, 2005, Public domain

#include <stdio.h>
#include <locale.h>
#include "hdump.h"

int main(void)
{
    char *ptr = "test";
    printf("Test of hdump implementation\n");

    setlocale(LC_ALL, "");

    hdump(ptr, 1);
    printf("\n");

    hdump(ptr, 16);
    printf("\n");

    hdump((void*)main, 100);  // Warning: not ISO C

    hdump(ptr, -1);
    return 0;
}
