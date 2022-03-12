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
 * https://www.youtube.com/watch?v=EHpS2TBfWQg - Good One
 * https://www.youtube.com/watch?v=-ExVoZXedo4
 *
 * Sat Mar 12 12:06:09 PST 2022
 * Folsom, CA
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

struct ListNode {
  int val;
  struct ListNode *next;
  struct ListNode *random;
};

/**
   Algo:
   I]  Crate new linkedlist copy of original linked list, set ramond ptr to NULL.
   II] Point Orignal linked list next pointer to Copied/clone linked list next ptr
   III] Point Copied/Clone linked list random ptr to Original linked list ramond ptr.
   IV] Now do this step wrt Clone linked : clone->r = clone->r->r->next this step
       takes care of copy ramdon pointer of clone linkedlist.
**/
struct ListNode*  copyRandomList(void* ptr) {
  struct ListNode* head = (struct ListNode*)(ptr);
  struct ListNode* trav = head;
  struct ListNode* nn = NULL;

  if (head == NULL)
    return head;

  /* Steps I & II */
  for(trav=head; trav != NULL; trav = trav->next->next) {
    nn = (struct ListNode*)malloc(sizeof(struct ListNode));
    nn->val = trav->val;
    nn->next = trav->next;
    trav->next = nn;
  }
  debug ("nn = %pK", nn);
  /* Step III: Copied original lists Random ptr to New list Random Pointer */
  for(trav=head; trav != NULL; trav = trav->next->next) {
    nn = trav->next;
    nn->random = (trav->random != NULL) ? trav->random->next : NULL;
  }

  /***
      Dis-assembled Org & New linked list.
   */
  struct ListNode dummy;
  dummy.next=head;
  struct ListNode *temp = &dummy;


  for(trav = head; trav != NULL; trav = trav->next) { // Check Fig-V & follow fig-IV
    nn = trav->next;

    temp->next = nn;
    trav->next = nn->next;
    temp = nn;
    nn->next = NULL;
  }

  return dummy.next;
  printf( "[%s] Done Deep Copy! %d \n", __func__, __LINE__);
  printList(dummy.next);
  //  return dummy.next;

}

void m_set_random_ptr (void *ptr) {
  struct ListNode* head = (struct ListNode*)(ptr);
  struct ListNode *temp = head;
  if(head == NULL) {
    printf ("Call Once m_Addfirst !\n");
    //    return head;
  }

  struct ListNode *old;
  //  printf ("[index=%d :- val->[%d] ]\n", temp->index,  temp->val);
  while (temp->next != NULL) {
    old = temp;
    temp = temp->next;
    temp->random = old;
    //    printf ("[index=%d :- val->[%d] ]\n", temp->index,  temp->val);
  }
  temp->random = NULL;
}

void push(struct ListNode** head_ref, int val) {
  struct ListNode* nn = (struct ListNode*)malloc(sizeof(struct ListNode));
  nn->random = NULL;
  nn->val = val;
  nn->next = (*head_ref);
  (*head_ref) = nn;
}

void printList(struct ListNode* head) {
  struct ListNode* trav = head;
  while (trav != NULL) {
    debug("val = %d   trav = %pK trav->next = %pK trav->random = %pK", trav->val, trav, trav->next, trav->random);
    trav = trav->next;
  }
}

void test() {
  struct ListNode* head = NULL;
  push(&head, 5);
  push(&head, 4);
  push(&head, 3);
  push(&head, 2);
  push(&head, 1);
  m_set_random_ptr(head);
  debug("Given linked list\n");
  printList(head);

  debug("Sort LinkedList!");
  struct ListNode* head2 = copyRandomList(head);
  printList(head2);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [test] L=138 :Given linked list

   [printList] L=125 :val = 1   trav = 0x7b0090K trav->next = 0x7b0070K trav->random = (nil)K
   [printList] L=125 :val = 2   trav = 0x7b0070K trav->next = 0x7b0050K trav->random = 0x7b0090K
   [printList] L=125 :val = 3   trav = 0x7b0050K trav->next = 0x7b0030K trav->random = 0x7b0070K
   [printList] L=125 :val = 4   trav = 0x7b0030K trav->next = 0x7b0010K trav->random = 0x7b0050K
   [printList] L=125 :val = 5   trav = 0x7b0010K trav->next = (nil)K trav->random = (nil)K
   [test] L=141 :Sort LinkedList!
   [copyRandomList] L=64 :nn = 0x7b0540K
   [printList] L=125 :val = 1   trav = 0x7b04c0K trav->next = 0x7b04e0K trav->random = (nil)K
   [printList] L=125 :val = 2   trav = 0x7b04e0K trav->next = 0x7b0500K trav->random = 0x7b04c0K
   [printList] L=125 :val = 3   trav = 0x7b0500K trav->next = 0x7b0520K trav->random = 0x7b04e0K
   [printList] L=125 :val = 4   trav = 0x7b0520K trav->next = 0x7b0540K trav->random = 0x7b0500K
   [printList] L=125 :val = 5   trav = 0x7b0540K trav->next = (nil)K trav->random = (nil)K
**/
