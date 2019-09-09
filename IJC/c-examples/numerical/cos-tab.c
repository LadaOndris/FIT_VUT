/* cos-tab.c 
 *
 * Program tiskne tabulku funkèních hodnot funkce cos(x) získanou
 * výpoètem øady a standardní funkcí cos() s pøesností double.
 * 
 * Sledujte nepøesnost výpoètu souètù a vliv poètu èlenù øady
 * 
 * UPOZORNÌNÍ: nejde o efektivní øe¹ení, 
 *             program sestavte s matematickou knihovnou (-lm)
 * 
 * Poèet prvkù øady lze zadat jako argument programu (implicitnì 10).
 * 
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int N = 10;			/* implicitní poèet prvkù øady */

double factorial(int i)
{
    double x = 1.0L;
    while (i > 1)
	x *= i--;
    return x;
}

double my_cos(double x)
{
    double sum;
    int i;
    /* výpoèet prvkù øady, sèítání od konce pro vy¹¹í pøesnost
     * 
     *  cos(x) = 1 - frac{x^2}{2!} + frac{x^4}{4!} - frac{x^6}{6!} + ...
     *  
     *  platí pro x v rozsahu -1 .. 1
     *
     */
    sum = 0;
    for (i = N - 1; i >= 0; i--)
	sum += ((i & 1) ? -1 : 1) * pow(x, 2 * i) / factorial(2 * i);
    return sum;
}

int main(int argc, char *argv[])
{
    double x;
    if (argc == 2)
	N = atoi(argv[1]);
    if (N < 1 || N > 50)
	return 1;
    for (x = -1.0; x <= 1.0; x += 0.01) {
	double y = my_cos(x);
	double y2 = cos(x);
	printf("%21.16f | %21.16f | %g\n", x, y, y2 - y);
    }
    return 0;
}
