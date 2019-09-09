/*  
 *  suchar2.c -- ukázka programu s chybou!
 *
 *  problém signed|unsigned char + EOF a konverze na int 
 *  chyba se chová rùznì podle implicitního signed|unsigned char
 *
 */

#include <stdio.h>

int main()
{

#ifdef  WITH_ERROR		/* definujte WITH_ERROR pro chybnou funkci   */
    char			/* zde je hrubá chyba! */
#else
    int				/* tak to má být */
#endif
     c;				/* promìnná pro jeden znak nebo EOF */

    printf("\n\n");
    printf(" zkuste znak '\xFF'   Alt_255 - program nesmi skoncit \n");
    printf(" zkuste EOF        Ctrl-Z (DOS), Ctrl-D (UNIX) - musi skoncit\n\n");

    while ((c = getchar()) != EOF)	/* èteme znaky ze stdin */
	putchar(c);     		/* opisujeme znaky na stdout */

    printf("\n***EOF***\n");
    return 0;
}
