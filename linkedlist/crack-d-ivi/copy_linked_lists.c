/***
    How to create a copy of a linked list ?
    Write a C program to create a copy of a linked list.

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

void copy_linked_lists(struct node *q, struct node **s);

void copy_linked_lists(struct node *org_list, struct node **new_list) {
  if(org_list != NULL) {
    (*new_list) = malloc(sizeof(struct node));
    (*new_list)->data = org_list->data;
    (*new_list)->next = NULL;
    copy_linked_lists(org_list->next, &((*new_list)->next));
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
  struct node* head2 = NULL;

  push(&head1, 1);
  push(&head1, 2);
  push(&head1, 3);
  push(&head1, 4);


  debug("Given linked list");
  printList(head1);
  copy_linked_lists(head1, &head2);
  debug("\nPost Copying Linked List");
  printList(head2);

  return 0;
}

/**
   => ./a.out
   [main] L=65 :Given linked list
   [printList] L=48 :4
   [printList] L=48 :3
   [printList] L=48 :2
   [printList] L=48 :1

   [main] L=68 :Post Copying Linked List
   [printList] L=48 :4
   [printList] L=48 :3
   [printList] L=48 :2
   [printList] L=48 :1
**/
