#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "../../at_lib.h"

LIST *init_list (void *_list) {
  _list = (LIST *) malloc (sizeof(LIST));
  LIST *list = (LIST *)_list;
  if (NULL == list)
    return NULL;
  list->head = NULL;
  return list;
}

NODE *create_node (int _data) {
  NODE *nn = (NODE *)malloc(sizeof(NODE));
  if (NULL == nn)
    return NULL;
  nn->data = _data;
  nn->next = NULL;
  nn->prev = NULL;
  return nn;
}

void m_add (void *_list, int _data) {
  LIST *list = (LIST *) _list;
  NODE *nn = NULL;
  nn = create_node (_data);
  if (NULL == list->head) { // first Node
	  nn->prev = list->head;
	  list->head = nn;
  } else {  // add last
	  NODE *trav = list->head;
	  while (NULL != trav->next)
	     trav = trav->next;
	  trav->next = nn;
	  nn->prev = trav;
  }
}

void m_sort() {

}


// function to insert a new node in sorted way in
// a sorted doubly linked list
void sortedInsert(void *_list, NODE* newNode) {
  LIST *list = (LIST *)_list;
  if (NULL == list->head) {
    printf ("List is Empty\n");
    return;
  }
  NODE *trav = list->head;

   NODE* current;

    // if list is empty
    if (list->head == NULL)
        list->head = newNode;

    // if the node is to be inserted at the beginning
    // of the doubly linked list
    else if (trav->data >= newNode->data) {
        newNode->next = trav;
        newNode->next->prev = newNode;
        trav = newNode;
    }

    else {
      current = list->head;

        // locate the node after which the new node
        // is to be inserted
        while (current->next != NULL &&
               current->next->data < newNode->data)
            current = current->next;

        /*Make the appropriate links */

        newNode->next = current->next;

        // if the new node is not inserted
        // at the end of the list
        if (current->next != NULL)
            newNode->next->prev = newNode;

        current->next = newNode;
        newNode->prev = current;
    }
}

/**
   https://www.geeksforgeeks.org/bubble-sort-on-doubly-linked-list/
   https://www.geeksforgeeks.org/insertion-sort-doubly-linked-list/
**/
// function to sort a doubly linked list using insertion sort
void m_insertionSort(void *_list) {
  LIST *list = (LIST *)_list;
  if (NULL == list->head) {
    printf ("List is Empty\n");
    return;
  }
  NODE *trav = list->head;

    // Initialize 'sorted' - a sorted doubly linked list
    struct NODE* sorted = NULL;

    // Traverse the given doubly linked list and
    // insert every node to 'sorted'
    //struct Node* current = *head_ref;
    NODE *current = list->head;
    while (current != NULL) {

        // Store next for next iteration
        struct NODE* next = current->next;

        // removing all the links so as to create 'current'
        // as a new node for insertion
        current->prev = current->next = NULL;

        // insert current in 'sorted' doubly linked list
        sortedInsert(&sorted, current);

        // Update current
        current = next;
    }

    // Update head_ref to point to sorted doubly linked list
    list->head = sorted;
}

void m_display (void *_list) {
  LIST *list = (LIST *)_list;
  if (NULL == list->head) {
    printf ("List is Empty\n");
    return;
  }
  NODE *trav = list->head;
  while (NULL != trav) {
    printf ("->[%d]", trav->data);
    trav = trav->next;
  }
}

void m_free (void *_list) {
  LIST *list = (LIST *)_list;
  NODE *temp = NULL;
  if (NULL == list->head) {
    printf ("Empty\n");
    return;
  }
  printf ("list->head = %p \n", list->head);
  NODE *trav = list->head;
  while (trav != NULL) {
    if (trav->next == list->head) { /*if only 1 node in list*/
      trav->next = NULL;
      free(trav);
      trav = NULL;
    } else {
      printf ("list->head = %p \n", list->head);
      temp = trav;
      trav = trav->next;
      free(temp);
      temp = NULL;
    }
  }
  list->head = NULL;  /* make sure to clear head as it points to nothig here */
}

void m_Printrev(void *_list) {
  LIST *list = (LIST *)_list;
  NODE *temp = list->head;
  list->head = NULL;
  NODE *trav = NULL;
  while (NULL != temp->next) {
    printf ("temp ->[%d]", temp->data);
    trav = temp->next;
    temp->next = list->head;
    list->head = temp;
    temp->prev = list->head;
    temp = trav;
  }
  temp->next = list->head;
}
