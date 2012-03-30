/*
* Aim : Singly Linked List.
* Date : Monday, March 26  2012 05:15 PM
* End  : 
* By : Atul R. Raut
* 
***/
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

NODE *head = NULL;

void m_Init (NODE *node){
	node->data = 0;
	node->next = NULL;
}

NODE* m_CreateNodeL (int data){
	NODE *nn = NULL;
	nn = (NODE*)malloc(sizeof (NODE *));
	if (nn == NULL)
		return;
	nn->data  = data;
	nn->next = NULL;
	return nn;
}

void m_Display(){
	printf ("\n----------:: Output ::-----------\n");
	NODE *temp = NULL;
	temp = head;
	while (temp != NULL) {
		printf ("->[%d]", temp->data);
		temp = temp->next;
	}
	printf ("\n----------:: End ::-----------\n");
}

void m_Addfirst(int data) {
	NODE *nn = NULL;
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
	NODE *nn = NULL;
	nn = m_CreateNodeL (data);

	if (head == NULL) 
		m_Addfirst (data);
	else {
		NODE *temp = NULL;
		temp = head;
		while (temp->next != NULL) 
			temp = temp->next;
		temp->next = nn;
		nn->next = NULL;
	}		
}

void m_Insert(int pos, int data){
	int cnt = 0; // initialise to 0;
	NODE *temp = NULL;
	NODE *nn = NULL;
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
		NODE *temp = NULL;
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
		NODE *temp = NULL;
		NODE *tmp  = NULL;
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
	
}

void m_Printrev (NODE *node) {
	if (head == NULL) {
		printf ("\nEmpty link list.\n");
	} else {
		// Logic to reverse link list.
	}
}

void m_Freelist() {
	if (head == NULL)
		printf ("\n Empty Link List.");
	else {
		NODE *temp = NULL;
		NODE *tmp  = NULL;
		if (head->next == NULL)
			free (head);
		else {
			temp = head;			
			while (temp != NULL) {
				tmp = temp;
				tmp->next == NULL;
				temp = temp->next;					       
				free (tmp);
			} // while end
			free (head);
		} // second if end
	} // first if end
}