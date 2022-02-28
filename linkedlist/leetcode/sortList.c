/***
    https://leetcode.com/problems/sort-list/

    Sort List
    Given the head of a linked list, return the list after sorting it in ascending order.

    Input: head = [4,2,1,3]
    Output: [1,2,3,4]

    Input: head = [-1,5,3,4,0]
    Output: [-1,0,3,4,5]

    Input: head = []
    Output: []

    Constraints:

    The number of nodes in the list is in the range [0, 5 * 104].
    -105 <= Node.val <= 105

    Follow up: Can you sort the linked list in O(n logn) time and O(1)
    memory (i.e. constant space)?

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 22-02-2022
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
#define max(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a > _b ? _a : _b; })
#define min(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

/**
 * Definition for singly-linked list.
 */
struct ListNode {
  int val;
  struct ListNode *next;
};

struct ListNode *mergeList(struct ListNode *l1, struct ListNode *l2) {
  if(l1 == NULL) return l2;
  if(l2 == NULL) return l1;

  if(l1->val <= l2->val) {
    l1->next = mergeList(l1->next, l2);
    return l1;
  } else {
    l2->next = mergeList(l1, l2->next);
    return l2;
  }
}

struct ListNode* sortList(struct ListNode* head) {
  if(head == NULL)
    return NULL;
  if(head->next == NULL)
    return head;
  struct ListNode *fast, *slow, *pre;
  fast = slow = head;
  while(fast && fast->next) {
    pre = slow;
    fast = fast->next->next;
    slow = slow->next;
  }

  pre->next = NULL;
  return mergeList(sortList(head), sortList(slow));
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
  /* Start with the empty list */
  struct ListNode head;

  push(&head, 3);
  push(&head, 1);
  push(&head, 2);
  push(&head, 4);

  debug("Given linked list\n");
  printList(&head);

  debug("Sort LinkedList!");
  struct ListNode head2 = sortList(head);
  printList(&head2);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**

 **/
