/***
    https://leetcode.com/problems/insert-into-a-sorted-circular-linked-list/
    708. Insert into a Sorted Circular Linked List

    Given a Circular Linked List node, which is sorted in ascending order,
    write a function to insert a value insertVal into the list such that it
    remains a sorted circular list. The given node can be a reference to any
    single node in the list and may not necessarily be the smallest value in
    the circular list.

    If there are multiple suitable places for insertion, you may choose any
    place to insert the new value. After the insertion, the circular list
    should remain sorted.

    If the list is empty (i.e., the given node is null), you should create a n
    ew single circular list and return the reference to that single node.
    Otherwise, you should return the originally given node.

    Input: head = [3,4,1], insertVal = 2
    Output: [3,4,1,2]
    Explanation: In the figure above, there is a sorted circular list of
    three elements. You are given a reference to the node with value 3, and we
    need to insert 2 into the list. The new node should be inserted between
    node 1 and node 3. After the insertion, the list should look like this,
    and we should still return node 3.

    Input: head = [], insertVal = 1
    Output: [1]
    Explanation: The list is empty (given head is null). We create a new single
    circular list and return the reference to that single node.

    Input: head = [1], insertVal = 0
    Output: [1,0]

    Constraints:
    The number of nodes in the list is in the range [0, 5 * 104].
    -106 <= Node.val, insertVal <= 106

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address insert.c -lm

    Date: 12/30/2021
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
 * Definition for a Node.
 */
struct Node {
  int val;
  struct Node *next;
};

struct Node* insert(struct Node* head, int insertVal)
{
  struct Node* node = malloc(sizeof(struct Node));
  node->val = insertVal;

  if (head == NULL) {
    node->next = node;
    return node;
  }

  struct Node* pre = head;
  struct Node* cur = head->next;

  while (1) {

    // Case 1: normal ascending region
    if (pre->val <= insertVal &&
	insertVal <= cur->val) {
      break;
    }

    // Case 2: max -> min turning point
    if (pre->val > cur->val &&
	(insertVal >= pre->val ||
	 insertVal <= cur->val)) {
      break;
    }

    pre = cur;
    cur = cur->next;

    // Finished one complete cycle
    if (pre == head) {
      break;
    }
  }

  node->next = cur;
  pre->next = node;

  return head;
}

struct Node* insert_org(struct Node* head, int insertVal) {
  if (!head) {
    struct Node* head = (struct Node*)malloc(sizeof(struct Node));
    head->next = head;
    return head;
  }

  struct Node* ret = head, *curr = head;

  while (curr->next != ret) {
    int currVal = curr->val;
    int nextVal = curr->next->val;

    if (currVal > nextVal && (insertVal >= currVal || insertVal <= nextVal))
      break;

    if (currVal <= insertVal && insertVal <= nextVal)
      break;

    curr = curr->next;
  }

  printf ("--> %ld", ((sizeof(struct Node) % 8)));
  struct Node* nNode = (struct Node*)malloc((sizeof(struct Node) % 8) + 32);
  nNode->val = insertVal;
  curr->next = nNode;

  return ret;
}

void push(struct Node** thisHead, int insertVal) {
  struct Node* nn = (struct Node*)malloc(sizeof(struct Node));
  nn->val = insertVal;

  if ((*thisHead) == NULL) {
    (*thisHead) = nn;
    nn->next = (*thisHead);
    debug ("nn = %pK  %d", nn, nn->val);
  } else {
    struct Node *trav = (*thisHead);
    while(trav->next != (*thisHead))
      trav = trav->next;
    trav->next = nn;
    nn->next = (*thisHead);
    debug ("nn = %pK  %d", nn, nn->val);
  }
}

void printList(struct Node* head) {
  struct Node* trav = head;
  while (trav->next != head) {
    debug("trav = %pK trav->next = %pK val=%d  ",trav, trav->next, trav->val);
    trav = trav->next;
  }
  debug("trav = %pK trav->next = %pK val=%d  ",trav, trav->next, trav->val);
}

int main (int argc, char **argv) {
  int ret = 0;
  int insertVal = 5;
   struct Node* head = NULL;

  push(&head, 3);
  push(&head, 4);
  push(&head, 1);
  push(&head, 2);

  debug("Given linked list\n");
  printList(head);

  struct Node* result = insert(head, insertVal);
  debug("Output = %d", ret);
  printList(result);
  return 0;
}

/**
   => ./a.out
   [push] L=180 :nn = 0x16d4010K  3
   [push] L=187 :nn = 0x16d4440K  4
   [push] L=187 :nn = 0x16d4460K  1
   [push] L=187 :nn = 0x16d4480K  2
   [main] L=210 :Given linked list

   [printList] L=194 :trav = 0x16d4010K trav->next = 0x16d4440K val=3
   [printList] L=194 :trav = 0x16d4440K trav->next = 0x16d4460K val=4
   [printList] L=194 :trav = 0x16d4460K trav->next = 0x16d4480K val=1
   [printList] L=197 :trav = 0x16d4480K trav->next = 0x16d4010K val=2
   [main] L=214 :Output = 0
   [printList] L=194 :trav = 0x16d4010K trav->next = 0x16d4440K val=3
   [printList] L=194 :trav = 0x16d4440K trav->next = 0x16d44a0K val=4
   [printList] L=194 :trav = 0x16d44a0K trav->next = 0x16d4460K val=5
   [printList] L=194 :trav = 0x16d4460K trav->next = 0x16d4480K val=1
   [printList] L=197 :trav = 0x16d4480K trav->next = 0x16d4010K val=2
**/
