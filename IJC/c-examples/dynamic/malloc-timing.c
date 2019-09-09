// malloc-timing.c --- test of malloc() and free() speed
// use with GCC on x86 with RDTSC instruction (Pentium+,K6,...) 
// use gcc -std=c99 
// Author: P. Peringer, 2005, Public domain

#include <stdio.h>
#include <stdlib.h>

// rdtsc() --- reading Pentium+, K6, ... 64 bit timer (GNU C/C++ only)
#ifndef __GNUC__
#error "use GNU C, please"
#endif
inline long long rdtsc()
{
    register long long edxeax;
    __asm __volatile__("rdtsc":"=A"(edxeax));
    return edxeax;
}

long long test(long size)
{
    long long start;
    long long end;
    long long dt = 1000000000;
    int n;
    char *ptr;
    for (n = 0; n < 10; n++) {
	start = rdtsc();
	ptr = malloc(size);
	end = rdtsc();
        if(ptr==NULL) {
            printf("No memory for malloc(%ld)\n", size);
            exit(1);
        }
	free(ptr);
	if (end - start < dt)
	    dt = end - start;	// minimum 
    }
    return dt;
}

long long test2(long size)
{
    long long start;
    long long end;
    long long dt = 1000000000;
    int n;
    char *ptr;
    for (n = 0; n < 10; n++) {	// 10 mereni
	ptr = malloc(size);
        if(ptr==NULL) {
            printf("No memory for malloc(%ld)\n", size);
            exit(1);
        }
	start = rdtsc();
	free(ptr);
	end = rdtsc();
	if (end - start < dt)
	    dt = end - start;	// minimum 
    }
    return dt;
}

// main test
int main(void)
{
    printf("Timing of malloc() [min time, no fragmentation]\n");
    for (int i = 0; i < 31; i++) {
	const long N = 1L << i;
	printf("malloc(%ld):  \t %lld clocks\n", N, test(N));
	printf("free(%ld):    \t %lld clocks\n", N, test2(N));
    }
    return 0;
}
