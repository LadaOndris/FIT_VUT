/* align-test.c --- test of alignment
 * use with GCC on x86 with RDTSC instruction (Pentium+,K6,...) 
 * Author: P. Peringer, 1999-2005, Public domain
 * 
 * use optimization: gcc -O2
 *
 * Sample output on Athlon64/2GHz:
 * ==============================
 *
 * Timing of (un)aligned data access
 * copy 100 items cache->cache
 * item size = sizeof(long) = 4
 *
 * aligned/unaligned time in CPU clocks
 *    416 / 416  (offset=0)
 *    416 / 616  (offset=1)
 *    420 / 626  (offset=2)
 *    415 / 615  (offset=3)
 * 
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * rdtsc() --- reading Pentium+, K6, ... 64 bit timer (GNU C/C++ only)
 */
#ifndef __GNUC__
#error "use GNU C, please"
#endif

__inline long long rdtsc()
{
    register long long edxeax;
    __asm __volatile__("rdtsc":"=A"(edxeax));
    return edxeax;
}

#define MAX      100		/* array length (should be small) */

long long test(long *t, long *x)
{
    long long start;
    long long end;
    long long dt = 1000000;
    int i, n;
    for (n = 0; n < 10; n++) {	/* 10 experiments */
	start = rdtsc();
	for (i = 0; i < MAX; i++) {
	    x[i] = t[i];	/* copy */
	}
	end = rdtsc();
	if (end - start < dt)
	    dt = end - start;	/* minimum */
    }
    return dt;
}

void test_align(int offset)
{
    long *t = (long *) malloc(MAX * sizeof(long) + offset);
    long *x = (long *) malloc(MAX * sizeof(long) + offset);
    if (x == NULL || t == NULL) {
	printf("not enough memory\n");
	exit(1);
    }
    /* fill cache(s) */
    test(t, x);
    /* aligned access */
    printf("   %lld / ", test(t, x));
    /* unaligned access with offset */
    t = (long *) (((char *) t) + offset);
    x = (long *) (((char *) x) + offset);
    printf("%lld  (offset=%d)\n", test(t, x), offset);
}

int main(void)
{
    int i;
    printf("Timing of (un)aligned data access\n");
    printf("copy %d items cache->cache\n", MAX);
    printf("item size = sizeof(long) = %d\n", sizeof(long));
    printf("\n");
    printf("aligned/unaligned time in CPU clocks\n");

    for (i = 0; i < sizeof(long); i++) 
	test_align(i);
    
    return 0;
}
