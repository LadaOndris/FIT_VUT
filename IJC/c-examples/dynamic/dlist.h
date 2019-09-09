// dlist.h --- double-linked list interface
// use gcc -std=c99 
// Author: P. Peringer, 2005, Public domain
//
// Warning: fixed data type, slow

/////////////////////////////////////////////////////////////////////////////
// interface

// structure:
//
//   |next|--->|next|--->|next|-O
// O-|prev|<---|prev|<---|prev|  
//   |data|    |data|    |data|  
//   
//  first^               last^ 
//  n=3
// 

/////////////////////////////////////////////////////////////////////////////
// types
//
typedef int data_t; // type of data stored in list

struct dlist_item;  // internal type for list item
struct dlist;       // internal type for list

typedef struct dlist_item *dlist_pos;	// iterator type
typedef struct dlist dlist;             // list type

/////////////////////////////////////////////////////////////////////////////
// operations
//
dlist *dlist_init(void);          // constructor
void dlist_destruct(dlist * l);   // destructor

// insert operation
void dlist_insert(dlist * l, dlist_pos i, data_t d);

// delete operations
void dlist_remove(dlist * l, dlist_pos i);
void dlist_clear(dlist * l);

// iteration through list
dlist_pos dlist_first(dlist * l);
dlist_pos dlist_last(dlist * l);

dlist_pos dlist_next(dlist_pos i);
dlist_pos dlist_prev(dlist_pos i);

// status info
unsigned long dlist_size(dlist * l);

// data access is possible only this way (slow)
data_t dlist_get_data(dlist_pos i);
data_t dlist_set_data(dlist_pos i, data_t d);

// end of dlist.h
