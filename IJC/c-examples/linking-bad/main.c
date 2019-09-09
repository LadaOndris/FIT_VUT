/*  
 *  main.c -- uk�zka programu s chybou!
 *
 *  demonstrace nutnosti pou��vat prototypy funkc� v ISO C
 *
 *  N�zorn� uk�zka co dok�e chybn� proveden� modularita:
 *
 *  Bez prototypu p�eklada� nem��e t�m�� nic zkontrolovat.
 *  Chov�n� viz ISO C99 (6.5.2.2 paragraf 6). 
 *  P�eklada� m��e hl�sit chybu nebo pouze varov�n� - podrobnosti
 *  viz C99 Rationale - sekce 6.5.2.2.
 *
 */

/* ZDE CHYB� #include ROZHRAN� modulu obsahuj�c�ho definici funkce f() */

#include <stdio.h>		/* prototyp  int printf(const char *, ...)   */

int main()
{				/* funkce main mus� b�t jen jedna            */

    printf("P��klad chyby p�i vol�n� funkce bez prototypu\n");
    printf("Vol�n� f(x) m� spr�vn� vr�tit hodnotu argumentu x\n\n");

    /* p�i vol�n� bez prototypu p�eklada� implicitn� p�edpokl�d�: int f()    */
    /* ale funkce je ve skute�nosti: double f(double)                        */

    printf("int i = f(1);\n");
    int i = f(1);		/* CHYBA: parametr i n�vratov� hodnota       */
    printf("i = %d\n", i);

    printf("double d = f(1.0);\n");
    double d = f(1.0);		/* CHYBA: n�vratov� hodnota                  */
    printf("d = %g\n", d);

    return 0;
}
