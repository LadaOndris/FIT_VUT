// htab_move.c 
// IJC-DU2, part b), 24.4.2019 
// Author: Ladislav Ondris, FIT, xondri07@stud.fit.vutbr.cz
// Compiled: gcc 8.3.1

#include <stdio.h>
#include <assert.h>
#include "htab_private.h"

htab_t *htab_move(size_t n, htab_t *from) {
    assert(from != NULL);
    
    htab_t *new_htab = htab_init(n);
    if (new_htab == NULL)
        return NULL;
    
    // Iterate through the old htab and move the items to the new htab.
    htab_iterator_t iterator = htab_begin(from);
    while (htab_iterator_valid(iterator)) {
        
        // Move the item to the new htab.
        const char *key = htab_iterator_get_key(iterator);
        htab_iterator_t new_item_iterator = htab_lookup_add(new_htab, key);
        
        if (!htab_iterator_valid(new_item_iterator)) {
            fprintf(stderr, "Invalid iterator: memory allocation failed. Couldn't move htab.\n");
            htab_free(new_htab);
            return NULL;
        }
        
        // Copy the value of the old htab to the new item in the new htab.
        int value = htab_iterator_get_value(iterator);
        htab_iterator_set_value(new_item_iterator, value);
        
        iterator = htab_iterator_next(iterator);
    }
    
    htab_clear(from);
    return new_htab;
}