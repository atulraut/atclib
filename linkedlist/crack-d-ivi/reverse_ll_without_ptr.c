/***
    How do you reverse a linked list without using
    any C pointers?
    One way is to reverse the data in the nodes without
    changing the pointers themselves. One can also
    create a new linked list which is the reverse of
    the original linked list. A simple C program can
    do that for you. Please note that you would still
    use the "next" pointer fields to traverse through
    the linked list (So in effect, you are using the
    pointers, but you are not changing them when
    reversing the linked list).

    Date: 10/9/2021 - 109 Hindu Magic Number
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

/* Need Fix */
static void reverse(struct node** head_ref) {
  struct node* prev = NULL;
  struct node* current = *head_ref;
  struct node* next = NULL;

  while (current != NULL) {
    // Store next
    next = current->next;
     // Reverse current node's pointer
    current->next = prev;
     // Move pointers one position ahead.
    prev = current;
    current = next;
  }

  *head_ref = prev;
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
  /* Start with the empty list */
  struct node* head = NULL;

  push(&head, 20);
  push(&head, 4);
  push(&head, 15);
  push(&head, 85);

  debug("Given linked list\n");
  printList(head);
  reverse(&head);
  debug("Reversed Linked list \n");
  printList(head);

  return 0;
}

/**
   => ./a.out
   [main] L=78 :Given linked list

   [printList] L=64 :85
   [printList] L=64 :15
   [printList] L=64 :4
   [printList] L=64 :20
   [main] L=81 :Reversed Linked list

   [printList] L=64 :20
   [printList] L=64 :4
   [printList] L=64 :15
   [printList] L=64 :85
**/
