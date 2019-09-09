// htab_private.h 
// IJC-DU2, part b), 24.4.2019 
// Author: Ladislav Ondris, FIT, xondri07@stud.fit.vutbr.cz
// Compiled: gcc 8.3.1
// Note: This file contains declarations of opaque data types 
// not visible to the user of the library.

#ifndef HTAB_PRIVATE_H
#define HTAB_PRIVATE_H

#include "htab.h"

typedef struct htab_item htab_item_t;

struct htab {
    size_t size;
    size_t arr_size;
    htab_item_t *arr[];
};

struct htab_item {
    char *key;
    int data;
    struct htab_item *next;
};

#endif // HTAB_PRIVATE_H