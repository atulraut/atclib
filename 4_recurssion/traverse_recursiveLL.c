/***
    Algo in C by Robert S.
    Linkedlist traveser list using Recursive Mechanism

    Date: Tuesday June 28 2022
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
  int data;
  struct ListNode *next;
};

void push(struct ListNode** head_ref, int data) {
  struct ListNode* nn = (struct ListNode*)malloc(sizeof(struct ListNode));
  nn->data = data;
  nn->next = (*head_ref);
  (*head_ref) = nn;
}

void printList(struct ListNode* head) {
  struct ListNode* trav = head;
  while (trav != NULL) {
    debug("%d  ", trav->data);
    trav = trav->next;
  }
}

//void (*visit) (struct list *ll);
//void m_traverseR(struct list *l, void (*visit)(struct list *ll));

/* Algo in C #algoinc */
void m_traverseL(struct ListNode *this_head, void (*visit)(struct ListNode *this_head)) {
  debug ("Enter");
  if (this_head == NULL)
    return;
  m_traverseL(this_head->next, visit);
  (*visit)(this_head);
}

void m_traverseR(struct ListNode *this_head, void (*visit)(struct ListNode *this_head)) {
  debug ("Enter");
  if (this_head == NULL)
    return;
  (*visit)(this_head);
  m_traverseR(this_head->next, visit);
}

void visit (struct ListNode *this_head) {
  printf ("\n----------:: Output ::-----------\n");
  struct ListNode *temp = this_head;
  printf ("->[%d]", temp->data);
  printf ("\n----------:: End ::-----------\n");
}

void m_traverse(void *ptr) {
  struct ListNode *head = (struct ListNode*)ptr;
  m_traverseR(head, visit);
  // m_traverseL(head, visit);
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
  debug("*** Traverse linked List ***");
  m_traverse(head);
  printList(head);
}

int main () {
  test_remove();
}

/**
   => ./a.out
   [test_remove] L=83 :Given linked list

   [printList] L=36 :1
   [printList] L=36 :2
   [printList] L=36 :3
   [printList] L=36 :4
   [printList] L=36 :5
   [test_remove] L=85 :*** Traverse linked List ***
   [m_traverseL] L=46 :Enter
   [m_traverseL] L=46 :Enter
   [m_traverseL] L=46 :Enter
   [m_traverseL] L=46 :Enter
   [m_traverseL] L=46 :Enter
   [m_traverseL] L=46 :Enter

   ----------:: Output ::-----------
   ->[5]
   ----------:: End ::-----------

   ----------:: Output ::-----------
   ->[4]
   ----------:: End ::-----------

   ----------:: Output ::-----------
   ->[3]
   ----------:: End ::-----------

   ----------:: Output ::-----------
   ->[2]
   ----------:: End ::-----------

   ----------:: Output ::-----------
   ->[1]
   ----------:: End ::-----------
   [printList] L=36 :1
   [printList] L=36 :2
   [printList] L=36 :3
   [printList] L=36 :4
   [printList] L=36 :5


   atul@Raigad:~/dev/c/atclib/recursion
   => ./a.out
   [test_remove] L=83 :Given linked list

   [printList] L=36 :1
   [printList] L=36 :2
   [printList] L=36 :3
   [printList] L=36 :4
   [printList] L=36 :5
   [test_remove] L=85 :*** Traverse linked List ***
   [m_traverseR] L=54 :Enter

   ----------:: Output ::-----------
   ->[1]
   ----------:: End ::-----------
   [m_traverseR] L=54 :Enter

   ----------:: Output ::-----------
   ->[2]
   ----------:: End ::-----------
   [m_traverseR] L=54 :Enter

   ----------:: Output ::-----------
   ->[3]
   ----------:: End ::-----------
   [m_traverseR] L=54 :Enter

   ----------:: Output ::-----------
   ->[4]
   ----------:: End ::-----------
   [m_traverseR] L=54 :Enter

   ----------:: Output ::-----------
   ->[5]
   ----------:: End ::-----------
   [m_traverseR] L=54 :Enter
   [printList] L=36 :1
   [printList] L=36 :2
   [printList] L=36 :3
   [printList] L=36 :4
   [printList] L=36 :5
**/
