
/* kun2.c
 * 
 * vetsi sachovnice okoli je zakazano --> test pozice Inside() odpada.
 *
 * POZOR: nemusi byt rychlejsi
 *
 */

#include <stdio.h>
#include <stdlib.h>

int size = 5;
int maxlevel;

/* sachovnice */
#define MAX_SZ 8
#define MAX_STEP 8  /* je vhodne volit celkovou velikost 2^N */

// vetsi sachovnice
char s[MAX_SZ+2*MAX_STEP][MAX_SZ+2*MAX_STEP];

/* mozne skoky */
struct {
    int x;
    int y;
} step[8] = {
    { -1, +2}, { +1, +2}, { +2, +1}, { +2, -1}, 
    { +1, -2}, { -1, -2}, { -2, -1}, { -2, +1},
};

typedef enum { FALSE, TRUE } bool_t;

// inicializace sachovnice
void Init()
{
    int x, y;
    maxlevel = size * size;
    for (y = 0; y < size+2*MAX_STEP; y++)
	for (x = 0; x < size+2*MAX_STEP; x++)
	    s[x][y] = maxlevel+1; /* okoli je poznaceno */
    for (y = 0; y < size; y++)
	for (x = 0; x < size; x++)
	    s[x+MAX_STEP][y+MAX_STEP] = 0; /* pracovni oblast sachovnice */
}

// tisk sachovnice s poradim obsazovanych poli
void Print()
{
    int x, y;
    for (y = 0; y < size; y++) {
	for (x = 0; x < size; x++)
	    printf(" %2d ", s[x+MAX_STEP][y+MAX_STEP]);
	printf("\n");
    }
    printf("\n");
}

// hledani reseni rekurzivnim prohledavanim do hloubky
bool_t Search(int x, int y, int level)
{
    int i;
#ifdef DEBUG
    printf("Search(%d,%d,%d)\n", x, y, level);
#endif
    // prepocet souradnic z duvodu pridaneho okoli,
    // tj. prevod logicka pozice --> fyzicka pozice:
    x+=MAX_STEP;
    y+=MAX_STEP;

    if (level <= 1)
	Init();
    if (s[x][y] != 0)		/* zde jsme uz byli nebo jsme mimo sachovnici */
	return FALSE;
    // aktualni pozice je volna:
    s[x][y] = level;		/* poznaceni pozice */
    if (level == maxlevel)	/* konec: reseni je nalezeno */
	return TRUE;
    // zkousime vsech 8 moznosti skoku kone:
    for (i = 0; i < 8; i++) {
        // Search vyzaduje logickou pozici, (proto -MAX_STEP):
	if (Search(x - MAX_STEP + step[i].x, y - MAX_STEP + step[i].y, level + 1)) {
	    return TRUE;	/* reseni bylo nalezeno */
	}
    }
    // reseni nenalezeno - vracime se a uvolnujeme aktualni pozici:
    s[x][y] = 0;
    return FALSE;		/* zadny tah nevyhovuje */
}

int main(int argc, char *argv[])
{
    int pocet_reseni = 0;
    int x, y;

    if (argc > 1) {
	size = strtol(argv[1], 0, 10);
	if (size < 4 || size > MAX_SZ) {
	    printf("povolena velikost sachovnice je 4..%d\n", MAX_SZ);
	    return 1;
	}
    }

    for (y = 0; y < size; y++)
	for (x = 0; x < size; x++) {
	    printf("Pocatecni pozice: [%d,%d]\n", x, y);
	    if (Search(x, y, 1)) {
		++pocet_reseni;
		Print();
	    } else
		printf(" nema reseni\n\n");
	}
    printf("Celkovy pocet reseni: %d\n", pocet_reseni);
    return 0;
}
