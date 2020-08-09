/**
 * https://leetcode.com/problems/copy-list-with-random-pointer/
 * Program : 138. Copy List with Random Pointer Using C
 * A linked list is given such that each node contains an additional random pointer 
 * which could point to any node in the list or null.
 * Return a deep copy of the list.
 * The Linked List is represented in the input/output as a list of n nodes. Each node
 * is represented as a pair of [val, random_index] where:
 * val: an integer representing Node.val
 * random_index: the index of the node (range from 0 to n-1) where random pointer points
 * to, or null if it does not point to any node.
 *
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     struct TreeNode *next;
 *     struct TreeNode *random;
 * };
 * https://medium.com/@lenchen/leetcode-138-copy-list-with-random-pointer-c3b40af9e971
 * https://www.youtube.com/watch?v=EHpS2TBfWQg
 * https://www.youtube.com/watch?v=-ExVoZXedo4
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "list.h"

static int get_input(char *cmd) {
  int res = 1;

  printf ("Enter number! \n");

  while(fgets (cmd, 20, stdin) && cmd[0] != '\n') {
    res = atoi(cmd);
  }
  return res;
}

static struct node* m_CreateNodeL (int data){
  struct node *nn = NULL;
  nn = (struct node*)malloc(sizeof (struct node *));
  if (nn == NULL)
    return NULL;
  nn->val  = data;
  nn->next = NULL;
  nn->random = NULL;
  return nn;
}

void m_Addfirst(void *ptr) {
  head = (struct node *)ptr;
  struct node *nn = NULL;
  char cmd[20] = {0};
  int data;

  data = get_input(cmd);
  nn = m_CreateNodeL (data);
  nn->val = data;
  if (NULL == head) {
    head = nn;
    nn->next = NULL;
    nn->random = NULL;
    nn->index = cnt = 1;
  } else {
    struct node *trav;
    trav = (struct node *)head;
    while (trav->next !=NULL)
      trav = trav->next;
    trav->next = (struct node *)nn;
    nn->index = ++cnt;
  }
  printf( "[%s] val=%d nn = %pK Reached %d \n", __func__, nn->val, nn, __LINE__);
}

void m_set_random_ptr (void *ptr) {
  head = (struct node*)(ptr);
  struct node *temp = head;
  if(head == NULL) {
    printf ("Call Once m_Addfirst !\n");
    return head;
  }

  struct node *old;
   printf ("[index=%d :- val->[%d] ]\n", temp->index,  temp->val);
  while (temp->next != NULL) {
      old = temp;
      temp = temp->next;
      temp->random = old->next;
      printf ("[index=%d :- val->[%d] ]\n", temp->index,  temp->val);
    }
  temp->random = NULL;
 }

struct node* m_copyRandomList(void* ptr) {
  head = (struct node*)(ptr);
  struct node* nn, *p;
  if(head == NULL)
    return head;

  /***
   * Traverse entire list and make copies of each node, and make each 
   * copy at the next node of original one.
   */
  for(p = head; p != NULL; p = p->next->next) {
    nn = (struct node*)malloc(sizeof(struct node));
    nn->val = p->val;
    nn->next = p->next;
    p->next  = nn;
  }
    
  /***
   * Traverse entire list again. If there is an original node whose random 
   * pointer has value, set its copy node which is in the next field to be 
   * its random pointer’s next field, which is 
   * node->next->random = node->random->next
   */  
  for(p = head; p != NULL; p = p->next->next) {
    nn = p->next;
    nn->random = p->random != NULL ? p->random->next : NULL; 
  }

  /***
   * Traverse entire list last time and use strategy for solving #328 to reattach
   * link between odd and even position.
   */
  struct node dummy;
  dummy.next = head;
  struct node *temp = &dummy;    
    
  for(p = head; p != NULL; p = p->next) {
    nn = p->next;
        
    temp->next = nn;
    p->next = nn->next;
    temp = nn;
    nn->next = NULL;
  }

  printf( "[%s] Done Deep Copy! %d \n", __func__, __LINE__);
  m_Display(dummy.next);
  return dummy.next;
}

/***
 * 328. Odd Even Linked List
 * https://leetcode.com/problems/odd-even-linked-list/
 * Given a singly linked list, group all odd nodes together followed by the even nodes. 
 * Please note here we are talking about the node number and not the value in the nodes.
 * You should try to do it in place. The program should run in O(1) space complexity 
 * and O(nodes) time complexity.
 * Example 1:
 * Input: 1->2->3->4->5->NULL
 * Output: 1->3->5->2->4->NULL
 * 
 * Date : August 03, 2020 11AM
 * San Diego
 */
struct ListNode* oddEvenList(struct ListNode* head){
  if(head == NULL||0 || head -> next == NULL)return head;
  struct ListNode *odd, *first_even , *last_even, *current, *next_current;
  int i = 3;
  odd = head;
  first_even = last_even = odd -> next;
  current = first_even -> next;
  while(current != NULL){
    next_current = current -> next;
    if(i % 2 != 0){
      last_even -> next = current -> next;
      odd -> next = current;
      current -> next = first_even;
      odd = current;
    }
    else
      last_even = current;
    current = next_current;
    i++;
  }
  return head;
}

void m_Display(void *ptr){
  head = (struct node *)ptr;
  printf ("\n----------:: Output ::-----------\n");
  struct node *temp = NULL;
  temp = head;
  if (NULL == head) {
    printf( "[%s] Reached %d \n", __func__, __LINE__);
    printf ("Empty link list \n");
    return;
  }
  if (NULL == head->next) {
    printf( "[%s] val = %d addr = %pK Reached %d \n", __func__, temp->val, temp, __LINE__);
    printf ("->[%d]", temp->val);
  } else {
    printf ("cnt = %d \n", cnt);
    while (temp != NULL) {
      printf ("[i=%d :- val->[%d] temp=%pK, temp->next=%pK, temp->random=%pK]\n", temp->index,  temp->val, temp, temp->next, temp->random);
      temp = temp->next;
    }
  }
  printf ("\n----------:: End ::-----------\n");
}

void quit(void *_ptr) {
  printf ("Farewell & Thank You! \n");
  exit(0);
} 

/***
----------:: Output ::-----------
cnt = 5 
[i=1 :- val->[10] temp=0x1884830K, temp->next=0x1884850K, temp->random=(nil)K]
[i=2 :- val->[20] temp=0x1884850K, temp->next=0x1884870K, temp->random=(nil)K]
[i=3 :- val->[30] temp=0x1884870K, temp->next=0x1884890K, temp->random=(nil)K]
[i=4 :- val->[40] temp=0x1884890K, temp->next=0x18848b0K, temp->random=(nil)K]
[i=5 :- val->[50] temp=0x18848b0K, temp->next=(nil)K, temp->random=(nil)K]

----------:: End ::-----------
Enter a command 
2
Calling command: Set Random 
[index=1 :- val->[10] ]
[index=2 :- val->[20] ]
[index=3 :- val->[30] ]
[index=4 :- val->[40] ]
[index=5 :- val->[50] ]
Enter a command 

Enter a command 
3
Calling command: Copy List with Random Pointer 
[m_copyRandomList] Done Deep Copy! 141 

----------:: Output ::-----------
cnt = 5 
[i=0 :- val->[10] temp=0x18848d0K, temp->next=0x18848f0K, temp->random=(nil)K]
[i=0 :- val->[20] temp=0x18848f0K, temp->next=0x1884910K, temp->random=0x18848f0K]
[i=0 :- val->[30] temp=0x1884910K, temp->next=0x1884930K, temp->random=0x1884910K]
[i=0 :- val->[40] temp=0x1884930K, temp->next=0x1884950K, temp->random=0x1884930K]
[i=0 :- val->[50] temp=0x1884950K, temp->next=(nil)K, temp->random=(nil)K]

----------:: End ::-----------
*/
