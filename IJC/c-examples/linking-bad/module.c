/*  
 *  module.c -- ukázka programu s chybou!
 *
 */

/* ZDE CHYBÍ #include ROZHRANÍ tohoto modulu */

#include <stdio.h>      /* prototyp  int printf(const char *, ...)   */

/* definice funkce */
double f(double x)
{
    printf("Funkce ve skuteènosti dostala parametr x = %f \n", x);
    return x; 
}

