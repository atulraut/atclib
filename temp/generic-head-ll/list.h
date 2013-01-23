/*
* Aim  : WAP to implement Generic Linked list.
* Date : Monday, Jan 23 2013 10:41 PM
* By   : Atul R. Raut, Hyderabad
* File : list.h Implementation of Generic Link list using head method.
*
***/

#include <stdio.h>
#include <stdlib.h>

FILE *fr, *fw;
typedef struct node_t node;

typedef struct node_t {
	node *next;
	node *prev;
	void *data;
} node;

node *atclib_head;

int numEl;

node * createnode (void *, int len);
void addfirst (void *, int);
void list_print ();
