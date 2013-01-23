#include "list.h"

node * list_init (node *_list) {
	_list = (node*)malloc(sizeof(node));
	_list->next = NULL;
	_list->prev = NULL;
	_list->data = NULL;
	numEl = 0;
}

node * createnode (void *_data, int len) {
	node *newNode = NULL;
	newNode = (node*)malloc(sizeof(node));
	if (NULL != newNode) {
		newNode->next = NULL;
		newNode->prev = NULL;
		newNode->data = (char*)malloc(sizeof (len));
		if (NULL == newNode->data) {
			free (newNode->data);
			newNode->data = NULL;
			return -1;
		} else {
			newNode->data = (char *)_data;
		} // 2nd if end.
	} else 
		printf ("\nFailed to allocate Memory !");
	return newNode;
}

void addfirst (node *_list, void *_data, int len) {
	node *newNode = NULL;
	newNode = createnode (_data, len);
	printf ("\nstr = %s, len = %d\n", (char *)_data, len);
	if (NULL == newNode)
		printf ("\nFailed to allocate Memory !\n");
	else {
		numEl += 1;
		if (numEl == 1) {   // add first
		      	_list->prev = NULL;	     
			_list = newNode;
			_list->next = NULL;
			printf ("\n @@@@_list->datae = %s\n", (char *)_list->data);
		} else { 		
			node *trav = NULL;
			trav = _list;
			while (trav->next != NULL){
				printf ("\n$$$$$\n");
				trav = trav->next;
				printf ("\n@@@@@@\n");
			}
			trav->next = newNode;
			trav = newNode;
			trav->next = NULL;
			printf ("\n::newNode = %s\n", (char *)trav->data);
			trav = NULL;
		}
	} // first if end.
}

void list_print (node *_list) {
	node *trav = NULL;
	if (_list->data == NULL)
		printf ("\n_list is empty\n");
	else
		printf ("\n_list->data %s\n", (char*)_list->data);
	trav = _list;
	printf ("ATUL-->[%s], numEl = %d\n\n", (char *)_list->data, numEl);
	while (trav != NULL) {
		printf ("-->[%s]", (char *)trav->data);
/*		if (NULL != fw) {
			fputs((char *)trav->data, fw);
			fputc('\n', fw);
		} else 
*/		trav = trav->next;
	}
}
