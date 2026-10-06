/***
    https://leetcode.com/problems/swap-nodes-in-pairs
    Swap Nodes in Pairs

    Given a linked list, swap every two adjacent nodes and
    return its head.
    You must solve the problem without modifying the
    values in the list's nodes (i.e., only nodes themselves
    may be changed.)

    Input: head = [1,2,3,4]
    Output: [2,1,4,3]

    Input: head = []
    Output: []

    Input: head = [1]
    Output: [1]

    Constraints:
    The number of nodes in the list is in the range [0, 100].
    0 <= Node.val <= 100

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 02/15/2022 20:47
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

struct ListNode* swapPairs(struct ListNode* head) {
  struct ListNode *start = NULL, *prev = head, *temp;
  if (head == NULL || head->next == NULL)
    return head;
  start = head->next;
  while(head != NULL && head->next != NULL) {
    temp = head->next->next;
    prev->next = head->next;
    head->next->next = prev = head;
    head->next = temp;
    head = head->next;
  }
  return start;
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

/* Rewrite to fix cycle code */
void test() {
  int ret = 0;
  struct ListNode* head = NULL;

  push(&head, 4);
  push(&head, 3);
  push(&head, 2);
  push(&head, 1);

  debug("Given linked list\n");
  printList(head);

  struct ListNode* retur = swapPairs(head);
  debug("Output = %d head->val=%pK", ret, retur);
  printList(retur);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [test] L=104 :Given linked list

   [printList] L=89 :1
   [printList] L=89 :2
   [printList] L=89 :3
   [printList] L=89 :4
   [test] L=108 :Output = 0 head->val=0x1b12050K
   [printList] L=89 :2
   [printList] L=89 :1
   [printList] L=89 :4
   [printList] L=89 :3
**/
