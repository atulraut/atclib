/*
* Aim  : WAP to implement Generic Linked list.
* Date : Saturday, January 5th & 6th 2013 12:00 PM
* By   : Atul R. Raut
* File : list.c implementation of generic linked list.
*
***/

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

list * list_init (list *_list) {
    _list = (list*)malloc(sizeof(list));
    if (_list == NULL)
      printf ("\nFailed to allocate memory.\n");
    else {
            _list->NumEl = 0;
            _list->pFirst = NULL;
            _list->pLast  = NULL;
            _list->pCurr  = NULL;
    }
    printf ("\nsizeof = %d\n", sizeof(_list));
    return (_list);
}

list_node * create_node (void *_data, int len) {
    list_node *newNode = NULL;
    newNode = (list_node*) malloc (sizeof (list_node));
    if (len > 0) {
       newNode->data = (char *) malloc (len+1);
       if (newNode->data == NULL) {
          free(newNode);
          return NULL;
       } else {
         newNode->data = (char*) _data;
       }
    }
    return newNode;
}

void list_add (list *_list, void *_data, int len) {
    list_node *newnode = NULL;
    newnode = create_node (_data, len);
    if (NULL == newnode)
        printf ("\nfailed to allocate memory");
    else {
         _list->NumEl += 1;
	 printf ("\n_list->NumEl = %d, address=%p\n", _list->NumEl, _list);
         if(_list->NumEl == 1) {
            _list->pFirst = newnode;
            newnode->next = NULL;
            newnode->prev = NULL;
         } else {
           newnode->prev = _list->pLast;
           newnode->next = NULL;
           _list->pLast->next = newnode;
	 }
	 _list->pLast = newnode;
    } // first else end
}

void list_print (list *_list) {
    list_node *temp = NULL;
    temp = _list->pFirst;
    printf ("\n [print] Link cnt=%d, address=%p\n", _list->NumEl,  _list);
    if (_list->NumEl == 0) {
      printf ("\n [print] Link List is empty\n");
      return;
    }

    while (temp != _list->pLast->next) {
         printf("-->[%s]", (char *)temp->data);
         fputs((char *)temp->data, fw);
         fputc('\n', fw);
         temp = temp->next;
    }
    printf ("\n\n");
}
