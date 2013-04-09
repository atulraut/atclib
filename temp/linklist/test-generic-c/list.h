/*
* Aim  : WAP to implement Generic Linked list.
* Date : Saturday, Feb 2nd & 3rd 2013 12:00 AM
* By   : Atul R. Raut
* File : list.h skeleton to generic linked list.
*
***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fr, *fw;
typedef struct node_t node;
typedef struct node_list_t list;

typedef struct node_t {
    node *prev;
    node *next;
    void *data;
} node;

typedef struct node_list_t {
  node *pFirst;
  node *pLast;
  node *pCurr;
  int numEl;
} list;

node *list_atclib;

list * init_list (list *);
node * create_list (void *, size_t);

int add_list (list *, void *, size_t);
//int m_Addfirst (node *, void *, size_t);
void reverse_list(list *);

void print_list (list *);

typedef enum list_type {
    LIST_EXIT = 0,
    LIST_ADD,
    LIST_ADD_FIRST,
    LIST_ADD_LAST,
    LIST_DELETE_FIRST,
    LIST_DELETE_LAST,
    LIST_DELETE,
    LIST_PRINT,
    LIST_REVERSE,
    LIST_FREE
} list_action;

typedef enum input_type {
    ONE_STRING = 0,
    TWO_INT
} input_type;
