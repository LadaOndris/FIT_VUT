// dlist.c --- double-linked list implementation
// use gcc -std=c99 
// Author: P. Peringer, 2005, Public domain

/////////////////////////////////////////////////////////////////////////////
// interface

#include "dlist.h"

/////////////////////////////////////////////////////////////////////////////
// implementation
//
//#include <stdlib.h>
//#include <assert.h>

// test of basic functionality

/////////////////////////////////////////////////////////////////////////////
// debugging
//
#include <stdio.h>

void dlist_print(dlist * l)
{
    printf("( ");
    dlist_pos p = dlist_first(l);
    while (p) {
	printf("%d ", dlist_get_data(p));
	p = dlist_next(p);
    }
    printf(") size=%ld\n", dlist_size(l));
}

/////////////////////////////////////////////////////////////////////////////
void dlist_remove_values(dlist * l, data_t d)
{
    dlist_pos p = dlist_first(l);
    while (p) {
	if (dlist_get_data(p) == d)
	    dlist_remove(l, p);
	p = dlist_next(p);
    }
}

void dlist_push_back(dlist * l, data_t d)
{
    dlist_insert(l, NULL, d);
}

/////////////////////////////////////////////////////////////////////////////
// basic test
//
int main(void)
{
    printf("Test of dlist implementation\n");

    // TODO: speed test?

    printf("creating list:\n");
    dlist *l = dlist_init();

    dlist_print(l);
    printf("inserting last:\n");
    for (int i = 0; i < 10; i++) {
	dlist_insert(l, NULL, i);
	dlist_print(l);
    }
    printf("removing first:\n");
    for (int i = 0; i < 10; i++) {
	dlist_remove(l, dlist_first(l));
	dlist_print(l);
    }

    printf("inserting first:\n");
    for (int i = 0; i < 10; i++) {
	dlist_insert(l, dlist_first(l), i);
	dlist_print(l);
    }
    printf("removing last:\n");
    for (int i = 0; i < 10; i++) {
	dlist_remove(l, dlist_last(l));
	dlist_print(l);
    }

    printf("\n");
    for (int i = 0; i < 10; i++) {
	dlist_insert(l, NULL, i);
	//dlist_print(l);
    }
    dlist_print(l);

    printf("removing second:\n");
    dlist_pos p = dlist_first(l);
    p = dlist_next(p);
    dlist_remove(l, p);
    dlist_print(l);

    printf("removing second from end:\n");
    p = dlist_last(l);
    p = dlist_prev(p);
    dlist_remove(l, p);
    dlist_print(l);

    printf("insert second:\n");
    p = dlist_first(l);
    p = dlist_next(p);
    dlist_insert(l, p, 100);
    dlist_print(l);

    printf("destructing list:\n");
    dlist_destruct(l);

    printf("done.\n");
    return 0;
}

