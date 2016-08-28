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
  NODE *trav = list->head;
  NODE *nn = create_node (_data);
  if (NULL == list->head) {
    list->head = nn;  
    nn->prev = list->head;
    nn->next = list->head;
  } else {
    while (trav->next != list->head)
      trav = trav->next;
    trav->next = nn;
    nn->prev = trav;
    nn->next = list->head;
  }
  printf ("list->head = %p \n", list->head);
  printf ("trav= %p \n", trav);
} 

void m_display (void *_list) {
  LIST *list = (LIST *) _list;
  NODE *trav = list->head;
  if (NULL == list->head) {
    printf ("Empty ! \n");
    return; 
  }  
  while (trav->next != list->head) {
    printf ("->[%d]", trav->data);
    trav = trav->next;
  }
  printf ("->[%d]", trav->data);
}

void m_free (void *_list) {
  LIST *list = (LIST *) _list;
  NODE *trav = list->head;
  NODE *temp;
  if (NULL == list->head) {
    printf ("Empty ! \n");
    return; 
  } 
  while (trav != NULL) {
    printf ("data->[%p], head->[%p]", trav, list->head);
    if (trav->next == list->head) {
	trav->next = NULL;
	trav->prev = NULL;
	free (trav);
	trav = NULL;
    } else {
      temp = trav;
      trav = trav->next;
      temp->next = NULL;
      temp->prev = NULL;
      trav->prev = NULL;
      free(temp);
      temp = NULL;
    }
  }
  list->head = NULL;
}

void m_Printrev(void *_list) {
  LIST *list = (LIST *)_list;
  NODE *temp = list->head;
  NODE *save = list->head;
  NODE *trav = list->head;
  if (NULL == list->head) {
    printf ("Empty ! \n");
    return; 
  } 
  printf ("head = %p\n", list->head);
  while (trav->next != list->head) {
    trav = trav->next;
  }
  list->head = trav;
  while (trav != save) {  
    trav = temp->next;
    temp->next = list->head;
    temp->prev = trav;
    list->head = temp;
    temp = trav;
  }
} 
