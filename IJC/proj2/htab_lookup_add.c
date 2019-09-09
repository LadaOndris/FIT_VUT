// htab_lookup_add.c 
// IJC-DU2, part b), 24.4.2019 
// Author: Ladislav Ondris, FIT, xondri07@stud.fit.vutbr.cz
// Compiled: gcc 8.3.1

#include <stdlib.h>
#include <string.h>
#include "htab_private.h"


static inline char *strdup(const char *str) {
    int str_len = strlen(str);
    char *new_str = malloc(str_len + 1);
    if (new_str == NULL)
        return NULL;
    strcpy(new_str, str);
    return new_str;
}

static inline htab_item_t *create_new_item(const char *key) {
    htab_item_t *item = malloc(sizeof(htab_item_t));
    if (item == NULL)
        return NULL;
    
    char *copied_key = strdup(key);
    if (copied_key == NULL) {
        free(item);
        return NULL;
    }
    
    item->next = NULL;
    item->key = copied_key;
    item->data = 0;
    return item;
}

static inline htab_iterator_t get_iterator(htab_item_t * item, htab_t *t, int index) {
    htab_iterator_t iterator;
    iterator.ptr = item;
    iterator.t = t;
    iterator.idx = index;
    return iterator;
}

htab_iterator_t htab_lookup_add(htab_t *t, const char *key) {
    unsigned int hash = htab_hash_function(key);
    
    int item_index = hash % t->arr_size;
    htab_item_t *item_ptr = t->arr[item_index];
    htab_item_t *previous_item_ptr = NULL;
    
    // search for the item
    while (item_ptr != NULL) {
        if (strcmp(item_ptr->key, key) == 0) {
            break;
        }
        
        previous_item_ptr = item_ptr;
        item_ptr = item_ptr->next;
    }
    // item wasn't found, create new one and add it into the table
    if (item_ptr == NULL) {
        item_ptr = create_new_item(key);
        if (item_ptr == NULL)
            return get_iterator(NULL, t, 0);    // allocation failed
            
        if (previous_item_ptr == NULL) {
            t->arr[item_index] = item_ptr;
        }
        else {
            previous_item_ptr->next = item_ptr;
        }
        t->size++;
    }
    // return an iterator pointing to the found item
    return get_iterator(item_ptr, t, item_index);
}
