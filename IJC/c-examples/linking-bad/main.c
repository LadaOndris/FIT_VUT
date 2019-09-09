/*  
 *  main.c -- ukázka programu s chybou!
 *
 *  demonstrace nutnosti pou¾ívat prototypy funkcí v ISO C
 *
 *  Názorná ukázka co doká¾e chybnì provedená modularita:
 *
 *  Bez prototypu pøekladaè nemù¾e témìø nic zkontrolovat.
 *  Chování viz ISO C99 (6.5.2.2 paragraf 6). 
 *  Pøekladaè mù¾e hlásit chybu nebo pouze varování - podrobnosti
 *  viz C99 Rationale - sekce 6.5.2.2.
 *
 */

/* ZDE CHYBÍ #include ROZHRANÍ modulu obsahujícího definici funkce f() */

#include <stdio.h>		/* prototyp  int printf(const char *, ...)   */

int main()
{				/* funkce main musí být jen jedna            */

    printf("Pøíklad chyby pøi volání funkce bez prototypu\n");
    printf("Volání f(x) má správnì vrátit hodnotu argumentu x\n\n");

    /* pøi volání bez prototypu pøekladaè implicitnì pøedpokládá: int f()    */
    /* ale funkce je ve skuteènosti: double f(double)                        */

    printf("int i = f(1);\n");
    int i = f(1);		/* CHYBA: parametr i návratová hodnota       */
    printf("i = %d\n", i);

    printf("double d = f(1.0);\n");
    double d = f(1.0);		/* CHYBA: návratová hodnota                  */
    printf("d = %g\n", d);

    return 0;
}
