/*  
 *  suchar2.c -- uk�zka programu s chybou!
 *
 *  probl�m signed|unsigned char + EOF a konverze na int 
 *  chyba se chov� r�zn� podle implicitn�ho signed|unsigned char
 *
 */

#include <stdio.h>

int main()
{

#ifdef  WITH_ERROR		/* definujte WITH_ERROR pro chybnou funkci   */
    char			/* zde je hrub� chyba! */
#else
    int				/* tak to m� b�t */
#endif
     c;				/* prom�nn� pro jeden znak nebo EOF */

    printf("\n\n");
    printf(" zkuste znak '\xFF'   Alt_255 - program nesmi skoncit \n");
    printf(" zkuste EOF        Ctrl-Z (DOS), Ctrl-D (UNIX) - musi skoncit\n\n");

    while ((c = getchar()) != EOF)	/* �teme znaky ze stdin */
	putchar(c);     		/* opisujeme znaky na stdout */

    printf("\n***EOF***\n");
    return 0;
}
