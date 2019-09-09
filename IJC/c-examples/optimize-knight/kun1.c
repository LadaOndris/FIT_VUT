/* kun1.c
 *
 * zakladni varianta
 *
 */

#include <stdio.h>
#include <stdlib.h>

int size = 5;
int maxlevel;

/* sachovnice */
#define MAX_SZ 8
char s[MAX_SZ][MAX_SZ];

/* mozne skoky */
struct {
    int x;
    int y;
} step[8] = {
    { -1, +2}, { +1, +2}, { +2, +1}, { +2, -1}, 
    { +1, -2}, { -1, -2}, { -2, -1}, { -2, +1},
};

typedef enum { FALSE, TRUE } bool_t;

void Init()
{
    int x, y;
    maxlevel = size * size;
    for (y = 0; y < size; y++)
	for (x = 0; x < size; x++)
	    s[x][y] = 0;
}

void Print()
{
    int x, y;
    for (y = 0; y < size; y++) {
	for (x = 0; x < size; x++)
	    printf(" %2d ", s[x][y]);
	printf("\n");
    }
    printf("\n");
}

static bool_t Inside(int x, int y)
{
    return ((unsigned) x) < size && ((unsigned) y) < size;
}

bool_t Search(int x, int y, int level)
{
    int i;
#ifdef DEBUG
    printf("Search(%d,%d,%d)\n", x, y, level);
#endif
    if (level <= 1)
	Init();
    if (!Inside(x, y))		/* bod mimo sachovnici */
	return FALSE;
    if (s[x][y] != 0)		/* zde jsme uz byli */
	return FALSE;
    s[x][y] = level;		/* poznaceni pozice */
    if (level == maxlevel)	/* konec: reseni je nalezeno */
	return TRUE;
    for (i = 0; i < 8; i++) {
	if (Search(x + step[i].x, y + step[i].y, level + 1)) {
	    return TRUE;	/* reseni bylo nalezeno */
	}
    }
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
	    printf("start: [%d,%d]\n", x, y);
	    if (Search(x, y, 1)) {
		++pocet_reseni;
		Print();
	    } else
		printf(" nema reseni\n\n");
	}
    printf("Pocet reseni: %d\n", pocet_reseni);
    return 0;
}
