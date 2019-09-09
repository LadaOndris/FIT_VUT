
#define HTABLE_SIZE 1024  /* size can be changed - velikost tabulky lze menit */

/* hash function - rozptylovac� funkce */
unsigned int hash_function(char *str)
{
    unsigned int h = 0;
    unsigned char *p; /* should be unsigned - mus� b�t unsigned */
    for (p = (unsigned char *) str; *p != '\0'; p++)
	h = 31 * h + *p;
    return h % HTABLE_SIZE;
}


