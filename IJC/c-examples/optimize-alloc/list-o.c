
/* optimalizovana verze - alokace uzlu seznamu po blocich */

#include <stdio.h>
#include <stdlib.h>

/* prvek seznamu */
struct listitem {
    int data;
    struct listitem *next;
};

/* seznam */
struct list {
    struct listitem *first;
    struct listitem *last;
    unsigned long count;
};

/* sub-alokace prvku seznamu -- POZOR -- neresi ruseni */
#define LI_BSZ 10240		/* budeme alokovat ve velkem - pos kupinach */
struct listitem *listitem_new_sub(void)
{
    static struct listitem *li_block = NULL;
    static int next;
    if (!li_block) {
	/* allokujeme velky blok prvku */
	li_block = malloc(LI_BSZ * sizeof(struct listitem));
	next = 1;
	return li_block;	/* vratime prvni polozku */
    } else {
	struct listitem *li = &(li_block[next++]);	/* dalsi polozka */
	if (next == LI_BSZ)	/* byla posledni -- poznacime si */
	    li_block = NULL;
	return li;
    }
}

/* alokace prvku seznamu */
struct listitem *listitem_new(int x)
{
    struct listitem *li;
    li = listitem_new_sub();	/* vlastni alokace */
    if (li == NULL)
	exit(1);
    li->data = x;
    li->next = NULL;
    return li;
}

/* alokace seznamu */
struct list *list_new(void)
{
    struct list *l;
    l = malloc(sizeof(struct list));
    if (l == NULL)
	exit(1);
    l->first = NULL;
    l->last = NULL;
    l->count = 0;
    return l;
}

/* pridani do seznamu na konec */
void list_push_back(struct list *l, int x)
{
    struct listitem *li;
    li = listitem_new(x);
    if (l->last)		/* not empty */
	l->last->next = li;
    else
	l->first = li;
    l->last = li;		/* posledni prvek v seznamu */
}

/* TODO: dodelat ruseni za domaci ukol */

int main(int argc, char *argv[])
{
    long i;
    struct list *l;
    struct listitem *li;
    long n;
    if (argc != 2) {
	fprintf(stderr, "pouzijte: %s pocet\n", argv[0]);
	exit(2);
    }
    n = strtol(argv[1], NULL, 10);
    printf("Alokace %ld prvku...\n", n);
    l = list_new();
    for (i = 0; i < n; i++)
	list_push_back(l, i);
    printf("Scitani %ld prvku...\n", n);
    li = l->first;
    i = 0;
    while (li != NULL) {
	i += li->data;
	li = li->next;
    }
    printf("Vysledek mod 2^32: %ld \n\n", i);
    return 0;
}
