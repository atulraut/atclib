/***
* Aim : Generic Linklist.
* Date : Thursday, January 03 2013, 11:12 PM
* File : list.h
*/

#include <stdio.h>

enum status {
	LIST_OK=0,
	LIST_EMPTY,
	LIST_EXTEND, 
} list_status;

typedef struct list_element_t {
	list_element_t pFirst;
	list_element_t PLast;
	list_element_t pCurr;
}LIST_ELEMENT;

typedef struct {
	LIST_ELEMENT *prev;
	LIST_ELEMENT *next;
	void *data;
} NODE; 

NODE *atclib_list;
// function declaration
void atclib_init ();
