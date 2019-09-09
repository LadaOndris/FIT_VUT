#include <assert.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>

// pomocna funkce
// obecny prevod znaku na hodnotu cislice (az do zakladu 36)
int char2digit(int c)
{
    c = toupper(c);
    if (isdigit(c))
	return c - '0';
    if (isalpha(c))
	return c - 'A' + 10;
    else
	return 99;		// neni cislice v zadne soustave
}

unsigned long str2ul(const char *s, const char **p, int radix)
{
    unsigned long result = 0;
    int digit;

    assert(radix >= 2 && radix <= 36);

    // preskocime pripadne bile znaky
    while (isspace(*s))
	s++;

    // vlastni prevod  retezec->cislo
    while ((digit = char2digit(*s)) < radix) {
	// je dalsi platna cislice
	//// zde by byla pripadna kontrola preteceni
	result = result * radix + digit;
	s++;
    }
    // konec prevodu - neni dalsi cislice
    if (p)
	*p = s;			// vratime pozici, pokud je pozadovano (!=NULL)

    // vraceni vysledku
    return result;
}


bool ul2str(unsigned long x, int radix, char *s, int n)
{
    char *p = s;

    assert(radix >= 2 && radix <= 36);

    // vlastni prevod  cislo->retezec
    do {
	int digit = x % radix;	// koncova cislice
	x /= radix;		// odstraneni koncove cislice

	if (--n <= 0)		// kontrola limitu
	    return false;

	// prevod cislice na znak v retezci
	*s++ = (digit < 10) ? '0' + digit : 'A' + digit - 10;

    } while (x != 0);		// do-while zvladne dobre x==0

    // ukoncit C-string
    *s-- = '\0';

    // otocit poradi -- prevod ukladal obracene
    while (p < s) {
	int tmp = *p;
	*p = *s;
	*s = tmp;
        p++; s--;
    }

    return true;		// hotovo 
}

#define TEST(p)  do{ printf("%s\n",#p); p; }while(0)
#define N 80
#define RADIX 2

int main(void)
{
    unsigned long x = 12345;
    char s[N] = "";
    bool b;
    printf("\n");
    printf("RADIX = %d\n", RADIX);
    printf("sizeof(s) = %d\n", sizeof(s));
    printf("\n");
#if 1
    TEST(b = ul2str(x, RADIX, s, sizeof(s)));
    if (b)
	printf("uspesny prevod: %lu -> \"%s\"\n", x, s);
    else
	printf("NEuspesny prevod: %lu -> \"%s\"\n", x, s);
    printf("\n");
#endif
    const char *p;
    TEST(x = str2ul(s, &p, RADIX));
    printf("prevod: \"%s\" -> %lu\n", s, x);
    printf("prevod skoncil na pozici: %d v \"%s\"\n", p - s, s);
    printf("\n");
    return 0;
}

