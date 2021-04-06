/*
* Aim : Singly Linked List for verifying isPalindrome LinkedList.
* Date : 4/3/21 {Note Date is Palindrome} 
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

/***
    https://leetcode.com/submissions/detail/476178816/
    234. Palindrome Linked List
    Given the head of a singly linked list, return true if it is a palindrome.
    Input: head = [1,2,2,1]
    Output: true

    Input: head = [1,2]
    Output: false

    Approach 3: Reverse Second Half In-place
    Algorithm :
    The only way we can avoid using O(n)O(n)O(n) extra space is by modifying
    the input in-place.
    The strategy we can use is to reverse the second half of the Linked List
    in-place (modifying the Linked List structure), and then comparing it with
    the first half. Afterwards, we should re-reverse the second half and put
    the list back together. While you don't need to restore the list to pass
    the test cases, it is still good programming practice because the function
    could be a part of a bigger program that doesn't want the Linked List broken.

    Algorithm
    Specifically, the steps we need to do are:
    Find the end of the first half.
    Reverse the second half.
    Determine whether or not there is a palindrome.
    Restore the list.
    Return the result.

    To do step 1, we could count the number of nodes, calculate how many nodes
    are in the first half, and then iterate back down the list to find the
    end of the first half. Or, we could do it in a single parse using the two
    runners pointer technique. Either is acceptable, however we'll have a look
    at the two runners pointer technique here.

    Imagine we have 2 runners one fast and one slow, running down the nodes of
    the Linked List. In each second, the fast runner moves down 2 nodes, and the
    slow runner just 1 node. By the time the fast runner gets to the end of the
    list, the slow runner will be half way. By representing the runners as pointers,
    and moving them down the list at the corresponding speeds, we can use this
    trick to find the middle of the list, and then split the list into two halves.

    If there is an odd-number of nodes, then the "middle" node should remain attached
    to the first half.

    Step 2 uses the algorithm that can be found in the solution article for the
    Reverse Linked List problem to reverse the second half of the list.

    Step 3 is fairly straightforward. Remember that we have the first half, which
    might also contain a "middle" node at the end, and the second half, which is
    reversed. We can step down the lists simultaneously ensuring the node values
    are equal. When the node we're up to in the second list is null, we know we're
    done. If there was a middle value attached to the end of the first list, it is
    correctly ignored by the algorithm. The result should be saved, but not returned,
    as we still need to restore the list.

    Step 4 requires using the same function you used for step 2, and then for
    step 5 the saved result should be returned.
*/
//reverse function.
struct list_node* reverse_list(struct list_node* iter) {
  struct list_node* cur = NULL, *prev = NULL, *next = NULL;

  //if have less than two numbers in linked list, then return original pointer.
  if (!iter || !iter->next){
    return iter;
  }

  prev = iter;
  cur = prev->next;
  prev->next = NULL;
  next = cur->next;
  //printf("%d %d %d xx\n",prev->val, cur->val, next->val);
  while(1) {
    cur->next = prev;
    if (!next)
      break;
    prev = cur;
    cur = next;
    next = next->next;
    // printf("%d %d cc\n",prev->val, cur->val);
  }
  return cur;
}

void m_isPalindrome(void *ptr) {
  struct list *ll = (struct list *)ptr;
  struct list_node *head = (struct list_node*)ll->head;
  struct list_node *tmp = head;
  struct list_node *reverse = head;
  int count = 0;
  int i;

  //for calculating length of linked list.
  while(tmp) {
    tmp = tmp->next;
    count++;
  }
  tmp = head;
  debug ("count = %d count/2=%d", count, (count/2));
  //this for loop is used to find middle address of linked list.
  for (i = 0 ; i < count/2 ; i++) {
    tmp = tmp->next;
  }

  reverse = reverse_list(tmp);
  /*tmp = reverse;
    while (tmp){
    printf("%d ffff\n", tmp->val);
    tmp = tmp->next;
    }*/

  while (head && reverse) {
    // printf("%d %dcmp\n", tmp->val, reverse->val);
    if (head->data != reverse->data){
      debug("Result = %d", false);
      return false;
    }
    head = head->next;
    reverse = reverse->next;
  }
  debug("Result = %d", true);
  return true;
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

/**
   ----------:: Output ::-----------
   ->[1]->[2]->[2]->[1]
   ----------:: End ::-----------
   Enter a command
   p
   Calling command: Check SnglyLL Palindrome!
   [m_isPalindrome] L=226 :count = 4 count/2=2
   [m_isPalindrome] L=248 :Result = 1
**/
