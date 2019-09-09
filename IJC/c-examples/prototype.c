/*  
 *  prototyp.c -- ukázka programu s chybou!
 *
 *  demonstrace nutnosti pou¾ívat prototypy funkcí v ISO C90/C99
 *
 */

#include <stdio.h>      /* prototyp  int printf(const char *, ...)   */

int main()              /* funkce main musí být jen jedna            */
{

  printf("Ukázka volání funkce bez deklarace\n");

  /* bez prototypu pøekladaè implicitnì pøedpokládá int f() */
  printf("Volání bez prototypu: i = f(1)\n");
  int i = f(1); /* funkce f dostane argument typu int, 
                   ale má ve skuteènosti parametr typu double 
                   -- hrubá CHYBA */
  /* pøekladaè varuje (gcc -Wall) 
   * prototype.c:18: warning: implicit declaration of function `f'
   */
  printf("Výsledek: %d\n", i);

  /* prototyp pøekladaè informuje jaké jsou parametry/typ funkce */
  int f(double x);

  printf("Volání s prototypem: i = f(1)\n");
  i = f(1);  /* pøekladaè automaticky provede konverzi: (double)1 
                a volání probìhne O.K. */
  printf("Výsledek: %d\n", i);

  return 0;
}

/* definice funkce -- mù¾e být v jiném modulu */
int f(double x)
{
    printf("Funkce dostala parametr x = %f\n", x);
    return x; /* tato funkce vrací celoèíselnou hodnotu x */
              /* Poznámka: zkuste si  x == 1e20 */
}

