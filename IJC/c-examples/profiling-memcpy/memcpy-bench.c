/*
 *  memcpy-bench.c --- basic test of memory access speed
 *  Warning: it is not exact!
 *
 *  Example of inline assembly language support in GCC
 *  Uses instruction RDTSC (supported on all modern x86 processors)
 *
 */

/* max size of buffers */
#define MSIZE (10*1024*1024L)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 *  function for reading Pentium+, K6, ... 64 bit timer
 */
__inline unsigned long long rdtsc()
{
    register unsigned long long edxeax;
    __asm __volatile__("rdtsc":"=A"(edxeax));
    return edxeax;
}

/* static buffers */
char buffer[MSIZE];
char buffer2[MSIZE];

void print_time(long long delta, long size)
{
    const double dt = (double) delta;   /* time in clk */
    printf("%10.3f %6.4f\n", size / 1024.0, size / dt);       /* KB, B/clk */
    fflush(stdin);
}

void MEASURE(unsigned long size)
{
    int k;
    unsigned long long start;
    unsigned long long delta;
    unsigned long long mintime;
    memcpy(buffer2, buffer, size);      /* cache fill */
    /* 1 */
    start = rdtsc();
    memcpy(buffer2, buffer, size);
    mintime = rdtsc() - start;          /* time */
    /* 2...N */
    for (k = 0; k < 5; k++) {
        start = rdtsc();
        memcpy(buffer, buffer2, size);
        delta = rdtsc() - start;        /* time */
        if (delta < mintime)
            mintime = delta;            /* take minimum */
        start = rdtsc();
        memcpy(buffer2, buffer, size);
        delta = rdtsc() - start;        /* time */
        if (delta < mintime)
            mintime = delta;            /* take minimum */
    } /* for */
    print_time(mintime, size);          /* print fastest */
}

/* main test */
int main(int argc, const char *argv[])
{
    int n, size, x=0;
    int step;
    unsigned end = sizeof(buffer);
    if (argc > 1)
        end = atoi(argv[1]) * 1024 * 1024L;
    if (end > sizeof(buffer))
        end = sizeof(buffer);
#if 1
    /* try without this initialization -- interesting results */
    for (n = 0; n < sizeof(buffer); n++) {
        buffer[n] = x = x * 13 + 111;
        buffer2[n] = x = x * 7 + 333;
    }
#endif
    printf("# data for GNUPLOT\n");
    printf("# PARAMETERS: sizeof(buffer) = %ld KB\n",
           sizeof(buffer) / 1024L);
    printf
        ("# block size in KB      transfer rate in B/clock\n\n");

    for (size = 128; size < end; size += step) {
        MEASURE(size);
        unsigned long i;
        for (i = 1L << 8; i < size; i <<= 1)
            /* empty */ ;
        step = i >> 5;
    }
    return 0;
}
