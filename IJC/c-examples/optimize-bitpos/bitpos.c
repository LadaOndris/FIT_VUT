/* bitpos.c
 * test efektivity algoritmu
 * POZOR: program predpoklada 32 bitovy unsigned long
 */

/* bitpos1
 * pozice prvniho nenuloveho bitu v cisle unsigned long
 */
unsigned bitpos1(unsigned long d)
{
#if 0
    unsigned i = 32 / 2;
    int pos = 32;
    if (d == 0) return 0;
    do {
	if (d >> i)
	    d >>= i;
	else
	    pos -= i;
    } while ((i /= 2) != 0);
    return pos;
#else
    int pos;
    if (d == 0) return 0;
    for (pos = 32; (d & ~(~0UL >> 1)) == 0; pos--)
        d <<= 1;
    return pos;
#endif
}

/* bitpos2
 * pozice prvniho nenuloveho bitu v cisle unsigned long
 * zacne na 32 
 * odecita 32/2, 32/4, 32/8, ... pokud jsou vyssi bity 0
 */
unsigned bitpos2(unsigned long d)
{
#if 1
    unsigned i = 32 / 2;
    int pos = 32;
    if (d == 0) return 0;
    do {
	if (d >> i)
	    d >>= i;
	else
	    pos -= i;
    } while ((i /= 2) != 0);
    return pos;
#else
    int pos;
    if (d == 0) return 0;
    for (pos = 32; (d & ~(~0UL >> 1)) == 0; pos--)
        d <<= 1;
    return pos;
#endif
}

unsigned empty(unsigned long d)
{
    return 0;
}

