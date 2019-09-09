/*
 * this is simple test of interrupt service time
 *
 * Process is interrupted by timer and other hardware interrupts,
 *         it can be suspended, context can be switched, etc...
 *         
 * Comments:
 *   - we display only interrupt time greater than MINCYCLES
 *   - this program uses long long
 *   - use with GCC and optimization -O2 
 *
 * Public domain. Author: peringer AT fit.vutbr.cz
 *
 */

#include <stdio.h>
#include <stdlib.h>

/* change next line */
double MHz = 2000.0;		/* CPU clock frequency [Linux: /proc/cpuinfo] */

long MAX = 100;			/* how much interrupts */

#define MINCYCLES 250		/* minimal clock count displayed */

/*
 * conversion: function clocks --> time in seconds
 */
double T(long long dt)
{
    return dt / MHz / 1e6;
}

/*
 * rdtsc() --- function for reading Pentium+, K6, ... 64 bit timer
 * (GNU C/C++ only)
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

long long *m;			/* duration */
long long *t;			/* time */

long long start;
long long end;

int main(int argc, char *argv[])
{
    int i;
    long long a, b, dt;
    fprintf(stderr, "Timming of interrupts ...\n");
    /* parse arguments */
    if (argc > 2) {
	printf("usage: %s number_of_ints \n", argv[0]);
	return 1;
    }
    if (argc > 1)
	MAX = atol(argv[1]);
    if (MAX < 1 || MAX > 100000) {
	printf("bad number of interrupts (1..100000 is allowed)\n");
	return 1;
    }
    /* allocate memory */
    t = (long long *) malloc(MAX * sizeof(long long));
    m = (long long *) malloc(MAX * sizeof(long long));
    if (m == NULL || t == NULL) {
	printf("not enough memory\n");
	return 1;
    }
    /* touch memory buffers to eliminate page-faults */
    for (i = 0; i < MAX; i++) {
	t[i] = 0;
	m[i] = 0;
    }
    /* wait to interrupt */
    start = rdtsc();
    a = start;
    for (;;) {
	b = rdtsc();
	dt = b - a;
	if (dt > MINCYCLES) {
	    break;
	}
	a = b;
    }
    /* start after interrupt for more readable output */
    start = a;
    a = start;
    i = 0;
    for (;;) {
	b = rdtsc();
	dt = b - a;
	if (dt > MINCYCLES) {
	    t[i] = a;
	    m[i] = dt;
            if(++i >= MAX) 
                break; /* end after MAX records */
	}
	a = b;
    }
    end = rdtsc();
    /* print time of interrupts: */
    printf("# Expected processor clock: %.3f MHz\n\n", MHz);
    printf("#    time [us]   dt [us] \n");
    for (i = 0; i < MAX; i++)
	printf("%4d %9.2f %9.1f \n", i, T(t[i] - start) * 1e6, T(m[i]) * 1e6);
    printf("# Total time: %f s\n", T(end - start));
    fprintf(stderr, "Done.\n");
    return 0;
}

