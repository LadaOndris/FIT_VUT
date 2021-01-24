//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     Ladislav Ondris <xondri07@stud.fit.vutbr.cz>
// $Date:       $2019-02-19
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author Ladislav Ondris
 * 
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include <stdio.h>

#include "tdd_code.h"

//============================================================================//
// ** ZDE DOPLNTE IMPLEMENTACI **
//
// Zde doplnte implementaci verejneho rozhrani prioritni fronty (Priority Queue)
// 1. Verejne rozhrani fronty specifikovane v: tdd_code.h (sekce "public:")
//    - Konstruktor (PriorityQueue()), Destruktor (~PriorityQueue())
//    - Metody Insert/Remove/Find a GetHead
//    - Pripadne vase metody definovane v tdd_code.h (sekce "protected:")
//
// Cilem je dosahnout plne funkcni implementace prioritni fronty implementovane
// pomoci tzv. "double-linked list", ktera bude splnovat dodane testy 
// (tdd_tests.cpp).
//============================================================================//

PriorityQueue::PriorityQueue() {
    head = NULL;
}

PriorityQueue::~PriorityQueue() {
    Element_t *prev = NULL;
    for (Element_t *e = GetHead(); e != NULL; e = e->pNext) {
        if (prev)
            free(prev);
        prev = e;
    }
    if (prev)
        free(prev);
}

void PriorityQueue::Insert(int value) {
    Element_t *new_element = NewElement(value);
    
    Element_t *before = NULL;
    Element_t *after = NULL;
    
    for (Element_t *element = head; element != NULL; element = element->pNext) {
        if (element->value > value) {
            after = element;
            before = element->pPrev;
            break;
        }
        if (element->pNext == NULL) {
            before = element;
        }
    }
    
    if (before && after) { // insert between elements
        before->pNext = new_element;
        after->pPrev = new_element;
        new_element->pPrev = before;
        new_element->pNext = after;
    } else if (after) { // add to the beginning of a list
        new_element->pNext = after;
        after->pPrev = new_element;
        head = new_element;
    } else if (before) { // add to the end of a list
        before->pNext = new_element;
        new_element->pPrev = before;
    } else { // no element in a list yet
        head = new_element;
    }
}

bool PriorityQueue::Remove(int value) {
    Element_t *to_be_removed = Find(value);
    if (to_be_removed == NULL)
        return false;
    
    if (to_be_removed->pPrev && to_be_removed->pNext) {
        to_be_removed->pPrev->pNext = to_be_removed->pNext;
        to_be_removed->pNext->pPrev = to_be_removed->pPrev;
    } else if (to_be_removed->pNext) {
        to_be_removed->pNext->pPrev = NULL;
        head = to_be_removed->pNext;
    } else if (to_be_removed->pPrev) {
        to_be_removed->pPrev->pNext = NULL;
    } else {
        head = NULL;
    }
    free(to_be_removed);
    return true;
}

PriorityQueue::Element_t *PriorityQueue::Find(int value) {
    for (Element_t *e = head; e != NULL; e = e->pNext) {
        if (e->value == value)
            return e;
    }
    return NULL;
}

PriorityQueue::Element_t *PriorityQueue::GetHead() {
    return head;
}


// Protected methods

PriorityQueue::Element_t *PriorityQueue::NewElement(int value) {
    Element_t *element = (Element_t *) malloc(sizeof(Element_t));
    if (element == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return NULL;
    }
    element->value = value;
    element->pPrev = NULL;
    element->pNext = NULL;
    return element;
}


/*** Konec souboru tdd_code.cpp ***/
