/* bits.c
 * test efektivity algoritmu
 * POZOR: program predpoklada 32 bitovy unsigned long
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "bitpos.h"

#define PRINT1 0
#define PRINT2 0

/*  rdtsc
 *  function for reading 64 bit timer (Pentium, K6, etc.) 
 *  for GNU C/C++ only 
 */
#ifndef __GNUC__
#error "use GNU C, please"
#endif
__inline long long rdtsc(void)
{
    register long long edxeax;
    __asm __volatile__("rdtsc":"=A"(edxeax));	// compiler-dependent
    return edxeax;
}

#define N 20
int ucmp(const void *a, const void *b)
{
    return *(unsigned *) a < *(unsigned *) b;
}

double test(unsigned (*f) (unsigned long), unsigned (*e) (unsigned long))
{
    long long t, t1, t2, t3;
    double avgt;
    unsigned pos;
    int i, j;
    unsigned sumt = 0;
#if PRINT1
    printf("* ");
#endif
    for (i = 0; i < 32; i++) {
	unsigned ta[N];
	for (j = 0; j < N; j++) {
	    unsigned long x = 1 << i;
	    t1 = rdtsc();
//	    pos = e(x);		/* kompenzace volani funkce */
	    t2 = rdtsc();
	    pos = f(x);
	    t3 = rdtsc();
	    t = t3 - t2 - (t2 - t1);
	    ta[j] = t;		/* zaznam mereni */
//printf("%d\n", (unsigned)(t2-t1));
	    if (pos != i + 1)
		fprintf(stderr, "bitpos() test error\n");
	}
	qsort(ta, N, sizeof(unsigned), ucmp);
#if PRINT1
	printf("%d%c", ta[N / 2], (i == 32 - 1) ? '\n' : ' ');
#endif
#if PRINT2
	printf("# ");
	for (int k = 0; k < N; k++)
	    printf("%d%c", ta[k], (k == N - 1) ? '\n' : ' ');
#endif
	sumt += ta[N / 2];    /* median */
    }
    avgt = sumt / 32.0;
    return avgt;
}

int main(int argc, char *argv[])
{
    int i;
    const char *s = argv[0];
    test(bitpos1, empty);
    test(bitpos1, empty);
    test(bitpos2, empty);
    test(bitpos2, empty);
    for(i=0;i<10;i++)
        printf("%6.1f clocks bitpos1 (%s)\n", test(bitpos1, empty), s);
    for(i=0;i<10;i++)
        printf("%6.1f clocks bitpos2 (%s)\n", test(bitpos2, empty), s);
    return 0;
}
