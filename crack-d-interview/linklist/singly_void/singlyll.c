/*
* Aim : Singly Linked List.
* Date : Monday, July 29 2016 
* San Diego, CA
* By : Atul R. Raut
* valgrind -v --leak-check=full --show-reachable=yes ./main
***/
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

LIST * m_Init (){
  LIST *list;
  list = malloc (sizeof (LIST));
  list->head = NULL;
  return list;
}

LIST_NODE* m_CreateNodeL (int data){
        LIST_NODE *nn = NULL;
	nn = (LIST_NODE*)malloc(sizeof (LIST_NODE *));
	if (nn == NULL)
		return NULL;
	nn->data  = data;
	nn->next = NULL;
	return nn;
}

void m_Addfirst(int data, void *ptr) {
  LIST *list = (LIST *)ptr;
	LIST_NODE *nn = NULL;
	nn = m_CreateNodeL (data);
	nn->data = data;
	if (NULL == list->head) {
 	  list->head = (LIST *)nn;
	  nn->next = NULL;
	} else {
	  LIST_NODE *trav;
	  trav = (LIST_NODE *)list->head;
	  while (trav->next != NULL)
	    trav = trav->next;
	  trav->next = nn;
	  nn->next = NULL;
	}
}

void m_Delfirst(void *ptr) {
  LIST *ll = (LIST *)ptr; 
	if (ll == NULL)
		printf ("\n Empty Link List.");
	else {
		LIST_NODE *temp = NULL;
		temp = (LIST_NODE *)ll->head;
		if (temp->next == NULL) {
			free (temp);
			temp = NULL;
		}
		else {
			temp = (LIST_NODE *)ll->head;			
			ll->head = (LIST *)temp->next;		
			free (temp);
			temp = NULL;
		}				
	}
}

void m_Freelist(void *ptr) {
	LIST *ll = (LIST *)ptr;
	if (ll->head == NULL)
		printf ("\n Empty Link List.");
	else {
	  LIST_NODE *temp = NULL;
	  LIST_NODE *trav = NULL;
	  temp = (LIST_NODE *)ll->head;
	  while (temp != NULL) {
		  trav = temp->next;
		  free(temp);
		  temp = NULL;
		  temp = trav;
	  }
 	  ll->head = NULL;
	}
}

void m_Revlist(void *ptr) {
  LIST *ll = ptr;
  LIST_NODE *head = (LIST_NODE *)ll->head;
  LIST_NODE *trav;
  LIST_NODE *temp = head;
  head = NULL;
  while (temp != NULL) {
    trav = temp->next;
    temp->next = head;
    head = temp;
    ll->head = (LIST *)head;
    temp = trav;
  }
} 
/*
void m_RevRec(NODE **head_ref) {
  NODE *first;
  NODE *rest;
  printf ("**head_ref->[%p] *head_ref->[%p] \n", **head_ref, *head_ref);
  if (NULL == *head_ref)
    return;
  first = *head_ref;
  rest  = first->next;
  if (NULL == rest)
    return;

  m_RevRec (&rest);
  first->next->next = first;
  first->next = NULL;
  *head_ref = rest;
    
}
*/

void m_Sortlist(void *_list) {
  LIST *list = (LIST*)_list;
  LIST_NODE *head = (LIST_NODE*)list->head;
  LIST_NODE *start = head;
  LIST_NODE *trav, *min;
  while (start->next) {
    min = start;
    trav = start->next;
    while (trav) {
       if (min->data > trav->data) {
         min = trav;
       }
       trav = trav->next;
    }
    swap (start, min);
    start = start->next;
  }
  m_Display(_list);
}

void swap (LIST_NODE *s, LIST_NODE *m) {
  LIST_NODE *temp;
  temp = s->data;
  s->data = m->data;
  m->data = temp;
}

void m_Display(void *ptr){
	LIST *ll = (LIST *)ptr;
	printf ("\n----------:: Output ::-----------\n");
	LIST_NODE *temp = NULL;
	temp = (LIST_NODE*)ll->head;
	if (NULL == ll->head) {
		printf ("Empty link list \n");
		return;
	} else {
		while (temp != NULL) {
			printf ("->[%d]", temp->data);
			temp = temp->next;
		}
	}
	printf ("\n----------:: End ::-----------\n");
}

