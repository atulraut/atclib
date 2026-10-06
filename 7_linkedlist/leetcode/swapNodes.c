/***
    https://leetcode.com/problems/swapping-nodes-in-a-linked-list/
    Swapping Nodes in a Linked List

    You are given the head of a linked list, and an integer k.

    Return the head of the linked list after swapping the
    values of the kth node from the beginning and the kth
    node from the end (the list is 1-indexed).

    Input: head = [1,2,3,4,5], k = 2
    Output: [1,4,3,2,5]

    Input: head = [7,9,6,6,7,8,3,0,9,5], k = 5
    Output: [7,9,6,6,8,7,3,0,9,5]

    Constraints:
    The number of nodes in the list is n.
    1 <= k <= n <= 105
    0 <= Node.val <= 100

    Date: Mon Apr  4 08:43:15 PDT 2022
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

struct ListNode* swapNodes(struct ListNode* head, int k) {
  int listLength = 0;
  struct  ListNode* frontNode;
  struct ListNode* endNode;
  struct ListNode* currentNode = head;
  while (currentNode) {
    listLength++;
    if (listLength == k) {
      frontNode = currentNode;
    }
    currentNode = currentNode->next;
  }
  endNode = head;
  for (int i = 1; i <= listLength - k; i++) {
    endNode = endNode->next;
  }
  // swap front node and end node values
  //   swap(frontNode->val, endNode->val);
  int temp = frontNode->val;
  frontNode->val = endNode->val;
  endNode->val = temp;
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
  head = swapNodes(head, 2);
  printList(head);
}

int main () {
  test_remove();
}

/**
   => ./a.out
   [test_remove] L=91 :Given linked list

   [printList] L=77 :1
   [printList] L=77 :2
   [printList] L=77 :3
   [printList] L=77 :4
   [printList] L=77 :5
   [test_remove] L=93 :*** Remove Nth from End List ***
   [printList] L=77 :1
   [printList] L=77 :4
   [printList] L=77 :3
   [printList] L=77 :2
   [printList] L=77 :5
**/
