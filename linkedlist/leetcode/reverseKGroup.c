/***

    https://leetcode.com/problems/reverse-nodes-in-k-group/
    25. Reverse Nodes in k-Group

    Given the head of a linked list, reverse the nodes of the
    list k at a time, and return the modified list.

    k is a positive integer and is less than or equal to the length of
    the linked list. If the number of nodes is not a multiple of k then
    left-out nodes, in the end, should remain as it is.

    You may not alter the values in the list's nodes, only nodes themselves may be changed.

    Input: head = [1,2,3,4,5], k = 2
    Output: [2,1,4,3,5]

    Input: head = [1,2,3,4,5], k = 3
    Output: [3,2,1,4,5]

    Constraints:
    The number of nodes in the list is n.
    1 <= k <= n <= 5000
    0 <= Node.val <= 1000

    Follow-up: Can you solve the problem in O(1) extra memory space?

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address reorderList.c -lm

    Date: Sat Sep 10 11:16:04 PM PDT 2022
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
typedef struct ListNode Node;

/**
 * Definition for singly-linked list.
 */
struct ListNode {
  int val;
  struct ListNode *next;
};

Node* reverseKGroup(Node* head, int k) {
  Node dummy = {-1, head};

  Node* left = &dummy;
  while(1) {
    // go over k nodes
    Node* right = left;
    for(int i = 0; right && i < k; ++i) {
      right = right->next;
    }
    // if tail less than k nodes let's break
    if(!right) {
      break;
    }
    Node* prev = left->next;
    Node* next = prev->next;
    // reconnect borders
    prev->next = right->next;
    left->next = right;
    left = prev;
    // reverse connections
    for(int i = 1; i < k; ++i) {
      Node* tmp = next->next;
      next->next = prev;
      prev = next;
      next = tmp;
    }
  }
  return dummy.next;
}

struct ListNode* reverseKGroup_works_1(struct ListNode* head, int k) {
  if (k == 1)
    return head;

  struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
  dummy->val = -1;
  dummy->next = head;

  struct ListNode* returnHead = NULL;

  struct ListNode* start = dummy->next;
  struct ListNode* pp_prev = dummy;
  int firstTime = 1;
  while (start != NULL) {
    struct ListNode* end = start;

    int temp = 1;
    while (temp < k && end != NULL) {
      end = end->next;
      temp++;
      if (firstTime == 1)
	returnHead = end;
    }
    firstTime = 0;

    if (end == NULL)
      break;
    struct ListNode* aa_after = end->next;
    // REVERSE START
    pp_prev->next = NULL;
    end->next = NULL;
    struct ListNode* lastAfterReverse = start;
    struct ListNode* prev = NULL;
    struct ListNode* nnext = NULL;
    while (start != NULL) {
      nnext = start->next;
      start->next = prev;
      prev = start;
      start = nnext;
    }

    pp_prev->next = prev;
    lastAfterReverse->next = aa_after;

    // REVERSE END
    pp_prev = lastAfterReverse;
    start = pp_prev->next;
  }
  return returnHead;
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

int main (int argc, char **argv) {
  int ret = 0;

   struct ListNode* head = NULL;

  push(&head, 5);
  push(&head, 4);
  push(&head, 3);
  push(&head, 2);
  push(&head, 1);

  debug("Given linked list\n");
  printList(head);
  debug("Reversed List");
  int k = 2;
  Node* output = reverseKGroup(head, k);
  printList(output);
  return 0;
}

/**
   => ./a.out
   [main] L=177 :Given linked list

   [printList] L=161 :1
   [printList] L=161 :2
   [printList] L=161 :3
   [printList] L=161 :4
   [printList] L=161 :5
   [main] L=179 :Reversed List
   [printList] L=161 :2
   [printList] L=161 :1
   [printList] L=161 :4
   [printList] L=161 :3
   [printList] L=161 :5
**/

/**
   Complexity Analysis
   Time Complexity: O(N) since we process each node exactly twice.
   Once when we are counting the number of nodes in each recursive call,
   and then once when we are actually reversing the sub-list.
   A slightly optimized implementation here could be that we don't
   count the number of nodes at all and simply reverse k nodes.
   If at any point we find that we didn't have enough nodes, we can
   re-reverse the last set of nodes so as to keep the original
   structure as required by the problem statement. That ways, we can
   get rid of the extra counting.
   Space Complexity: O(N/k) used up by the recursion stack.
   The number of recursion calls is determined by both kk and N.
   In every recursive call, we process k nodes and then make a
   recursive call to process the rest.
**/
