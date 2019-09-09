// hdump.c --- hexdump of memory conents
// use gcc -std=c99 
// Author: P. Peringer, 2005, Public domain

#include "hdump.h"

#include <stdio.h>
#include <ctype.h>

// print of memory contents from address a 
// format:
// ADDRESS  HH HH HH ..... HH HH  cccccccccccccccc
//
void hdump(const char *a, unsigned long size)
{
    const char *b = a + size;
    const char *addr = (const char *) ((unsigned long) a & ~0x000F);
    while (addr < b) {
	// address, always aligned to 16B boundary
	printf("%08lX  ", (unsigned long) addr);
	// hex numbers
	for (const char *i = addr; i < addr + 0x10; i++)
	    if (i < a || i >= b)
		printf("   ");
	    else
		printf("%02X ", *(unsigned char *) i);
	printf(" ");
	// characters
	for (const char *i = addr; i < addr + 0x10; i++)
	    if (i < a || i >= b)
		printf(" ");
	    else
		printf("%c", isprint(*i) ? *i : '.');
	printf("\n");
	addr += 16;
    }
}

#if 0
int main(void)
{
    char *ptr = "test";
    printf("Test of hdump implementation\n");

//    setlocale(LC_ALL, "");

    hdump(ptr, 1);
    printf("\n");

    hdump(ptr, 16);
    printf("\n");

    hdump(main, 100);

    hdump(ptr, -1);
    return 0;
}
#endif
