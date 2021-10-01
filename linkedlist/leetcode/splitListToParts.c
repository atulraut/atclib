/***
    https://leetcode.com/problems/split-linked-list-in-parts/
    Split Linked List in Parts
    Given the head of a singly linked list and an integer k,
    split the linked list into k consecutive linked list parts.

    The length of each part should be as equal as possible:
    no two parts should have a size differing by more than
    one. This may lead to some parts being null.

    The parts should be in the order of occurrence in the input
    list, and parts occurring earlier should always have a
    size greater than or equal to parts occurring later.
    Return an array of the k parts.

    Input: head = [1,2,3], k = 5
    Output: [[1],[2],[3],[],[]]
    Explanation:
    The first element output[0] has output[0].val = 1,
    output[0].next = null.
    The last element output[4] is null, but its string
    representation as a ListNode is [].

    Input: head = [1,2,3,4,5,6,7,8,9,10], k = 3
    Output: [[1,2,3,4],[5,6,7],[8,9,10]]
    Explanation:
    The input has been split into consecutive parts with
    size difference at most 1, and earlier parts are a larger
    size than the later parts.

    Constraints:

    The number of nodes in the list is in the range [0, 1000].
    0 <= Node.val <= 1000
    1 <= k <= 50
    Date: 20 Sept 2021
    Fair Oaks, CA.
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

/**
 * Definition for singly-linked list.
 */
struct listnode {
  int val;
  struct listnode *next;
};
struct listnode* listhead = NULL;

struct listnode* m_Init (struct listnode *ll){
  struct listnode *listnn = NULL;

  listnn = (struct listnode *)malloc (sizeof (struct listnode));
  if (NULL == listnn)
    return NULL;

  return listnn;
}

static struct listnode* m_CreateNodeL (int data) {
  struct listnode *nn = NULL;
  nn = (struct listnode*)malloc(sizeof (struct listnode *));
  if (nn == NULL)
    return NULL;
  nn->val  = data;
  nn->next = NULL;
  return nn;
}

void m_Addfirst(int sz, int* data) {
  struct listnode *nn = NULL;

  for (int i=0; i<sz; ++i) {
    nn = m_CreateNodeL (data[i]);
    nn->val = data[i];
    if (NULL == listhead) {
      listhead = nn;
      nn->next = NULL;
    } else {
      struct listnode *trav;
      trav = (struct listnode *)listhead;
      while (trav->next != NULL)
	trav = trav->next;
      trav->next = nn;
      nn->next = NULL;
    }
  }
}

void m_Display(struct listnode *listhed) {

  printf ("\n----------:: Output ::-----------\n");
  struct listnode *temp = NULL;
  temp = (struct listnode*)listhed;
  if (NULL == listhead) {
    printf ("Empty link list \n");
    return;
  } else {
    while (temp != NULL) {
      printf ("->[%d]", temp->val);
      temp = temp->next;
    }
  }
  printf ("\n----------:: End ::-----------\n");
  //	m_Middlenode(ptr);
}

struct listnode* create_linkedlist() {
  struct listnode *listhed;
  struct listnode ll;
  int input[] = {1,2,3};
  int sz = sizeof(input)/sizeof(input[0]);

  //listhed = m_Init(&ll);
  m_Addfirst(sz, input);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
struct listnode** splitListToParts(struct listnode* head, int k, int* returnSize) {
  int counter=0;
  struct listnode* ptr;
  struct listnode** ret_array;
  int count_array[k];
  int i, j;
  ptr = head;

  while (ptr!=NULL) {
    counter++;
    ptr = ptr->next;
  }

  ret_array = malloc(k * sizeof(struct listnode*));

  for (i=0; i<k; i++)
    ret_array[i]=NULL;

  *returnSize = k;

  for (i=0; i<k; i++)
    count_array[i]=counter/k;

  for (i=0; i<(counter % k); i++)
    count_array[i]++;

  for (i=0; i<k; i++) {
    ret_array[i] = head;
    ptr=head;

    for (j=1; j<count_array[i]; j++)
      ptr = ptr->next;

    if (ptr != NULL) {
      head=ptr->next;
      ptr->next=NULL;
    }
  }

  return ret_array;
}

int main (int argc, char **argv) {
  int k = 5;
  int returnSize;
  //struct listnode* head;
  create_linkedlist();
  m_Display(listhead);

  struct listnode**ret = splitListToParts(listhead, k, &returnSize);
  for (int i=0; i<returnSize; ++i) {
    struct listnode  *temp = ret[i];
    if (temp != NULL)
      debug("Output:[%d] = %d", i, temp->val);
    else
      debug("Output:[%d] = NULL",i);
  }
  return 0;
}

/**
   ----------:: Output ::-----------
   ->[1]->[2]->[3]
   ----------:: End ::-----------
   [main] L=186 :Output = 1
   [main] L=186 :Output = 2
   [main] L=186 :Output = 3
   [main] L=188 :Output:[3] = NULL
   [main] L=188 :Output:[4] = NULL
**/
