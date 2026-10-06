/***
    Medium: 92. Reverse Linked List II
    https://leetcode.com/problems/reverse-linked-list-ii/

    Given the head of a singly linked list and two integers left and right
    where left <= right, reverse the nodes of the list from position
    left to position right, and return the reversed list.

    Input: head = [1,2,3,4,5], left = 2, right = 4
    Output: [1,4,3,2,5]

    Input: head = [5], left = 1, right = 1
    Output: [5]

    Constraints:
    The number of nodes in the list is n.
    1 <= n <= 500
    -500 <= Node.val <= 500
    1 <= left <= right <= n

    Date: 23 June 2021
    San Diego, CA.
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

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* reverseBetween2(struct ListNode* head, int left, int right) {
  if (!head) return NULL;
  struct ListNode *prevSubTail = NULL, *currSubHead, *next, *prev = NULL, *curr = head;
  int i = 1;
  while (i < left) {
    prevSubTail = curr;
    curr = curr->next;
    i++;
  }
  currSubHead = curr;
  while (curr && i++ <= right) {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }
  if (prevSubTail) {
    prevSubTail->next = prev;
  } else {
    head = prev;
  }
  currSubHead->next = curr;
  return head;
}

struct ListNode* reverseBetween(struct ListNode* head, int left, int right) {
  struct ListNode  mock = { .next = head };
  struct ListNode* prev = &mock;
  struct ListNode* start = mock.next;
  struct ListNode* end = mock.next;
  struct ListNode* next = NULL;
  struct ListNode* reverse = NULL;
  int i = 1;
  for (; i < left; i++) {
    prev = prev->next;
    start = start->next;
  }
  reverse = start;
  end = start->next;
  if (end) next = end;
  for (; i < right; i++) {
    next = end->next;
    end->next = reverse;
    reverse = end;
    end = next;
  }
  // if (next)
  // printf("%d\n", next->val);
  // else
  // printf("null\n");
  start->next = next;
  prev->next = reverse;
  return mock.next;
}

int main () {
  int ret = 0;

  debug("Output = %d", ret);
  return 0;
}

/**

 **/
