/*
* Aim : Singly Linked List.
* Date : Monday, March 26 2012 05:15 PM
* End  : Monday, April 02 2012 06:00 PM
* By : Atul R. Raut
*
***/
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct list_t *head = NULL;

void m_Init (struct list_t *node){
	node->data = 0;
	node->next = NULL;
}

struct list_t* m_CreateNodeL (int data){
	struct list_t *nn = NULL;
	nn = (struct list_t*)malloc(sizeof (struct list_t));
	if (nn == NULL)
		return NULL;
	nn->data  = data;
	nn->next = NULL;
	return nn;
}

void m_Addfirst(int data) {
	struct list_t *nn = NULL;
	nn = m_CreateNodeL (data);

	if (head == NULL) {
		head = nn;
		head->next = NULL;
	} else {
		nn->next = head;
		head = nn;
	}
}

void m_Addlast(int data) {
	struct list_t *nn = NULL;
	nn = m_CreateNodeL (data);

	if (head == NULL)
		m_Addfirst (data);
	else {
		struct list_t *temp = NULL;
		temp = head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = nn;
		nn->next = NULL;
	}
}

void m_Insert(int pos, int data){
	int cnt = 0; // initialise to 0;
	struct list_t *temp = NULL;
	struct list_t *nn = NULL;
	temp = head;
	while (temp->next != NULL) {
		temp = temp->next;
		cnt++;
	}
	if (pos < 1) {
		printf ("\n Enter valid input\n");
		return;
	} else {
		nn = m_CreateNodeL (data);
		if (cnt == 1 || head == NULL)
			m_Addfirst (data);
		 else {
			 temp = head; // Re-assing temp
			 for (cnt=1; pos<cnt; cnt++) {
				 printf ("\nam inside for loop");
				 temp = temp->next;
				 cnt++;
			 }
			 temp->next = nn;
			 nn->next = NULL;
		 }
	}
}

void m_Delfirst() {
	if (head == NULL)
		printf ("\n Empty Link List.");
	else {
		struct list_t *temp = NULL;
		if (head->next == NULL) {
			free (head);
			head = NULL;
		}
		else {
			temp = head;
			head = head->next;
			free (temp);
			temp = NULL;
		}
	}
}

void m_Dellast() {
	if (head == NULL)
		printf ("\n Empty Link List.");
	else {
		struct list_t *temp = NULL;
		struct list_t *tmp  = NULL;
		if (head->next == NULL) {
			free (head);
			head = NULL;
		}
		else {
			temp = head;
			while (temp->next->next != NULL) {
				temp = temp->next;
			}
			tmp = temp->next;
			temp->next = NULL;
			free (tmp);
			tmp = NULL;
		}
	}
}

void m_Deletenode(int data) {
	struct list_t *temp = NULL;
	struct list_t *tmp  = NULL;
	temp = head;
	while (temp != NULL) {
		if (temp->next != NULL) {
			if (temp->next->data == data) {
			  printf ("\n Data found deleting Node !\n");
			  tmp = temp->next;
			  if (temp->next->next != NULL)
				temp->next = temp->next->next;
			   else
				temp->next = NULL;
			   free (tmp);
			   tmp = NULL;
			}
		} else {
			m_Delfirst ();
		}
		if (temp != NULL)
			temp = temp->next;
	}
}

void m_Printrev () {
	struct list_t *trav = NULL;
	struct list_t *temp = NULL;
	if (head == NULL) {
		printf ("\nEmpty link list.\n");
	} else {
		printf ("\n Inside Reverse Link List\n");
		// Logic to reverse link list.
		temp = head;
		head = NULL;
		while (temp != NULL) {
		        printf ("temp=[%p][%d]\n", temp,temp->data);
			trav = temp->next;
			temp->next = head; // attach NODE
			head = temp;     // L1 Make NULL, L2 Attach Node
			temp = trav;
			printf ("temp=[%p][%d]\n", temp,temp->data);
		}
	}
}

/***
    https://leetcode.com/problems/plus-one-linked-list/
    369. Plus One Linked List
    iven a non-negative integer represented as a linked list of digits, plus one to the integer.
    The digits are stored such that the most significant digit is at the head of the list.
    Example 1:
    Input: head = [1,2,3]
    Output: [1,2,4]Example 2:
    Input: head = [0]
    Output: [1]
    Constraints:
    The number of nodes in the linked list is in the range [1, 100].
    0 <= Node.val <= 9
    The number represented by the linked list does not contain leading zeros except for the zero itself.

*/
struct list_t* m_plusOne(){
  // sentinel head _पहारेकरी, watchman
  printf ("[%s] Enter L=%d \n",__func__,  __LINE__);
  struct list_t* sentinel = m_CreateNodeL(0);
  sentinel->next = head;
  struct list_t* notNine = sentinel;

  // find the rightmost not-nine digit
  while (head != NULL) {
    if (head->data != 9) notNine = head;
    head = head->next;
  }
  // increase this rightmost not-nine digit by 1
  notNine->data++;
  notNine = notNine->next;
  // set all the following nines to zeros
  while (notNine != NULL) {
    notNine->data = 0;
    notNine = notNine->next;
  }

  printf ("[%s] sentinel->data=%d L=%d \n",__func__,  sentinel->data, __LINE__);
  free(notNine);
  notNine = NULL;
  printf ("[%s] sentinel->data=%d L=%d \n",__func__,  sentinel->data, __LINE__);
  return sentinel->data != 0 ? (head=sentinel) : (head=sentinel->next);
}
/***
---------:: Input ::-----------
->[1][0x241b890]->[9][0x241b870]->[8][0x241b850]->[9][0x241b830]
----------:: End ::-----------
----------:: Output ::-----------
->[1][0x241b890]->[9][0x241b870]->[9][0x241b850]->[0][0x241b830]
----------:: End ::-----------
*/


void m_Freelist() {
	if (head == NULL)
		printf ("\n Empty Link List.");
	else {
		struct list_t *temp = NULL;
		struct list_t *tmp  = NULL;
		if (head->next == NULL) {
			free (head);
			head = NULL;
		}
		else {
			temp = head;
			while (temp != NULL) {
				tmp = temp;
				//tmp->next == NULL;
				temp = temp->next;
				free (tmp);
				tmp = NULL;
			} // while end
			free (head);
			head = NULL;
		} // second if end
	} // first if end
}

void m_Display(){
	printf ("\n----------:: Output ::-----------\n");
	struct list_t *temp = NULL;
	temp = head;
	while (temp != NULL) {
	  printf ("->[%d][%p]", temp->data, temp);
		temp = temp->next;
	}
	printf ("\n----------:: End ::-----------\n");
}

