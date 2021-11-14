/***
    https://leetcode.com/problems/remove-linked-list-elements

    Given the head of a linked list and an integer val,
    remove all the nodes of the linked list that has
    Node.val == val, and return the new head.

    Input: head = [1,2,6,3,4,5,6], val = 6
    Output: [1,2,3,4,5]

    Input: head = [], val = 1
    Output: []

    Input: head = [7,7,7,7], val = 7
    Output: []

    The number of nodes in the list is in the range [0, 104].
    1 <= Node.val <= 50
    0 <= val <= 50

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 13 Nov 2021
    Folsom, CA.
*/

/*----------------------------------- Header --------------------------------------*/
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

/*----------------------------------- Micro --------------------------------------*/
#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)
#define atsizeof(object) (char *)(&object+1) - (char*)(&object)
#define arrsz(x)  (sizeof(x) / sizeof((x)[0]))
#define max(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a > _b ? _a : _b; })
#define min(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct node {
  int val;
  struct node* next;
};

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

struct node* removeElements(struct node* head, int val) {
  if (head == NULL)
    return head;

  struct node *curr = head;

  while(curr != NULL && curr->next != NULL) {
    if( curr->next->val == val)
      curr->next = curr->next->next;
    else
      curr = curr->next;
  }

  if (head->val == val)
    head = head->next;

  return head;
}

struct node* removeElements1(struct node* head, int val) {
  struct node *tmp, *tracker = head;
  if(head == NULL)
    return NULL;

  while(tracker != NULL && tracker == head && tracker->val == val) {
    tracker = tracker->next;
    free(head);
    head = tracker;
  }

  while(tracker != NULL) {
    if(tracker->next != NULL && tracker->next->val == val) {
      tmp = tracker->next;
      tracker->next = tracker->next->next;
      free(tmp);
    } else
       tracker = tracker->next;
  }
  return head;
}

// Need Improvement
struct node* removeElements2(struct node* head, int val) {
  struct node *trav = head;
  struct node *temp = NULL;

  while (trav->next != NULL) {
    debug (" trav->val=%d", trav->val);
    if(trav->val == val)  {
      if (trav->next == NULL) {
	break;
      } else {
	temp = trav->next;
	trav->next = temp->next;
	trav->val = temp->val;
	free(temp);
	temp = NULL;
      }
    } else
      trav = trav->next;
    debug (" trav->val=%d", trav->val);
  }
  if(trav->val == val) {
    free(trav);
    trav = NULL;
  }
  return head;
}

void push(struct node** head_ref, int val) {
  struct node* nn = (struct node*)malloc(sizeof(struct node));
  nn->val = val;
  nn->next = (*head_ref);
  (*head_ref) = nn;
}

void printList(struct node* head) {
  struct node* trav = head;
  while (trav != NULL) {
    debug("%d  ", trav->val);
    trav = trav->next;
  }
}

int main (int argc, char **argv) {
  int ret = 0;
  /* Start with the empty list */
  struct node* head = NULL;

  push(&head, 1);
  push(&head, 2);
  push(&head, 3);
  push(&head, 6);
  push(&head, 4);
  push(&head, 5);
  push(&head, 6);

  debug("Given linked list\n");
  printList(head);

  debug("Remove Duplicates from LinkedList!");
  head = removeElements(head, 6);
  printList(head);

  return 0;
}

/**
   => ./a.out
   [main] L=145 :Given linked list

   [printList] L=127 :6
   [printList] L=127 :5
   [printList] L=127 :4
   [printList] L=127 :6
   [printList] L=127 :3
   [printList] L=127 :2
   [printList] L=127 :1
   [main] L=148 :Remove Duplicates from LinkedList!
   [printList] L=127 :5
   [printList] L=127 :4
   [printList] L=127 :3
   [printList] L=127 :2
   [printList] L=127 :1
**/
