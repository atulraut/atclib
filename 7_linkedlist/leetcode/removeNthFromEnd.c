/***
    Medium: 19. Remove Nth Node From End of List
    https://leetcode.com/problems/remove-nth-node-from-end-of-list

    Given the head of a linked list, remove the nth node from the
    end of the list and return its head.

    Input: head = [1,2,3,4,5], n = 2
    Output: [1,2,3,5]

    Input: head = [1], n = 1
    Output: []

    Input: head = [1,2], n = 1
    Output: [1]

    Constraints:
    The number of nodes in the list is sz.
    1 <= sz <= 30
    0 <= Node.val <= 100
    1 <= n <= sz

    Follow up: Could you do this in one pass?

    Constraints:
    The number of nodes in the list is in the range [0, 200].
    -100 <= Node.val <= 100
    -200 <= x <= 200

    Date: 12/29/20221
    Folsom, CA
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

/**
   1] Count Number of Element
   2] Subtract it from ask number
   3] Move pointers till there
   4] Return next ptr
**/
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
  struct ListNode *new_head = (struct ListNode*)malloc(sizeof(struct ListNode));
  new_head->next = head;
  int length = 0;
  struct ListNode *curr = head;

  while (curr != NULL) {
    length++;
    curr = curr->next;
  }
  debug("len = %d", length)
  length -= n;
  debug("len = %d", length);
  curr = new_head;

  while (length > 0) {
    length--;
    curr = curr->next;
    debug("len = %d", length);
  }
  debug("val = %d", curr->val);
  curr->next = curr->next->next;
  return new_head->next;
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

  push(&head, 5);
  push(&head, 4);
  push(&head, 3);
  push(&head, 2);
  push(&head, 1);

  debug("Given linked list\n");
  printList(head);
  debug("*** Remove Nth from End List ***");
  removeNthFromEnd(head, 2);
  printList(head);
}

int main () {
  test_remove();
}

/**
   => ./a.out
   [test_remove] L=100 :Given linked list

   [printList] L=86 :1
   [printList] L=86 :2
   [printList] L=86 :3
   [printList] L=86 :4
   [printList] L=86 :5
   [test_remove] L=102 :*** Remove Nth from End List ***
   [removeNthFromEnd] L=61 :len = 5
   [removeNthFromEnd] L=63 :len = 3
   [removeNthFromEnd] L=69 :len = 2
   [removeNthFromEnd] L=69 :len = 1
   [removeNthFromEnd] L=69 :len = 0
   [removeNthFromEnd] L=71 :val = 3
   [printList] L=86 :1
   [printList] L=86 :2
   [printList] L=86 :3
   [printList] L=86 :5
**/
