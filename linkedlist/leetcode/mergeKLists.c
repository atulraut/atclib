/***
    23. Merge k Sorted Lists
    https://leetcode.com/problems/merge-k-sorted-lists/
    You are given an array of k linked-lists lists, each linked-list is
    sorted in ascending order.
    Merge all the linked-lists into one sorted linked-list and return it.
    Example 1:
    Input: lists = [[1,4,5],[1,3,4],[2,6]]
    Output: [1,1,2,3,4,4,5,6]
    Explanation: The linked-lists are:
    [
    1->4->5,
    1->3->4,
    2->6
    ]
    merging them into one sorted list:
    1->1->2->3->4->4->5->6
    Example 2:
    Input: lists = []
    Output: []
    Constraints:
    k == lists.length
    0 <= k <= 10^4
    0 <= lists[i].length <= 500
    -10^4 <= lists[i][j] <= 10^4
    lists[i] is sorted in ascending order.
    The sum of lists[i].length won't exceed 10^4.

    Ref : https://www.youtube.com/watch?v=kpCesr9VXDA

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

struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
  if (l1 == NULL) {
    return l2;
  } else if (l2 == NULL) {
    return l1;
  } else if (l1->val < l2->val) {
    l1->next = mergeTwoLists(l1->next, l2);
    return l1;
  } else {
    l2->next = mergeTwoLists(l1, l2->next);
    return l2;
  }
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize){
  if (listsSize == 0) {
    return NULL;
  }
  if (listsSize == 1) {
    return lists[0];
  }
  for (int i=0, j=listsSize - 1; i<j; i++, j--) {

    lists[i] = mergeTwoLists(lists[i], lists[j]);
    listsSize--;
  }
  return mergeKLists(lists, listsSize);
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

void test() {
  int ret = 0;
  struct ListNode* head1 = NULL;
  struct ListNode* head2 = NULL;
  struct ListNode* head3 = NULL;
  struct ListNode* head4 = NULL;

  //  [[1,4,5],[1,3,4],[2,6]]

  push (&head1, 5);
  push (&head1, 4);
  push (&head1, 2);

  push (&head2, 4);
  push (&head2, 3);
  push (&head2, 1);

  push (&head3, 6);
  push (&head3, 2);
  //  push (&head3, 10);
  //push (&head3, 7);
  /*
    push (&head4, 4);
    push (&head4, 13);
    push (&head4, 14);
    push (&head4, 4);
  */
  int listsSize = 3;
  debug("Input listsSize = %d", listsSize);
  printList(head1);
  printList(head2);
  printList(head3);
  printList(head4);

  struct ListNode* lists[] = {head1, head2, head3};
  struct ListNode* result = mergeKLists(lists, listsSize);
  ret = 1;
  debug("Output = %d", ret);
  printList(result);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   > ./a.out
   [test] L=170 :Input listsSize = 3
   [printList] L=137 :2
   [printList] L=137 :4
   [printList] L=137 :5
   [printList] L=137 :1
   [printList] L=137 :3
   [printList] L=137 :4
   [printList] L=137 :2
   [printList] L=137 :6
   [test] L=179 :Output = 1
   [printList] L=137 :1
   [printList] L=137 :2
   [printList] L=137 :2
   [printList] L=137 :3
   [printList] L=137 :4
   [printList] L=137 :4
   [printList] L=137 :5
   [printList] L=137 :6
**/
