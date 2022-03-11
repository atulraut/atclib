/***
    2.1	: Crack Coding IVI :-
    Write code to remove duplicates from an unsorted linked list.
    FOLLOW UP
    How would you solve this problem if a temporary buffer is not allowed?

    https://leetcode.com/problems/remove-linked-list-elements

    Given the head of a linked list and an integer val,
    remove all the nodes of the linked list that has
    Node.val == val, and return the new head.

    Input: head = [1,2,6,3,4,5,6], val = 6
    Output: [1,2,3,4,5]

    Input: head = [], val = 1
    Output: []

    Input: head = [7,7,7,7], val = 7
    Output: []

    The number of nodes in the list is in the range [0, 104].
    1 <= Node.val <= 50
    0 <= val <= 50

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Sat Mar  5 11:23:24 PST 2022
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

#define NHASH 10

enum hash_ops_type {
  HASH_SEARCH = 1,
  HASH_INSERT = 2
} has_ops;

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

/*
  Hashing Implemetation :
***/
struct hash_map {
  int key;
  int val;
};

struct hash_map *systab[NHASH] = {NULL};

int get_hash(int val) {
  return val%NHASH;
}

struct node *create_node(int val) {
  struct node *temp = malloc(sizeof(*temp));
  temp->val = val;
  temp->next = NULL;
  return temp;
}

void m_Init() {
  for (int i=0; i<NHASH; ++i) {
    systab[i] = NULL;
  }
}

struct hash_map* lookup(int key, int val, int isCreate) {
  struct hash_map* hmap = NULL;
  if (HASH_SEARCH == isCreate) {
    hmap = systab[key];
    if(NULL != hmap)
      return hmap;
    else
      return NULL;
  }
  if(HASH_INSERT == isCreate) {
    hmap = systab[key];
    if (NULL == hmap) {
      hmap = (struct hash_map*)malloc(sizeof(struct hash_map));
      hmap->key = key;
      hmap->val = val;
      systab[key] = hmap;
      return hmap;
    }
  }
}

struct node* removeElements(struct node* head) {
  int key;
  struct node* curr_trav = head;
  struct node* prev = NULL;
  struct hash_map* hmap = NULL;
  struct node* temp;

  while (curr_trav != NULL) {
    //    debug("Enter val = %d", curr_trav->val);
    key = get_hash(curr_trav->val);
    hmap = lookup(key, curr_trav->val, HASH_SEARCH);
    if(NULL == hmap)
      lookup(key, curr_trav->val, HASH_INSERT);
    else {
      // Remove duplicates from linked list
      if (curr_trav->next == NULL) {
	//	debug("Condition Met prev = %pK prev_val = %d trav = %pK trav_val = %d", prev, prev->val, curr_trav, curr_trav->val);
	temp = curr_trav;
	curr_trav = NULL;
	prev->next = NULL;
	free(temp);
	temp = NULL;
	break;
      } else {
	temp = curr_trav;
	curr_trav = prev;
	prev->next = temp->next;
	temp->next = NULL;
	free(temp);
      }
    }
    prev = curr_trav;
    curr_trav = curr_trav->next;
  }

  return head;
}

/*
  Without a buffer, we can iterate with two pointers: “current”
  does a normal iteration, while “runner” iterates through all
  prior nodes to check for dups. Runner will only see one dup
  per node, because if there were multiple duplicates they
  would have been removed already.
*/
struct node* deleteDups2(struct node* head) {
  if (head == NULL)
    return NULL;

  struct node* previous = head;
  struct node* current = previous->next;

  while (current != NULL) {
    struct node* runner = head;
    while (runner != current) { // Check for earlier dups
      if (runner->val == current->val) {
	struct node* tmp = current->next; // remove current
	previous->next = tmp;
	current = tmp; // update current to next node
	break; // all other dups have already been removed
      }
      runner = runner->next;
    }
    if (runner == current) { // current not updated - update now
      previous = current;
      current = current->next;
    }
  }
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

struct node* test1(struct node* head) {
  head = removeElements(head);
  return head;
}

struct node* test2(struct node* head) {
  head = deleteDups2(head);
  return head;
}

int main (int argc, char **argv) {
  int ret = 0;
  /* Start with the empty list */
  struct node* head = NULL;

  push(&head, 1);
  //  push(&head, 1);
  push(&head, 2);
  push(&head, 3);
  push(&head, 3);
  push(&head, 4);
  push(&head, 4);
  //  push(&head, 4);
  push(&head, 5);
  //  push(&head, 2);
  //push(&head, 2);

  debug("Given linked list\n");
  printList(head);

  debug("Remove Duplicates from LinkedList!");
  //  head = test1(head);
  head = test2(head);
  printList(head);

  return 0;
}

/**
   => ./a.out
   [main] L=145 :Given linked list

   [printList] L=127 :6
   [printList] L=127 :5
   [printList] L=127 :4
   [printList] L=127 :6
   [printList] L=127 :3
   [printList] L=127 :2
   [printList] L=127 :1
   [main] L=148 :Remove Duplicates from LinkedList!
   [printList] L=127 :5
   [printList] L=127 :4
   [printList] L=127 :3
   [printList] L=127 :2
   [printList] L=127 :1
**/
