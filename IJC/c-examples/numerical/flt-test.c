/* flt-test.c 
 *
 * Program demonstruje vlastnosti v�po�tu v plovouc� ��rce
 * s nejvy��� p�esnost� (long double).
 *
 * (demonstruje p�esnost v�po�tu a vliv po�ad� p�i s��t�n�)
 *
 */

#include <stdio.h>
#include <float.h>		/* LDBL_EPSILON */

int main(void)
{
    long double x, y, delta = 0.001L, v;
    int i;

    /* vliv po�ad� v�po�tu: */
    x = 1.0L;
    y = 1e-16L;
    printf("\n");
    printf("Test presnosti vypoctu (long double)\n");
    printf("\n");
    printf("LDBL_EPSILON = %22.20Lf\n", LDBL_EPSILON);
    printf("x            = %22.20Lf\n", x);
    printf("y            = %22.20Lf\n", y);
    printf("\n");
    v = x + y + y;
    printf("x + y + y    = %22.20Lf\n", v);
    v = y + y + x;
    printf("y + y + x    = %22.20Lf\n", v);

    /* akumulace zaokrouhlovac�ch chyb: */
    x = 0.0L;
    for (i = 1; i <= 1000; i++) {
	x += delta;
	if (i % 100 == 0)
	    printf("\n0.0L + [%4d * 0.001L] = %22.20Lf", i, x);
    }
    printf(" %c= 1.0L \n", (x == 1.0L) ? '=' : '!');
    printf("\n");
    return 0;
}
