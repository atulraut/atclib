/***
    https://leetcode.com/problems/linked-list-cycle-ii/
    142. Linked List Cycle II

    Given the head of a linked list, return the node where
    the cycle begins. If there is no cycle, return null.

    There is a cycle in a linked list if there is some node in
    the list that can be reached again by continuously following
    the next pointer. Internally, pos is used to denote the index
    of the node that tail's next pointer is connected to (0-indexed).
    It is -1 if there is no cycle. Note that pos is not passed as a parameter.

    Do not modify the linked list.

    Input: head = [3,2,0,-4], pos = 1
    Output: tail connects to node index 1
    Explanation: There is a cycle in the linked list, where tail connects to the second node.

    Input: head = [1,2], pos = 0
    Output: tail connects to node index 0
    Explanation: There is a cycle in the linked list, where tail connects to the first node.

    Input: head = [1], pos = -1
    Output: no cycle
    Explanation: There is no cycle in the linked list.

    Constraints:
    The number of the nodes in the list is in the range [0, 104].
    -105 <= Node.val <= 105
    pos is -1 or a valid index in the linked-list.

    Follow up: Can you solve it using O(1) (i.e. constant) memory?
    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 18 Jan 2022
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

struct ListNode *detectCycle(struct ListNode *head) {
  struct ListNode *slow = head;
  struct ListNode *fast = head;
  unsigned char is_loop = 0;
  if(head == NULL)
    return NULL;

  while (fast && slow && fast->next) {
    slow = slow->next;
    fast = fast->next->next;

    if (slow == fast) {
      is_loop = 1;
      break;
    }
  }
  debug ("is_loop = %d", is_loop);
  if(!is_loop) {
    debug ("Returning NULL!");
    return NULL;
  } else {
    slow = head;
    while (slow != fast) {
      slow = slow->next;
      fast = fast->next;
    }
    debug ("slow->%pK", slow);
    return slow;
  }
}

void push(struct ListNode** head_ref, int val) {
  struct ListNode* nn = (struct ListNode*)malloc(sizeof(struct ListNode));
  nn->val = val;
  nn->next = (*head_ref);
  (*head_ref) = nn;
}

static struct ListNode* two = NULL;
static struct ListNode* four = NULL;
void push1(struct ListNode** head_ref, int val) {
  struct ListNode* nn = (struct ListNode*)malloc(sizeof(struct ListNode));
  nn->val = val;
  if (val != 4)
    nn->next = (*head_ref);
  (*head_ref) = nn;

  if (val == 2) {
    two = (*head_ref);
    debug ("two = %pK val = %d", two, val);
  }
  if (val == 4) {
    nn->next = two;
    debug ("four = %pK val = %d nn->next->val=%d", nn->next, val, nn->next->val);
  }
}

void printList(struct ListNode* head) {
  struct ListNode* trav = head;
  while (trav != NULL) {
    debug("%d  ", trav->val);
    trav = trav->next;
  }
}

/* Rewrite to fix cycle code */
void detect_loop_ll(void* ptr) {
  int ret = 0;
  struct ListNode* head = ptr;
  struct ListNode* retur = detectCycle(head);
  debug("Output = %d head->val=%pK", ret, retur);
  printList(retur);
}

struct ListNode* make_linkedlist(void *ptr) {
  struct ListNode* head = ptr;
  push(&head, 3);
  push(&head, 2);
  push(&head, 1);
  push(&head, 4);
/*
  push(&head, 4);
  push(&head, 5);
  push(&head, 6);
  push(&head, 7);
*/
  debug("Given linked list\n");
  //  printList(head);
  return head;
}

void reverse_linked_list(void* ptr) {
  debug("Enter!");
  struct ListNode* head = ptr;
  printList(head);
  struct ListNode* trav;
  struct ListNode* temp = head;
  head = NULL;

  while(temp) {
    trav = temp->next;
    temp->next = head;
    head = temp;
    temp = trav;
  }
  debug("Given linked list\n");
  printList(head);
}

int main (int argc, char **argv) {
  struct ListNode* head = NULL;
  head = make_linkedlist(head);

    /* Create a loop for testing */
    head->next->next->next->next = head;
  //  detect_loop_ll(head);

  reverse_linked_list(head);
  return 0;
}

/**

 **/
