/*
* Aim  : WAP to implement Generic Linked list.
* Date : Saturday, Feb 2nd & 3rd 2013 12:00 AM
* By   : Atul R. Raut
* File : list.c method defination generic linked list.
*
***/

#include <stdio.h>
#include <stdlib.h>

#include "list.h"

node * init_list (node *list) {
  list = (node *)malloc(sizeof (node));
  if (NULL != list) {
    list->prev = NULL;
    list->next = NULL;
    list->data = NULL;
    list->numEl = 0;
  }
  return (list);
}

node * create_list (void *_data, size_t _len) {
  node *new = NULL;
  new = (node *)malloc(sizeof (node));
  if (NULL != new) {
    new->prev = NULL;
    new->next = NULL;
    new->data = (char *)malloc(sizeof (_len));
    if (NULL == new->data) {
      free (new->data);
      free (new);
    } else {
      new->data = _data;
    } // 2nd if end
  } // 1st if end
  return (new);
}

int add_list (node *_list, void *_data, size_t _len) {
  node *new = NULL;
  new = create_list (_data, _len);
  if (NULL != new) {
    _list->numEl++;
    if (_list->numEl == 1) {
      printf ("Generic Link List \n");
      head = new;
      head->next = NULL;
    } else {
      node *trav = NULL;
      trav = head;
      while (trav->next != NULL)
      trav = trav->next;
      trav->next = new;
      trav = new;
      trav->next = NULL;			
    }
  }
  return 1;
}

/*< m_Addfirst : Add first to linklist  >*/
int m_Addfirst (node *_list, void *_data, size_t _len) {
  printf ("\nm_Addfirst = %s\n", (char *)_data);
}

/*< print_list: print and write to file the linkl list >*/
void print_list () {
  node *trav = NULL;
  trav = head;
  printf ("\n");
  while (trav != NULL) {
    printf ("-->[%s]", (char*)trav->data);
    fputs((char*)trav->data, fw);
    fputc ('\n', fw);
    trav = trav->next;
  }
  printf ("\n\n");
}
