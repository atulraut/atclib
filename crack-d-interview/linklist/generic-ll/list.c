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
    return (_list);
}

list_node * create_node (void *_data, size_t len) {
	list_node *newNode = NULL;
	newNode = (list_node*) malloc (sizeof (list_node));
	if (len > 0) {
		newNode->data = (char *) malloc (len);	
		if (newNode->data == NULL) {
			free(newNode);
			return NULL;
		} else {
			newNode->data = (char*) _data;
		}		
	}
	return newNode;
}

void list_add (list *_list, void *_data, size_t len) {
	list_node *newNode = NULL;
	newNode = create_node (_data, len);
	if (NULL == newNode)
		printf ("\nFailed to allocate memory");
	else {
		_list->NumEl += 1;
		if(_list->NumEl == 1) {
			newNode->next = newNode->prev= NULL;
			_list->pFirst = _list->pLast = _list->pCurr = newNode;
		}
	}
}

void list_print (list *_list) {
	int i;
	printf ("\nHi Print = %d\n", _list->NumEl);
	for(i=0; i<_list->NumEl; i++) {
		printf("\nAT::-->%d", (char *)_list->pFirst->data);
	}
}

