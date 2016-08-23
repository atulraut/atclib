#include <stdio.h>
#include <stdlib.h>
#include "list.h"

LIST *init_list (void *_list) {
  _list = (LIST *) malloc (sizeof(LIST));
  LIST *list = (LIST *)_list;
  if (NULL == list)
    return NULL;
  list->head = NULL;
  return list;
}

NODE *create_node (int _data) {
  NODE *nn = (NODE *)malloc(sizeof(NODE));
  if (NULL == nn)
    return NULL;
  nn->data = _data;
  nn->next = NULL;
  nn->prev = NULL;
  return nn;
} 

void m_add (void *_list, int _data) {
  LIST *list = (LIST *) _list;
  NODE *nn = NULL;
  nn = create_node (_data);
  if (NULL == list->head) { // first Node
	  nn->prev = list->head;
	  list->head = nn;	  
  } else {  // add last
	  NODE *trav = list->head;
	  while (NULL != trav->next)
	     trav = trav->next;
	  trav->next = nn;
	  nn->prev = trav;
  }	  
} 

void m_display (void *_list) {
  LIST *list = (LIST *)_list;
  if (NULL == list->head) {
    printf ("List is Empty\n");
    return;
  }
  NODE *trav = list->head;
  while (NULL != trav) {
    printf ("->[%d]", trav->data);
    trav = trav->next;
  }
}

void m_free (void *_list) {
  LIST *list = (LIST *)_list;
  NODE *temp = NULL;
  if (NULL == list->head) {
    printf ("Empty\n");
    return;
  }
  printf ("list->head = %p \n", list->head);  
  NODE *trav = list->head;  
  while (trav != NULL) {
    if (trav->next == list->head) { /*if only 1 node in list*/
      trav->next = NULL;
      free(trav);
      trav = NULL;
    } else {
      printf ("list->head = %p \n", list->head);  
      temp = trav; 
      trav = trav->next;
      free(temp);
      temp = NULL;
    }
  }
  list->head = NULL;  /* make sure to clear head as it points to nothig here */
}

void m_Printrev(void *_list) {
  LIST *list = (LIST *)_list;
  NODE *temp = list->head;
  list->head = NULL;
  NODE *trav = NULL;
  while (NULL != temp->next) {
    printf ("temp ->[%d]", temp->data);
    trav = temp->next;
    temp->next = list->head;
    list->head = temp;
    temp->prev - list->head;
    temp = trav;
  }
  temp->next = list->head;
} 
