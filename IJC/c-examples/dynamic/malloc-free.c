// malloc-free.c --- basic test of malloc and free
// use gcc -std=c99 
// Author: P. Peringer, 2005, Public domain

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    char *ptr;
    printf("Test of malloc() and free()\n");
    printf("ptr = %p [garbage]\n", ptr);
    for (int i = 0; i < 31; i++) {
	const long N = 1L << i; // 2^i
	printf("malloc(%ld):   \t", N);
	ptr = malloc(N);
	printf("ptr = %p\n", ptr);
	if (ptr == NULL) {
	    printf("No memory for malloc(%ld)\n", N);
	    exit(1);
	}
#if 0
	memset(ptr, 0, N); /* possible SIGSEGV in the case of "optimistic" allocation */
#endif
	free(ptr);
    }// for
    return 0;
}
