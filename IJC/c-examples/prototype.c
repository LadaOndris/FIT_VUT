/*  
 *  prototyp.c -- uk�zka programu s chybou!
 *
 *  demonstrace nutnosti pou��vat prototypy funkc� v ISO C90/C99
 *
 */

#include <stdio.h>      /* prototyp  int printf(const char *, ...)   */

int main()              /* funkce main mus� b�t jen jedna            */
{

  printf("Uk�zka vol�n� funkce bez deklarace\n");

  /* bez prototypu p�eklada� implicitn� p�edpokl�d� int f() */
  printf("Vol�n� bez prototypu: i = f(1)\n");
  int i = f(1); /* funkce f dostane argument typu int, 
                   ale m� ve skute�nosti parametr typu double 
                   -- hrub� CHYBA */
  /* p�eklada� varuje (gcc -Wall) 
   * prototype.c:18: warning: implicit declaration of function `f'
   */
  printf("V�sledek: %d\n", i);

  /* prototyp p�eklada� informuje jak� jsou parametry/typ funkce */
  int f(double x);

  printf("Vol�n� s prototypem: i = f(1)\n");
  i = f(1);  /* p�eklada� automaticky provede konverzi: (double)1 
                a vol�n� prob�hne O.K. */
  printf("V�sledek: %d\n", i);

  return 0;
}

/* definice funkce -- m��e b�t v jin�m modulu */
int f(double x)
{
    printf("Funkce dostala parametr x = %f\n", x);
    return x; /* tato funkce vrac� celo��selnou hodnotu x */
              /* Pozn�mka: zkuste si  x == 1e20 */
}

