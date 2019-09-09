// htab_iterator.c 
// IJC-DU2, part b), 24.4.2019 
// Author: Ladislav Ondris, FIT, xondri07@stud.fit.vutbr.cz
// Compiled: gcc 8.3.1

#include <assert.h>
#include "htab_private.h"

static htab_iterator_t create_new_iterator(const htab_t * t, htab_item_t * item, const int index) {
    htab_iterator_t iterator;
    iterator.t = t;
    iterator.ptr = item;
    iterator.idx = index;
    return iterator;
}

htab_iterator_t htab_begin(const htab_t * t) {
    if (t->size > 0) {
        for (size_t i = 0; i < t->arr_size; i++) {
            if (t->arr[i] != NULL) {
                return create_new_iterator(t, t->arr[i], i);
            }
        }
    }
    return create_new_iterator(t, NULL, 0);
}

htab_iterator_t htab_end(const htab_t * t) {
    
    return create_new_iterator(t, NULL, 0);
}


htab_iterator_t htab_iterator_next(htab_iterator_t it) {
    assert(htab_iterator_valid(it));
    if (it.ptr->next != NULL) {
        return create_new_iterator(it.t, it.ptr->next, it.idx);
    }
    for (size_t i = it.idx + 1; i < it.t->arr_size; i++) {
        if (it.t->arr[i] != NULL) {
            return create_new_iterator(it.t, it.t->arr[i], i);
        }
    }
    return create_new_iterator(it.t, NULL, 0);
}

const char * htab_iterator_get_key(htab_iterator_t it) {
    assert(htab_iterator_valid(it));
    return it.ptr->key;
}

int htab_iterator_get_value(htab_iterator_t it) {
    assert(htab_iterator_valid(it));
    return it.ptr->data;
}
int htab_iterator_set_value(htab_iterator_t it, int val) {
    assert(htab_iterator_valid(it));
    return it.ptr->data = val;
}

