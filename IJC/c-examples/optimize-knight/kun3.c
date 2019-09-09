/* kun3.c
 *
 * linearizovano do pole --> skoky (x,y) jsou jen +-offset [jednodussi]
 *
 */

#include <stdio.h>
#include <stdlib.h>

int size = 5;
int maxlevel;

/* sachovnice */
#define MAX_SZ 8
#define MAX_STEP 8
#define ROW_SIZE (MAX_SZ+2*MAX_STEP)
char s[ROW_SIZE*ROW_SIZE];

/* mozne skoky */
int step[8] = {
     -1*ROW_SIZE +2, 
     +1*ROW_SIZE +2, 
     +2*ROW_SIZE +1, 
     +2*ROW_SIZE -1, 
     +1*ROW_SIZE -2, 
     -1*ROW_SIZE -2, 
     -2*ROW_SIZE -1, 
     -2*ROW_SIZE +1,
};

typedef enum { FALSE, TRUE } bool_t;

// makra pro prevod souradnic
#define XY2INDEX(x,y) ((x+MAX_STEP)*ROW_SIZE + y+MAX_STEP)
#define INDEX2X(x) (x/ROW_SIZE - MAX_STEP)
#define INDEX2Y(x) (x%ROW_SIZE - MAX_STEP)

void Init()
{
    int x, y;
    maxlevel = size * size;
    for (x = 0; x < sizeof(s)/sizeof(s[0]); x++)
	    s[x] = maxlevel+1; /* fill working area + dead-zone */
    for (y = 0; y < size; y++)
	for (x = 0; x < size; x++)
	    s[XY2INDEX(x,y)] = 0; /* working area */
}

void Print()
{
    int x, y;
    for (y = 0; y < size; y++) {
	for (x = 0; x < size; x++)
	    printf(" %2d ", s[XY2INDEX(x,y)]);
	printf("\n");
    }
    printf("\n");
}

bool_t Search(int x, int level)
{
    int i;
#ifdef DEBUG
    printf("Search(%d,%d,%d)\n", INDEX2X(x), INDEX2Y(x), level);
#endif

    if (s[x] != 0)		/* zde jsme uz byli NEBO jsme mimo sachovnici */
	return FALSE;

    s[x] = level;		/* poznaceni aktualni pozice */
    if (level == maxlevel)	/* konec: reseni je nalezeno */
	return TRUE;

    level++; // zkusime dalsi uroven
    for (i = 0; i < 8; i++) { // celkem 8 moznosti skoku
	if (Search(x + step[i], level)) 
	    return TRUE;	/* reseni bylo nalezeno */
    }
    s[x] = 0;     // tudy cesta nevede - uvolnime pozici
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
	    printf("start: [%d,%d]\n", x, y);
            Init();
	    if (Search(XY2INDEX(x,y), 1)) {
                // nejake reseni nalezeno
		++pocet_reseni;
		Print();
	    } else
		printf(" nema reseni\n\n");
	}
    printf("Pocet reseni: %d\n", pocet_reseni);
    return 0;
}
