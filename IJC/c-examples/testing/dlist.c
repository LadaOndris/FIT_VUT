// dlist.c --- double-linked list implementation
// use gcc -std=c99 
// Author: P. Peringer, 2005, Public domain

/////////////////////////////////////////////////////////////////////////////
// interface

#include "dlist.h"

/////////////////////////////////////////////////////////////////////////////
// implementation
//
#include <stdlib.h>
#include <assert.h>

// list item
struct dlist_item {
    struct dlist_item *next;
    struct dlist_item *prev;
    data_t data;
};

// list
struct dlist {
    struct dlist_item *first;
    struct dlist_item *last;
    unsigned long n;
};

// create list
dlist *dlist_init(void)
{
    dlist *l = malloc(sizeof(dlist));
    if (l == NULL)
	return NULL;
    l->first = NULL;
    l->last = NULL;
    l->n = 0;
    return l;
}

// remove all items
void dlist_clear(dlist * l)
{
    while (l->first != NULL)
	dlist_remove(l, l->first);
}

// delete list
void dlist_destruct(dlist * l)
{
    dlist_clear(l);
    free(l);
}

// insert before position i (NULL means last)
void dlist_insert(dlist * l, dlist_pos i, data_t d)
{
    struct dlist_item *p = malloc(sizeof(struct dlist_item));
    if (p == NULL)
	exit(1);
    p->data = d;
    p->next = i;
    if (i) {			// not last
	p->prev = i->prev;
	if (p->prev)
	    i->prev->next = p;
	else			// insert first
	    l->first = p;
	i->prev = p;
    } else {			// insert last
	p->prev = l->last;
	if (p->prev)
	    p->prev->next = p;
	else			// single item in list
	    l->first = p;
	l->last = p;
    }
    l->n++;
}

// remove specified item
void dlist_remove(dlist * l, dlist_pos i)
{
    assert(i != NULL);
    if (i->prev)
	i->prev->next = i->next;
    else
	l->first = i->next;
    if (i->next)
	i->next->prev = i->prev;
    else
	l->last = i->prev;
    l->n--;
    free(i);
}

// number of items in list
unsigned long dlist_size(dlist * l)
{
    return l->n;
}

// first item
dlist_pos dlist_first(dlist * l)
{
    return l->first;
}

// last item
dlist_pos dlist_last(dlist * l)
{
    return l->last;
}

// get next item
dlist_pos dlist_next(dlist_pos i)
{
    return i->next;
}

// get previous item
dlist_pos dlist_prev(dlist_pos i)
{
    return i->prev;
}

// data access
data_t dlist_get_data(dlist_pos i) {
    return i->data;
}

data_t dlist_set_data(dlist_pos i, data_t d) {
    return i->data = d;
}

