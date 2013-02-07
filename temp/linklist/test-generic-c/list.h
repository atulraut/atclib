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
typedef struct node_ node;

typedef struct node_ {
    node *prev;
    node *next;
    void *data;
    int numEl;
} node;

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

node *head;

node * init_list (node *);
node * create_list (void *, size_t);

int add_list (node *, void *, size_t);
int m_Addfirst (node *, void *, size_t);

void print_list ();
