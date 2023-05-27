/**
   Linkedlist Template
   Add    - Push
   Remove - Pop
**/
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

void push(struct ListNode** head_ref, int val) {
  struct ListNode* nn = (struct ListNode*)malloc(sizeof(struct ListNode));
  nn->val = val;
  nn->next = (*head_ref);
  (*head_ref) = nn;
}

void pop(struct ListNode** head_ref) {
  struct ListNode* temp = (*head_ref);
  int val = temp->val;
  (*head_ref) = (*head_ref)->next;
  temp->next = NULL;
  free(temp);
  temp = NULL;
}

void printList(struct ListNode* head) {
  struct ListNode* trav = head;
  while (trav != NULL) {
    debug("->[%d]", trav->val);
    trav = trav->next;
  }
}

void test() {
  int ret = 0;
  /* Start with the empty list */
  struct ListNode* head = NULL;

  push(&head, 4);
  push(&head, 3);
  push(&head, 2);
  push(&head, 1);

  debug("Given linked list\n");
  printList(head);
  debug("Test Pop");
  pop(&head);
  debug("Pop LinkedList!");
  printList(head);
  pop(&head);
  debug("Pop LinkedList!");
  printList(head);
  pop(&head);
  debug("Pop LinkedList!");
  printList(head);
  pop(&head);
  debug("Pop LinkedList!");
  printList(head);
}

int main (int argc, char **argv) {
  test();
  return 0;
}
/**
   => ./a.out
   [test] L=68 :Given linked list

   [printList] L=53 :->[1]
   [printList] L=53 :->[2]
   [printList] L=53 :->[3]
   [printList] L=53 :->[4]
   [test] L=70 :Test Pop
   [pop] L=41 :Enter1
   [pop] L=47 :Worked!
   [test] L=72 :Pop LinkedList!
   [printList] L=53 :->[2]
   [printList] L=53 :->[3]
   [printList] L=53 :->[4]
   [pop] L=41 :Enter1
   [pop] L=47 :Worked!
   [test] L=75 :Pop LinkedList!
   [printList] L=53 :->[3]
   [printList] L=53 :->[4]
   [pop] L=41 :Enter1
   [pop] L=47 :Worked!
   [test] L=78 :Pop LinkedList!
   [printList] L=53 :->[4]
   [pop] L=41 :Enter1
   [pop] L=47 :Worked!
   [test] L=81 :Pop LinkedList!
**/
