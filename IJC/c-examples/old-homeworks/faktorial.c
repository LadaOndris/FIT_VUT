/* faktorial.c 
 * Jazyk C -- tisk faktoriálu
 */

#include <stdio.h>
#include <limits.h>

/*
 * factorial - výpoèet faktoriálu èísla n
 *
 * - pøi chybì (n<0, pøekroèení meze long int) vrací nulu
 *
 */
long factorial(int n)
{
  int i;
  long vysledek=1;
  if(n<0)
    return 0;                           /* chybová hodnota */
  for(i=1; i<=n; i++)
  {
    if(vysledek > LONG_MAX/i)           /* test pøekroèení mezí */
      return 0;                         /* chybová hodnota */
    vysledek *= i;
  }
  return vysledek;
}

/*
 * main - program tiskne faktoriály èísel od 0 do 12
 */
int main(void)
{
  int n;
  printf("---------------\n");
  for(n=0; n<=12; n++)
    printf("%2d! = %9ld \n", n, factorial(n));
  printf("---------------\n");
  return 0;
}

/* konec */
