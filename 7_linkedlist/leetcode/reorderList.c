/***
    https://leetcode.com/problems/reorder-list/
    Reorder List

    You are given the head of a singly linked-list. The list can be represented as:

    L0 → L1 → … → Ln - 1 → Ln
    Reorder the list to be on the following form:

    L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
    You may not modify the values in the list's nodes. Only nodes themselves may be changed.

    Input: head = [1,2,3,4]
    Output: [1,4,2,3]

    Input: head = [1,2,3,4,5]
    Output: [1,5,2,4,3]

    Constraints:
    The number of nodes in the list is in the range [1, 5 * 104].
    1 <= Node.val <= 1000

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address reorderList.c -lm

    Date: 12/23/21
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

/**
   Solution Bricks:
   This problem is a combination of these three easy problems:

   1] Middle of the Linked List.
   2] Reverse Linked List.
   3] Merge Two Sorted Lists.

**/

struct ListNode* m_middlenode(struct ListNode* ptr) {
  if (ptr == NULL) {
    return ptr;
  }
  struct ListNode* slow = ptr;
  struct ListNode* fast = ptr;
  while (fast != NULL && fast->next != NULL) {
    slow = slow->next;
    fast = fast->next->next;
  }
  return slow;
}

void m_reverse (struct ListNode* head) {
  struct ListNode *trav = NULL;
  struct ListNode *temp = NULL;
  if (head == NULL) {
    printf ("\nEmpty link list.\n");
  } else {
    printf ("\n Inside Reverse Link List\n");
    // Logic to reverse link list.
    temp = head;
    head = NULL;
    while (temp != NULL) {
      printf ("temp=[%p][%d]\n", temp,temp->val);
      trav = temp->next;
      temp->next = head; // attach NODE
      head = temp;     // L1 Make NULL, L2 Attach Node
      temp = trav;
      printf ("temp=[%p][%d]\n", temp,temp->val);
    }
  }
}

/**
   Merged Unsorted Linked List :
   Given two character array of limited size, create a link list
   with elements from both array in alternate way
   Example
   arr1 = a,b,c,d,e
   arr2 = x.y.z
   link list = a->x->b->y->c->z->d
   Assumption : We have list1 & list2 available to Merge (No Sorting)
   Date : 11 March 2021, San Diego, CA
**
void m_mergeTwoLinkedList (struct ListNode* list1, struct ListNode* list2, struct ListNode* ptr) {
  int flag = 1;
  struct ListNode *list3, l3;
  //  list3 = m_Init(&l3);
  if (NULL == list1 || NULL == list2 || NULL == list3)
    return;

  struct ListNodee *trav3 = list3->head = list1->head;
  struct ListNode *trav1 = (struct ListNode *)list1->head;
  trav1 = trav1->next;
  struct ListNode *trav2 = (struct ListNode *)list2->head;

  while (trav1 != NULL && trav2 != NULL) {
    if (flag) { // Add L2
      trav3->next = trav2;
      trav2 = trav2->next;
    } else {    // Add L1
      trav3->next = trav1;
      trav1 = trav1->next;
    }
    trav3 = trav3->next;
    flag = !flag;
  }

  // if there are still some elements in either list, just keep adding them.
  while (trav1 != NULL) {
    trav3->next = trav1;
    trav1 = trav1->next;
    trav3 = trav3->next;
  }
  while (trav2 != NULL) {
    trav3->next = trav2;
    trav2 = trav2->next;
    trav3 = trav3->next;
  }

  m_Display(list3);
}
*/

struct ListNode* getMid(struct ListNode* head) {
  struct ListNode* fast = head;
  struct ListNode* slow = head;
  while(fast->next != NULL && fast->next->next != NULL) {
    fast = fast->next->next;
    slow = slow->next;
  }
  return slow;
}

struct ListNode* reverseList(struct ListNode* head) {
  struct ListNode* tail = NULL;
  while(head != NULL) {
    struct ListNode* cur = head;
    head = head->next;

    cur->next = tail;
    tail = cur;
  }

  return tail;
}

void merge(struct ListNode* head1, struct ListNode* head2) {
  struct ListNode* head = head1;

  while(head2 != NULL) {
    struct ListNode* next = head2->next;
    head2->next = head->next;
    head->next = head2;

    head = head->next->next;
    head2 = next;
  }
}

void reorderList(struct ListNode* head) {
  if(head == NULL || head->next == NULL || head->next->next == NULL)
    return;

  struct ListNode* mid = getMid(head);
  struct ListNode* secondHalf = mid->next;
  mid->next = NULL;
  secondHalf = reverseList(secondHalf);
  merge(head, secondHalf);
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
  debug("ReOrdered List");
  reorderList(head);
  printList(head);
  return 0;
}

/**
   => ./a.out
   [main] L=231 :Given linked list

   [printList] L=215 :1
   [printList] L=215 :2
   [printList] L=215 :3
   [printList] L=215 :4
   [printList] L=215 :5
   [main] L=233 :ReOrdered List
   [printList] L=215 :1
   [printList] L=215 :5
   [printList] L=215 :2
   [printList] L=215 :4
   [printList] L=215 :3
**/

/**
   Complexity Analysis
   Time complexity: O(N). There are three steps here. To identify the middle
   node takes O(N) time. To reverse the second part of the list, one
   needs N/2 operations. The final step, to merge two lists, requires N/2
   operations as well. In total, that results in O(N) time complexity.

   Space complexity: O(1), since we do not allocate any additional data structures.
**/
