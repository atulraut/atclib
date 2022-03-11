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
  struct node *tmp, *trav = head;
  if(head == NULL)
    return NULL;

  while(trav != NULL && trav == head && trav->val == val) {
    trav = trav->next;
    free(head);
    head = trav;
  }

  while(trav != NULL) {
    if(trav->next != NULL && trav->next->val == val) {
      tmp = trav->next;
      trav->next = trav->next->next;
      free(tmp);
    } else
       trav = trav->next;
  }
  return head;
}

/**
   https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
   Remove Duplicates from Sorted List II

   Given the head of a sorted linked list, delete all nodes that have duplicate
   numbers, leaving only distinct numbers from the original list.
   Return the linked list sorted as well.

   Input: head = [1,2,3,3,4,4,5]
   Output: [1,2,5]

   Input: head = [1,1,1,2,3]
   Output: [2,3]


   Constraints:

   The number of nodes in the list is in the range [0, 300].
   -100 <= Node.val <= 100
   The list is guaranteed to be sorted in ascending order.

   Date: Thu Mar 10 18:32:23 PST 2022
   Folsom CA
**/
struct node* deleteDuplicates(struct node* head){
  int last_seen;
  struct node* ptr;
  struct node* ptr2;

  if (head == NULL)
    return NULL;

  while ((head->next != NULL) && (head->val == head->next->val)) {
    ptr = head->next;
    while ((ptr->next != NULL) && (ptr->next->val == head->val))
      ptr = ptr->next;

    head = ptr->next;
    if (head==NULL)
      return NULL;
  }
  // Now the head node is unique.
  ptr = head;
  while (ptr != NULL) {
    ptr2 = ptr->next;
    if (ptr2 != NULL) {
      last_seen = ptr2->val;
      while ((ptr2->next != NULL) && (ptr2->next->val == last_seen))
	ptr2 = ptr2->next;
    }
    if (ptr->next != ptr2) ptr->next = ptr2->next;
    else ptr = ptr2;
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
  int flag = 1;
  /* Start with the empty list */
  struct node* head = NULL;

  push(&head, 1);
  push(&head, 2);
  push(&head, 3);
  push(&head, 4);
  push(&head, 5);
  push(&head, 6);
  push(&head, 6);

  debug("Given linked list\n");
  printList(head);
  debug("Remove Duplicates from LinkedList!");
  if (!flag) {
    head = removeElements1(head, 6);
    printList(head);
  } else {
    head = deleteDuplicates(head);
    printList(head);
  }
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


/**
   deleteDuplicates:-
   => ./a.out
   [main] L=188 :Given linked list

   [printList] L=169 :6
   [printList] L=169 :6
   [printList] L=169 :5
   [printList] L=169 :4
   [printList] L=169 :3
   [printList] L=169 :2
   [printList] L=169 :1
   [main] L=190 :Remove Duplicates from LinkedList!
   [printList] L=169 :5
   [printList] L=169 :4
   [printList] L=169 :3
   [printList] L=169 :2
   [printList] L=169 :1
**/
