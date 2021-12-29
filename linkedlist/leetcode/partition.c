/***
    Medium: 86. Partition List
    https://leetcode.com/problems/partition-list/

    Given the head of a linked list and a value x, partition it such
    that all nodes less than x come before nodes greater than or equal to x.

    You should preserve the original relative order of the nodes in
    each of the two partitions.

    Input: head = [1,4,3,2,5,2], x = 3
    Output: [1,2,2,4,3,5]

    Input: head = [2,1], x = 2
    Output: [1,2]

    Constraints:
    The number of nodes in the list is in the range [0, 200].
    -100 <= Node.val <= 100
    -200 <= x <= 200
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

struct ListNode {
  int val;
  struct ListNode *next;
};


struct ListNode* partition(struct ListNode* head, int x) {
  struct ListNode *before_x = (struct ListNode *) malloc (sizeof(struct ListNode));
  struct ListNode *after_x = (struct ListNode *) malloc (sizeof(struct ListNode));

  struct ListNode *dummy_after_x = (struct ListNode *) malloc (sizeof(struct ListNode));
  struct ListNode *dummy_before_x = (struct ListNode *) malloc (sizeof(struct ListNode));

  dummy_after_x = after_x;
  dummy_before_x = before_x;


  while(head != NULL) {
    if (head->val < x) {
      before_x->next = head;
      before_x = before_x->next;
    }
    else {
      after_x->next = head;
      after_x = after_x->next;
    }
    head = head->next;
  }

  after_x->next = NULL;
  before_x->next = dummy_after_x->next;
  return dummy_before_x->next;
}

void push(struct ListNode** head_ref, int val) {
  struct ListNode* nn = (struct ListNode*)malloc(sizeof(struct ListNode));
  nn->val = val;
  nn->next = (*head_ref);
  (*head_ref) = nn;
}

void printList(struct ListNode* head) {
  struct ListNode* trav = head;
  while (trav != NULL) {
    debug("%d  ", trav->val);
    trav = trav->next;
  }
}

void test_remove() {
  struct ListNode* head = NULL;

  push(&head, 2);
  push(&head, 4);
  push(&head, 2);
  push(&head, 3);
  push(&head, 4);
  push(&head, 1);

  debug("Given linked list\n");
  printList(head);
  debug("*** Remove Nth from End List ***");
  head = partition(head, 3);
  printList(head);
}

int main () {
  test_remove();
}


/**
   => ./a.out
   [test_remove] L=94 :Given linked list

   [printList] L=79 :1
   [printList] L=79 :4
   [printList] L=79 :3
   [printList] L=79 :2
   [printList] L=79 :4
   [printList] L=79 :2
   [test_remove] L=96 :*** Remove Nth from End List ***
   [printList] L=79 :1
   [printList] L=79 :2
   [printList] L=79 :2
   [printList] L=79 :4
   [printList] L=79 :3
   [printList] L=79 :4
**/
