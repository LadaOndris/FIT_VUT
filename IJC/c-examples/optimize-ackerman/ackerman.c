/*
 * ackerman.c --- vypocet Ackermanovy funkce
 *
 * POZOR! - skonci na "stack overflow"
 *
 */

#include <stdio.h>

long long Ack(int x, int y)
{
    if (x > 0)
	return Ack(x - 1, (y > 0) ? Ack(x, y - 1) : 1);
    else
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

