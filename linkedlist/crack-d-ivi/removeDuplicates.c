/***
    Write a C program to remove duplicates from
    a sorted linked list

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

// Remove duplicates from a sorted list
void removeDuplicates(struct node* head) {
  struct node* current = head;

  if (current == NULL)
    return; // do nothing if the list is empty

  // Compare current node with next node
  while(current->next!=NULL) {
    if (current->data == current->next->data) {
      struct node* nextNext = current->next->next;
      free(current->next);
      current->next = nextNext;
    } else {
      current = current->next; // only advance if no deletion
    }
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
  push(&head1, 3);
  push(&head1, 3);
  push(&head1, 4);

  debug("Given linked list\n");
  printList(head1);

  debug("Remove Duplicates from LinkedList!");
  removeDuplicates(head1);
  printList(head1);

  return 0;
}

/**
   => ./a.out
   [main] L=71 :Given linked list

   [printList] L=56 :4
   [printList] L=56 :3
   [printList] L=56 :3
   [printList] L=56 :1
   [main] L=74 :Remove Duplicates from LinkedList!
   [printList] L=56 :4
   [printList] L=56 :3
   [printList] L=56 :1
**/
