/*
 * ackerman-o.c --- vypocet Ackermanovy funkce, castecne optimalizovana verze
 *
 * POZOR! - skonci na "stack overflow"
 * 
 */

#include <stdio.h>

/* rozmer pomocne tabulky v minulosti jiz vypocitanych hodnot */
#define XM 3
#define YM 100000

long long Ack(int x, int y)
{
    static long long a[XM][YM] = { { 0, }, };	/* tabulka hodnot - "cache" */
    if (x > 0) {
	if ((unsigned) x <= XM && (unsigned) y < YM) {	/* possibly in cache */
	    if (a[x-1][y] == 0)	                /* not in cache */
		a[x-1][y] = Ack(x-1, (y > 0) ? Ack(x, y-1) : 1);
	    return a[x-1][y];
	}
	return Ack(x-1, (y > 0) ? Ack(x, y-1) : 1);
    } else
	return y + 1;
}

int main()
{
    int x, y;
    printf("\n x y");
    for (y = 0; y < 10; y++)
	printf("| %4d ", y);
    printf("\n----");
    for (y = 0; y < 10; y++)
	printf("+------");
    for (x = 0; x < 5; x++) {
	printf("\n%2d  ", x);
	for (y = 0; y < 10; y++) {
	    printf("| %4lld ", Ack(x, y));
	    fflush(stdout);
	    if (x == 4 && y == 1)
		break; /* konec */
	}
    }
    printf("\n");
    return 0;
}
