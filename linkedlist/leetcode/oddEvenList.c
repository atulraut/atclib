/***
 * 328. Odd Even Linked List
 * https://leetcode.com/problems/odd-even-linked-list/
 * Given a singly linked list, group all odd nodes together followed by the even nodes.
 * Please note here we are talking about the node number and not the value in the nodes
 * You should try to do it in place. The program should run in O(1) space complexity
 * and O(nodes) time complexity.
 * Example 1:
 * Input: 1->2->3->4->5->NULL
 * Output: 1->3->5->2->4->NULL
    https://www.youtube.com/watch?v=YE9ggKeHeK0
 * Date : August 03, 2020 11AM
 * San Diego
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
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct node {
  int val;
  struct node* next;
};

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

/* Sort Odd Even */
struct node* oddEvenList(struct node* head) {
  //Boundary cases
  if(!head)
    return head;

  struct node *odd = head;
  struct node *even = head->next;
  struct node *even_head = head->next;

  while(even && even->next) {
    odd->next = odd->next->next;
    even->next = even->next->next;
    odd = odd->next;
    even = even->next;
  }
  odd->next = even_head;
  return head;
}

/* Sort Even Odd */
struct node* evenOddList(struct node* head) {
  //Boundary cases
  if(!head)
    return head;

  struct node *odd = head;
  struct node *even = head->next;
  struct node *odd_head = head;
  head = head->next;

  while(even && even->next) {
    odd->next = odd->next->next;
    even->next = even->next->next;
    odd = odd->next;
    if (even->next == NULL)
      break;
    even = even->next;
  }
  even->next = odd_head;
  return head;
}

void push(struct node** head_ref, int val) {
  struct node* nn = (struct node*)malloc(sizeof(struct node));
  nn->val = val;
  nn->next = (*head_ref);
  (*head_ref) = nn;
}

void printList(struct node* head) {
  struct node* trav = head;
  while (trav != NULL) {
    debug("%d  ", trav->val);
    trav = trav->next;
  }
}

int main (int argc, char **argv) {
  int ret = 0;
  /* Start with the empty list */
  struct node* head = NULL;

  push(&head, 5);
  push(&head, 4);
  push(&head, 3);
  push(&head, 2);
  push(&head, 1);

  debug("Given linked list\n");
  printList(head);

  debug("OddEven LinkedList!");
  head = oddEvenList(head);
  printList(head);
  debug("EvenOdd LinkedList!");
  head = evenOddList(head);
  printList(head);

  return 0;
}

/**
   => ./a.out
   [main] L=105 :Given linked list
   [printList] L=89 :1
   [printList] L=89 :2
   [printList] L=89 :3
   [printList] L=89 :4
   [printList] L=89 :5
   [main] L=108 :Sort EvenOdd LinkedList!
   [printList] L=89 :1
   [printList] L=89 :3
   [printList] L=89 :5
   [printList] L=89 :2
   [printList] L=89 :4
**/

/**
   => ./a.out
   [main] L=127 :Given linked list
   [printList] L=111 :1
   [printList] L=111 :2
   [printList] L=111 :3
   [printList] L=111 :4
   [printList] L=111 :5
   [main] L=130 :EvenOdd LinkedList!
   [printList] L=111 :2
   [printList] L=111 :4
   [printList] L=111 :1
   [printList] L=111 :3
   [printList] L=111 :5
**/
