/***
    https://leetcode.com/problems/remove-duplicates-from-sorted-list/

    Remove Duplicates from Sorted List

    Given the head of a sorted linked list, delete all duplicates such that
    each element appears only once. Return the linked list sorted as well.

    Input: head = [1,1,2]
    Output: [1,2]

    Input: head = [1,1,2,3,3]
    Output: [1,2,3]

    Constraints:
    The number of nodes in the list is in the range [0, 300].
    -100 <= Node.val <= 100
    The list is guaranteed to be sorted in ascending order.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 3 Feb 2022
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

struct ListNode* deleteDuplicates(struct ListNode* head){
  struct ListNode* current = head;
  while (current != NULL && current->next != NULL) {
    if (current->next->val == current->val) {
      current->next = current->next->next;
    } else {
      current = current->next;
    }
  }
  return head;
}

/**
   Create Linked List
**/
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

void test_leetcode() {
  int ret = 0;
  struct ListNode* head1 = NULL;

  /* Make sure it works only with decending linklist */
  push (&head1, 2);
  push (&head1, 4);
  push (&head1, 4);

  debug("Input linkedList");
  printList(head1);
  struct ListNode* result = deleteDuplicates(head1);
  debug("Output LinkedList");
  printList(result);
}

void test_CrackIVI() {

}

int main (int argc, char **argv) {
  test_leetcode();
  test_CrackIVI();
  return 0;
}

/**

 **/
