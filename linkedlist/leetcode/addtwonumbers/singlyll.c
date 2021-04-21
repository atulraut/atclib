/*
* Aim : Singly Linked List.
* Date : Sunday, May 24 2020
* Date : Friday, March 11 2021
* San Diego, CA
* By : Atul R. Raut
* valgrind -v --leak-check=full --show-reachable=yes ./main
***/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

static int get_input(char *cmd) {
  int res = 1;

  printf ("Enter number! \n");
  while(fgets (cmd, 20, stdin) && cmd[0] != '\n')
    res = atoi(cmd);
  return res;
}

struct list* m_Init (struct list *ll){
  struct list *list = NULL;

  list = (struct list *)malloc (sizeof (struct list));
  if (NULL == list)
    return NULL;

  list->head = NULL;
  return list;
}

static struct list_node* m_CreateNodeL (int data){
  struct list_node *nn = NULL;
  nn = (struct list_node*)malloc(sizeof (struct list_node *));
  if (nn == NULL)
    return NULL;
  nn->data  = data;
  nn->next = NULL;
  return nn;
}

void m_Addfirst(void *ptr) {
  struct list *list = (struct list *)ptr;
  struct list_node *nn = NULL;
  char cmd[20] = {0};
  int data;

  printf ("Selected Linked List Type l=%p L1=%p L2=%p\n", list, list1, list2);

  data = get_input(cmd);

  nn = m_CreateNodeL (data);
  nn->data = data;
  if (NULL == list->head) {
    list->head = (struct list_node *)nn;
    nn->next = NULL;
  } else {
    struct list_node *trav;
    trav = (struct list_node *)list->head;
    nn->next = trav;
    list->head = (struct list_node *)nn;
  }
}

void m_Addlast(void *ptr) {
  struct list *list = (struct list *)ptr;
  struct list_node *nn = NULL;
  char cmd[20] = {0};
  int data;

  data = get_input(cmd);
  nn = m_CreateNodeL (data);
  nn->data = data;
  if (NULL == list->head) {
    list->head = (struct list_node *)nn;
    nn->next = NULL;
  } else {
    struct list_node *trav;
    trav = (struct list_node *)list->head;
    while (trav->next != NULL)
      trav = trav->next;
    trav->next = nn;
    nn->next = NULL;
  }
}

void m_Delfirst(void *ptr) {
  struct list *ll = (struct list *)ptr;
  if (ll == NULL)
    printf ("\n Empty Link List.");
  else {
    struct list_node *temp = NULL;
    temp = (struct list_node *)ll->head;
    if (temp->next == NULL) {
      free (temp);
      temp = NULL;
    }
    else {
      temp = (struct list_node *)ll->head;
      ll->head = (struct list_node *)temp->next;
      free (temp);
      temp = NULL;
    }
  }
}

void m_Freelist(void *ptr) {
  struct list *ll = (struct list *)ptr;
  if (ll->head == NULL)
    printf ("\n Empty Link List.");
  else {
    struct list_node *temp = NULL;
    struct list_node *trav = NULL;
    temp = (struct list_node *)ll->head;
    while (temp != NULL) {
      trav = temp->next;
      free(temp);
      temp = NULL;
      temp = trav;
    }
    ll->head = NULL;
  }
}

static void swap (struct list_node *s, struct list_node *m) {
  int temp;
  temp = s->data;
  s->data = m->data;
  m->data = temp;
}

void m_Sortlist(void *_list) {
  int flag = 0;
  struct list *list = (struct list*)_list;
  struct list_node *head = (struct list_node*)list->head;
  struct list_node *start = head;
  struct list_node *trav, *min;

  while (start->next) {
    min = start;
    trav = start->next;
    while (trav) {
      if (min->data > trav->data) {
	min = trav;
	flag = 1; // to check we really needs to swap data
      }
      trav = trav->next;
    }
    if(flag) {
      swap (start, min);
      flag = 0; // Reset the flag
    }
    start = start->next;
  }
  m_Display(_list);
}

/*
  LeetCode:   Middle of the Linked List
*/
void middleNode(void *ptr) {
  struct list *ll = (struct list *)ptr;
  struct list_node *temp = NULL;
  struct list_node *hare, *tortoise;
  temp = (struct list_node*)ll->head;
  if (NULL == ll->head) {
    printf ("Empty link list \n");
    return;
  } else {
    hare = tortoise = temp;
    while (hare && hare->next) {
      hare = hare->next->next;
      tortoise = tortoise->next;
      printf ("->[%d]", temp->data);
    }
  } // else Ends
  //return tortoise;
  printf ("[%s] Middle Node = %d \n", __func__, tortoise->data);
}

/**
  https://leetcode.com/problems/add-two-numbers/
  You are given two non-empty linked lists representing two non-negative
  integers.
  The digits are stored in reverse order, and each of their nodes
  contains a single digit. Add the two numbers and return the sum
  as a linked list.
  You may assume the two numbers do not contain any leading zero, except
  the number 0 itself.
**/
static struct list_node* addTwoNumbers(struct list* list1, struct list* list2) {
//static void addTwoNumbers(void *ptr) {
  struct list_node temp;
  struct list_node *trav1;
  struct list_node *trav2;
  int remainder = 0, sum;

  trav1 = (struct list_node *)list1->head;
  trav2 = (struct list_node *)list2->head;

  struct list_node* curr = &temp;

  while (trav1 != NULL || trav2 != NULL || remainder != 0) {
    sum = remainder + (trav1 == 0 ? 0 : trav1->data) + (trav2 == 0 ? 0: trav2->data);
    debug ("sum = %d, remainder = %d", sum, remainder);
    remainder = sum/10;
    sum %= 10;
    debug ("sum = %d, remainder = %d", sum, remainder);
    curr->next = (struct list_node*)malloc(sizeof(struct list_node));
    curr->next->next = NULL;
    curr->next->data = sum;
    curr = curr->next;
    trav1 = (trav1 == 0 ? 0 : trav1->next);
    trav2 = (trav2 == 0 ? 0 : trav2->next);
  }

  return temp.next;
}
/**
   L1 :-> 2 4
   L2 :-> 4 6
   O/P:-> 6 0 1
   Calling command: Add Two Int of different Linked List
   [addTwoNumbers] L=238 :sum = 6, remainder = 0
   [addTwoNumbers] L=241 :sum = 6, remainder = 0
   [addTwoNumbers] L=238 :sum = 10, remainder = 0
   [addTwoNumbers] L=241 :sum = 0, remainder = 1
   [addTwoNumbers] L=238 :sum = 1, remainder = 1
   [addTwoNumbers] L=241 :sum = 1, remainder = 0
**/

void m_addTwoNumbers(void *_ptr) {
  struct list *list3 = NULL;
  struct list_node* result = addTwoNumbers(list1, list2);
  list3 = (struct list *)malloc(sizeof(struct list));
  list3->head = (struct list_node *)result;
  m_Display(list3);
  free(list3);
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
**/
void m_mergeTwoLinkedList (void *ptr) {
  int flag = 1;
  struct list *list3, l3;
  list3 = m_Init(&l3);
  if (NULL == list1 || NULL == list2 || NULL == list3)
    return;

  struct list_node *trav3 = list3->head = list1->head;
  struct list_node *trav1 = (struct list_node *)list1->head;
  trav1 = trav1->next;
  struct list_node *trav2 = (struct list_node *)list2->head;

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

/**
    Sort & Merged Linked List
    Assume : Caller Created 2 Linked List.
 **/
static struct list_node * sortedMergeLL(struct list_node* a, struct list_node* b) {
  struct list_node* result = NULL;

  /* Base cases */
  if (a == NULL)
     return(b);
  else if (b==NULL)
     return(a);

  /* Pick either a or b, and recur */
  if (a->data <= b->data) {
     result = a;
     result->next = sortedMergeLL(a->next, b);
  } else {
     result = b;
     result->next = sortedMergeLL(a, b->next);
  }
  return(result);
}

void m_sortedMergeLL(void *_ptr) {
  struct list *list3 = NULL;
  struct list_node* result = sortedMergeLL(list1->head, list2->head);
  list3->head = (struct list_node *)result;
  m_Display(list3);
}

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
 */
struct list_node* mergeTwoLists(struct list_node* l1, struct list_node* l2) {
    if (l1 == NULL) {
        return l2;
    }else if (l2 == NULL){
        return l1;
    }else if (l1->data < l2->data){
        l1->next = mergeTwoLists(l1->next, l2);
        return l1;
    }else{
        l2->next = mergeTwoLists(l1, l2->next);
        return l2;
    }
}

struct list_node* mergeKLists(struct list_node** lists, int listsSize){
  if (listsSize == 0) {
    return NULL;
  }
  if (listsSize == 1) {
    return lists[0];
  }
  for (int i = 0,j = listsSize - 1; i < j; i++, j--) {
    lists[i] = mergeTwoLists(lists[i], lists[j]);
    listsSize--;
  }
  return mergeKLists(lists, listsSize);
}

struct list_node* helper(struct list_node* current, struct list_node* head, bool* ans) {
  if(current == NULL) {
    return head;
  } else {
    head = helper(current->next, head, ans);
    if(*ans) {
      if(current->data != head->data) {
	*ans = false;
	return head->next;
      } else {
	return head->next;
      }
    }
  }
  return head;
}

//bool isPalindrome(struct ListNode* head) {
void m_isPalindrome(void *ptr) {
    struct list *ll = (struct list *)ptr;
    struct list_node *head = (struct list_node*)ll->head;
    bool* ans = malloc(sizeof(bool));
    *ans = true;
    helper(head, head, ans);
    debug("IsPalindrome = %d", *ans);
    //    return *ans;
}

/**
   86. Partition List Medium
   https://leetcode.com/problems/partition-list/
   Given the head of a linked list and a value x, partition it such
   that all nodes less than x come before nodes greater than or equal to x.

   You should preserve the original relative order of the nodes in each
   of the two partitions.
   Input: head = [1,4,3,2,5,2], x = 3
   Output: [1,2,2,4,3,5]
   Input: head = [2,1], x = 2
   Output: [1,2]
   Date: 04/14/2021 April.
 */
struct list_node* m_partition(struct list_node* head, int x) {
  struct list_node *before_x = (struct list_node *) malloc (sizeof(struct list_node));
  struct list_node *after_x = (struct list_node *) malloc (sizeof(struct list_node));

  struct list_node *dummy_after_x = (struct list_node *) malloc (sizeof(struct list_node));
  struct list_node *dummy_before_x = (struct list_node *) malloc (sizeof(struct list_node));

  dummy_after_x = after_x;
  dummy_before_x = before_x;

  while(head != NULL) {
    if (head->val < x) {
      before_x->next = head;
      before_x = before_x->next;
    }
    else {
      after_x->next = head;
      after_x = after_x->next;
    }
    head = head->next;
  }

  after_x->next = NULL;
  before_x->next = dummy_after_x->next;
  return dummy_before_x->next;
}


void m_Display(void *ptr){
  struct list *list = (struct list *)ptr;

  printf ("\n----------:: Output ::-----------\n");
  struct list_node *temp = NULL;
  temp = (struct list_node*)list->head;
  if (NULL == list->head) {
    printf ("Empty link list \n");
    return;
  } else {
    while (temp != NULL) {
      printf ("->[%d]", temp->data);
      temp = temp->next;
    }
  }
  printf ("\n----------:: End ::-----------\n");
  //	m_Middlenode(ptr);
}

void m_quit(void *_ptr) {
  printf ("Good Bye! \n");
  exit(0);
}
