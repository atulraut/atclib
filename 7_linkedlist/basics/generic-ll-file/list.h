/*
* Aim  : WAP to implement Generic Linked list.
* Date : Saturday, January 5th & 6th 2013 12:00 PM
* By   : Atul R. Raut
* File : list.h skeleton for generic linked list.
*
***/

#include <stdio.h>
#include <stdlib.h>
#define DEBUG 1

FILE *fw, *fr;

typedef struct list_node_t list_node;
typedef struct list_t list;

struct list_node_t {
   list_node *prev;
   list_node *next;
   void *data;
  //int NumEl;
};

struct list_t {
   list_node *pFirst;
   list_node *pLast;
   list_node *pCurr;
   int NumEl;
};

enum list_status {
   OK = 0,
   EMPTY,
   EXTEND
} LIST_STATUS;

list_node *atclib_list; // create empty list, can create no. of such list

list * list_init (list *);
list_node * create_node (void *, int);
void list_add (list *, void *, int);
void list_print (list *);
