/* faktorial.c 
 * Jazyk C -- tisk faktori�lu
 */

#include <stdio.h>
#include <limits.h>

/*
 * factorial - v�po�et faktori�lu ��sla n
 *
 * - p�i chyb� (n<0, p�ekro�en� meze long int) vrac� nulu
 *
 */
long factorial(int n)
{
  int i;
  long vysledek=1;
  if(n<0)
    return 0;                           /* chybov� hodnota */
  for(i=1; i<=n; i++)
  {
    if(vysledek > LONG_MAX/i)           /* test p�ekro�en� mez� */
      return 0;                         /* chybov� hodnota */
    vysledek *= i;
  }
  return vysledek;
}

/*
 * main - program tiskne faktori�ly ��sel od 0 do 12
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
