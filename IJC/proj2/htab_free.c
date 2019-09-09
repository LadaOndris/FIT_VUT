// htab_free.c 
// IJC-DU2, part b), 24.4.2019 
// Author: Ladislav Ondris, FIT, xondri07@stud.fit.vutbr.cz
// Compiled: gcc 8.3.1

#include <stdlib.h>
#include <assert.h>
#include "htab_private.h"

void htab_clear(htab_t * t) {
    if (t == NULL)
        return;
        
    for (size_t i = 0; i < t->arr_size; i++) {
        htab_item_t *next = t->arr[i];
        htab_item_t *current = NULL;
        
        while (next != NULL) {
            current = next;
            next = current->next;
            free(current->key);
            free(current);
            t->arr[i] = NULL;
        }
    }
    t->size = 0;
}

void htab_free(htab_t * t) {
    htab_clear(t);
    free(t);
    t = NULL;
}