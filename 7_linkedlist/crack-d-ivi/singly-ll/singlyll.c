/*
 * Aim : Singly Linked List.
 * Date : Monday, March 26 2012 05:15 PM
 * End  : Sunday, Feb 28 2021 12PM
 * By : Atul R. Raut
 *
 ***/
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)
struct node *head = NULL;

void m_Init (struct node *node){
  node->data = 0;
  node->next = NULL;
}

struct node* m_CreateNodeL (int data){
  struct node *nn = NULL;
  nn = (struct node*)malloc(sizeof (struct node));
  if (nn == NULL)
    return NULL;
  nn->data  = data;
  nn->next = NULL;
  return nn;
}

void m_Addfirst(int data) {
  struct node *nn = NULL;
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
  struct node *nn = NULL;
  nn = m_CreateNodeL (data);

  if (head == NULL)
    m_Addfirst (data);
  else {
    struct node *temp = NULL;
    temp = head;
    while (temp->next != NULL)
      temp = temp->next;
    temp->next = nn;
    nn->next = NULL;
  }
}

void m_Insert(int pos, int data){
  struct node *temp2 = NULL;
  struct node *nn = NULL;
  struct node *trav = head;

  if (pos < 1) {
    printf ("\n Enter valid input\n");
    return;
  } else {
    nn = m_CreateNodeL (data);
    if (pos == 1 || head == NULL)
      m_Addfirst (data);
    else {
      trav = head; // Re-assing temp
      /* Assume 1st Node is 1 */
      for (int i=1; i<pos-1; i++) {
	trav = ((trav->next != NULL) ? trav->next : NULL);
	if(NULL == trav->next)
	  break;
	trav = trav->next;
      }
      /* Assume 3 node in list & you're adding 2nd Node */
      temp2 = trav->next;
      trav->next = nn;
      nn->next = temp2;
    }
  }
}

void m_Delfirst() {
  if (head == NULL)
    printf ("\n Empty Link List.");
  else {
    struct node *temp = NULL;
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
    struct node *temp = NULL;
    struct node *tmp  = NULL;
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
  struct node *temp = NULL;
  struct node *tmp  = NULL;
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
  struct node *trav = NULL;
  struct node *temp = NULL;
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
      temp->next = head; // attach struct node
      head = temp;     // L1 Make NULL, L2 Attach Node
      temp = trav;
      printf ("temp=[%p][%d]\n", temp,temp->data);
    }
  }
}

void m_Freelist() {
  if (head == NULL)
    printf ("\n Empty Link List.");
  else {
    struct node *temp = NULL;
    struct node *tmp  = NULL;
    if (head->next == NULL) {
      free (head);
      head = NULL;
    }
    else {
      temp = head;
      while (temp != NULL) {
	tmp = temp;
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
  struct node *temp = NULL;
  temp = head;
  while (temp != NULL) {
    printf ("->[%d][%p]", temp->data, temp);
    temp = temp->next;
  }
  printf ("\n----------:: End ::-----------\n");
}

