/***
    Write a C program to insert nodes into a linked list in
    a sorted fashion.
    The solution is to iterate down the list looking for the
    correct place to insert the new node. That could be the end
    of the list, or a point just before a node which is larger
    than the new node.

    Note that we assume the memory for the new node has already
    been allocated and a pointer to that memory is being passed
    to this function.

    Date: 10/8/2021 - 109 Hindu Magic Number
    Fair Oaks, CA.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

struct node {
  int data;
  struct node* next;
};

// Special case code for the head end
void m_insert_Sorted(struct node** head_ref, struct node* nn) {
  // Special case for the head end
  if (*head_ref == NULL || (*head_ref)->data >= nn->data)  {
    nn->next = *head_ref;
    *head_ref = nn;
  } else {
    // Locate the node before which the insertion is to happen!
    struct node* current = *head_ref;
    while (current->next!=NULL && current->next->data < nn->data) {
      current = current->next;
    }
    nn->next = current->next;
    current->next = nn;
  }
}

void push(struct node** head_ref, int val) {
  struct node* nn = (struct node*)malloc(sizeof(struct node));
  nn->data = val;
  nn->next = (*head_ref);
  (*head_ref) = nn;
}

void printList(struct node* head) {
  struct node* trav = head;
  while (trav != NULL) {
    debug("%d  ", trav->data);
    trav = trav->next;
  }
}

int main (int argc, char **argv) {
  int ret = 0;
  /* Start with the empty list */
  struct node* head1 = NULL;

  push(&head1, 1);
  push(&head1, 2);
  push(&head1, 3);
  push(&head1, 4);

  debug("Given linked list\n");
  printList(head1);

  debug("Insertion with Sorting linked list ");
  struct node* nn = (struct node*)malloc(sizeof(struct node));
  nn->data = 90;
  nn->next = NULL;
  m_insert_Sorted(&head1, nn);
  printList(head1);

  return 0;
}

/**
   => ./a.out
   [main] L=77 :Given linked list

   [printList] L=62 :4
   [printList] L=62 :3
   [printList] L=62 :2
   [printList] L=62 :1
   [main] L=80 :Insertion with Sorting linked list
   [printList] L=62 :4
   [printList] L=62 :3
   [printList] L=62 :2
   [printList] L=62 :1
   [printList] L=62 :90
**/
