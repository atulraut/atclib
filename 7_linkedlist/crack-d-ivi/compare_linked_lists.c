/***
    How to compare two linked lists ?
    Write a C program to compare two linked lists.

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

int compare_linked_lists(struct node *q, struct node *r) {
  static int flag;

  if((q == NULL ) && (r == NULL)) {
    flag = 1;
  } else {
    if(q == NULL || r == NULL)
      flag = 0;
    if(q->data != r->data)
      flag = 0;
    else
      compare_linked_lists(q->next, r->next);
  }
  return(flag);
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
  push(&head2, 0);
  push(&head2, 2);
  push(&head2, 3);
  push(&head2, 4);

  debug("Given linked list\n");
  printList(head1);
  printList(head2);
  ret = compare_linked_lists(head1, head2);
  debug("Is Compare = %d \n", ret);

  return 0;
}

/**
   => ./a.out
   [main] L=73 :Given linked list

   [printList] L=53 :4
   [printList] L=53 :3
   [printList] L=53 :2
   [printList] L=53 :1
   [printList] L=53 :4
   [printList] L=53 :3
   [printList] L=53 :2
   [printList] L=53 :1
   [main] L=77 :Is Compare = 1

   => ./a.out
   [main] L=73 :Given linked list

   [printList] L=53 :4
   [printList] L=53 :3
   [printList] L=53 :2
   [printList] L=53 :1
   [printList] L=53 :4
   [printList] L=53 :3
   [printList] L=53 :2
   [printList] L=53 :0
   [main] L=77 :Is Compare = 0
**/
