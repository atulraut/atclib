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

list * init_list (list *_list_atclib) {
  _list_atclib = (list *)malloc(sizeof (list));
  if (NULL != list_atclib) {
    _list_atclib->pFirst = NULL;
    _list_atclib->pLast  = NULL;
    _list_atclib->pCurr  = NULL; 
    _list_atclib->numEl  = 0;
  }
  return (_list_atclib);
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

int add_list (list *_list_atclib, void *_data, size_t _len) {
  node *new = NULL;
  node *trav=  NULL;
  new = create_list (_data, _len);
  if (NULL != new) {
    _list_atclib->numEl++;
    printf ("\n numEl = %d, address head=%p, address_new=%p\n", _list_atclib->numEl, _list_atclib, new);
    if ( _list_atclib->numEl == 1) {
      printf ("Generic Link List \n");
      _list_atclib->pFirst = new;
      new->next = new->prev; 
    } else {
      trav = _list_atclib->pFirst;
      while (_list_atclib->pLast != trav)
	trav = trav->next;
      trav->next = new;
    }
    _list_atclib->pLast = new;
  }
  return 1;
}

/*< m_Addfirst : Add first to linklist  >*/
int m_Addfirst (node *_list, void *_data, size_t _len) {
  printf ("\nm_Addfirst = %s\n", (char *)_data);
}

/*< reverse_list: reverse the link list>*/
void reverse_list(list *_list) { // Fix Me
  printf ("\nReverse link list\n");
  node *trav = NULL;
  node *temp = NULL;
  /*  trav = _list->pFirst;
  while (trav != _list->pLast->next)
    trav = trav->next;
*/
  temp = _list->pLast;
  _list->pLast = _list->pFirst;
  _list->pFirst = temp;
  trav = _list->pFirst;
  while (trav != temp) {
    printf ("-->[%s]", (char*)trav->data);
    fputs((char*)trav->data, fw);
    fputc ('\n', fw);
    trav = trav->next;
  }
}

/*< print_list: print and write to file the linkl list >*/
void print_list (list *_list) {
  node *trav = NULL;
  trav = _list->pFirst;
  
  if ( _list->numEl == 0) {
    printf ("\nlist empty = %d, address=%p\n",  _list->numEl, _list);
    return;
   }
  
  while (trav != _list->pLast->next) {
    printf ("-->[%s]", (char*)trav->data);
    fputs((char*)trav->data, fw);
    fputc ('\n', fw);
    trav = trav->next;
    }
  printf ("\n\n");
}
