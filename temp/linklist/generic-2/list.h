#include <stdio.h>
#include <stdlib.h>

#ifndef _ATCLIB_LIST_H
#define _ATCLIB_LIST_H

/* Define a structure to describe the list. */
struct list;
/* A list handle. */
typedef struct list *list_t;

struct list_element;
typedef struct list_element *list_element_t;

//#define LIST struct list; 

struct list {
  size_t size;
  list_element_t pFirst;
  list_element_t pLast;
  list_element_t pCurr;
 };

struct list_element {
  list_element_t next;
  list_element_t prev;
  void *data;
};


/* Function prototype */
list_t list_init ();
list_element_t create_Element (void *, size_t);
int m_Add (list_t, void *, int);
void m_Display ();
void m_Free_List ();

#endif /* _ATCLIB_LIST_H */
