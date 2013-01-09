#include <stdio.h>
#include <stdlib.h>

#ifndef _ATCLIB_LIST_H
#define _ATCLIB_LIST_H

#define LIST_FORW	0
#define LIST_BACK	2
#define LIST_FRNT	4
#define LIST_CURR	8
#define LIST_SAVE	32

#define LIST_ALTR 64
#define LIST_REAR	(16 | LIST_BACK)

#ifndef TRUE
#define TRUE  1
#endif
#ifndef FALSE
#define FALSE 0
#endif


typedef enum list_status { 
	LIST_EMPTY = 0, 
	LIST_OK = 1, 
	LIST_EXTENT = 2,
} list_status_t;

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

list_t atclib_list;

/* Function prototype */
list_t list_init ();
list_element_t create_Element (void *, size_t);
int m_Add (list_t, void *, int);
void m_Display ();
void m_Free_List ();
int list_empty(list_t);
typedef int (*list_traverse_func_t) (void *data, void *element);
list_status_t list_traverse(list_t list, void *data, list_traverse_func_t func, int opts);
int print_element (char *input, char *curr);

#endif	/* _ATCLIB_LIST_H */
