/* cos-tab.c 
 *
 * Program tiskne tabulku funk�n�ch hodnot funkce cos(x) z�skanou
 * v�po�tem �ady a standardn� funkc� cos() s p�esnost� double.
 * 
 * Sledujte nep�esnost v�po�tu sou�t� a vliv po�tu �len� �ady
 * 
 * UPOZORN�N�: nejde o efektivn� �e�en�, 
 *             program sestavte s matematickou knihovnou (-lm)
 * 
 * Po�et prvk� �ady lze zadat jako argument programu (implicitn� 10).
 * 
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int N = 10;			/* implicitn� po�et prvk� �ady */

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
    /* v�po�et prvk� �ady, s��t�n� od konce pro vy��� p�esnost
     * 
     *  cos(x) = 1 - frac{x^2}{2!} + frac{x^4}{4!} - frac{x^6}{6!} + ...
     *  
     *  plat� pro x v rozsahu -1 .. 1
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
