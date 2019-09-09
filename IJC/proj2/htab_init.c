// htab_init.c 
// IJC-DU2, part b), 24.4.2019 
// Author: Ladislav Ondris, FIT, xondri07@stud.fit.vutbr.cz
// Compiled: gcc 8.3.1

#include <stdlib.h>
#include <stddef.h>
#include "htab_private.h"

htab_t *htab_init(size_t n) {
    htab_t *htab = malloc(sizeof(htab_t) + n * sizeof(struct htab_item_t *));
    if (htab == NULL)
        return NULL;
    htab->size = 0;
    htab->arr_size = n;
    for (size_t i = 0; i < n; i++) {
        htab->arr[i] = NULL;
    }
    return htab;
}

