/*
* Aim  : WAP to implement Generic Linked list.
* Date : Monday, Jan 23 2013 10:41 PM
* By   : Atul R. Raut, Hyderabad
* File : list.h Implementation of Generic Link list using head method.
*
***/
#include "list.h"

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
 
void addfirst (void *_data, int len) {
	node *newNode = NULL;
	newNode = createnode (_data, len);
	printf ("\nstr = %s, len = %d\n", (char *)_data, len);
	if (NULL == newNode)
		printf ("\nFailed to allocate Memory !\n");
	else {
		numEl += 1;
		if (numEl == 1) {   // add first
		      	if (atclib_head == NULL) {
                	atclib_head = newNode;      
               		atclib_head->next = NULL;
        		} else {
                		newNode->next = atclib_head;
                		atclib_head = newNode;
        		}
		} else { 		
			node *trav = NULL;
			trav = atclib_head;
			while (trav->next != NULL){
				trav = trav->next;
			}
			trav->next = newNode;
			trav = newNode;
			trav->next = NULL;
			trav = NULL;
		}
	} // first if end.
}

void list_print (node *_list) {
 	node *temp = NULL;
        temp = atclib_head;
        while (temp != NULL) {
                printf ("->[%s]", (char *)temp->data);
		fputs((char *)temp->data, fw);
		fputc('\n', fw);
                temp = temp->next;
        }
}
