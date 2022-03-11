/***
    https://leetcode.com/problems/rotate-list/
    Rotate List

    Given the head of a linked list, rotate the list to the right by k places.

    Input: head = [1,2,3,4,5], k = 2
    Output: [4,5,1,2,3]

    Input: head = [0,1,2], k = 4
    Output: [2,0,1]

    Constraints:

    The number of nodes in the list is in the range [0, 500].
    -100 <= Node.val <= 100
    0 <= k <= 2 * 109

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Thu Mar 10 19:48:16 PST 2022
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
 */
struct ListNode {
  int val;
  struct ListNode *next;
};

/**
   Algorithm:
   The algorithm is quite straightforward :
   Find the old tail and connect it with the
   head old_tail.next = head to close the ring.
   Compute the length of the list n at the same time.

   Find the new tail, which is (n - k % n - 1)th
   node from the head and the new head, which is (n - k % n)th node.

   Break the ring new_tail.next = None and return new_head.
**/
struct ListNode* rotateRight(struct ListNode* head, int k) {
  if (!head || k == 0)
    return head;

  struct ListNode* lastNode = head;
  int n = 1;

  while (lastNode->next) {
    lastNode = lastNode->next;
    n++;
  }

  k = k%n;
  if (k == 0)
    return head;
  k = n - k;

  lastNode->next = head;
  struct ListNode *newHead = head;

  for (int i = 0; i < k - 1; i++)
    newHead = newHead->next;

  head = newHead->next;
  newHead->next = NULL;

  return head;
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


void test() {
  int ret = 0;
  int k = 2;
  /* Start with the empty list */
  struct ListNode* head = NULL;

  push(&head, 5);
  push(&head, 4);
  push(&head, 3);
  push(&head, 2);
  push(&head, 1);

  debug("Given linked list\n");
  printList(head);

  debug("Sort LinkedList!");
  struct ListNode* head2 = rotateRight(head, k);
  printList(head2);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [test] L=116 :Given linked list

   [printList] L=98 :1
   [printList] L=98 :2
   [printList] L=98 :3
   [printList] L=98 :4
   [printList] L=98 :5
   [test] L=119 :Sort LinkedList!
   [printList] L=98 :4
   [printList] L=98 :5
   [printList] L=98 :1
   [printList] L=98 :2
   [printList] L=98 :3
**/
