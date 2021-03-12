/*
* Aim : Singly Linked List.
* Date : Sunday, May 24 2020
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

void m_Revlist(void *ptr) {
  struct list *ll = ptr;
  struct list_node *head = (struct list_node *)ll->head;
  struct list_node *trav;
  struct list_node *temp = head;
  head = NULL;
  while (temp != NULL) {
    trav = temp->next;
    temp->next = head;
    head = temp;
    ll->head = (struct list_node *)head;
    temp = trav;
  }
}

/*
void m_RevRec(NODE **head_ref) {
  NODE *first;
  NODE *rest;
  printf ("**head_ref->[%p] *head_ref->[%p] \n", **head_ref, *head_ref);
  if (NULL == *head_ref)
    return;
  first = *head_ref;
  rest  = first->next;
  if (NULL == rest)
    return;

  m_RevRec (&rest);
  first->next->next = first;
  first->next = NULL;
  *head_ref = rest;

}
*/

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

/* Given only a pointer to a node to be deleted */
void m_DelNode(void *_list, struct list_node *_node) {
  struct list_node *node_ptr = (struct list_node*)_node;
  struct list_node *temp = node_ptr->next;
  node_ptr->data = temp->data;
  node_ptr->next = temp->next;
  free (temp);
  m_Display(_list);
}

/* Middle Most Node of a Linked List */
void m_Middlenode(void *ptr) {
  struct list *ll = (struct list *)ptr;
  struct list_node *p = NULL;
  struct list_node *q = NULL;
  int flag = 0;
  q = p = (struct list_node *)ll->head;
  /*for every two hops of q, one hop for p*/
  while (q->next != NULL) {
    q = q->next;
    if (flag) {
      p = p->next;
    }
    flag = !flag;
  }
  if (flag) {
    printf("List contains even number of nodes.\n The middle two node's values are: %d  %d\n", p->next->data, p->data);
  } else {
    printf("The middle node of the list is: %d\n", p->data);
  }
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

/*
  https://leetcode.com/problems/add-two-numbers/
***/
//struct list* addTwoNumbers(struct list* l1, struct list* l2) {
void addTwoNumbers(void *ptr) {
  struct list_node *trav1;
  struct list_node *trav2;
  int remainder = 0, sum;

  trav1 = (struct list_node *)list1->head;
  trav2 = (struct list_node *)list2->head;

  struct list_node* curr;

  while (trav1 != NULL || trav2 != NULL || remainder != 0) {
    sum = remainder + (trav1 == 0 ? 0 : trav1->data) + (trav2 == 0 ? 0: trav2->data);
    remainder = sum/10;
    sum %= 10;
    curr->next = (struct list_node*)malloc(sizeof(struct list_node));
    curr->next->next = NULL;
    curr->next->data = sum;
    curr = curr->next;
    trav1 = (trav1 == 0 ? 0 : trav1->next);
    trav2 = (trav2 == 0 ? 0 : trav2->next);
  }
  //return temp_nn->next;
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
void mergeTwoLinkedList (void *ptr) {
  int flag = 1;
  struct list *list3, l3;
  list3 = m_Init(&l3);
  if (NULL == list1 || NULL == list2 || NULL == list3)
    return;

  struct list_node *trav3 = list3->head = list1->head;
  struct list_node *trav1 = (struct list_node *)list1->head;
  trav1 = trav1->next;
  struct list_node *trav2 = (struct list_node *)list2->head;
  //  struct list_node *trav3 = (struct list_node *)list3->head;

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

/* Sort & Merged Linked List /
struct list_node* SortedMergeLL(struct list_node* a, struct list_node* b) {
  struct list_node* result = NULL;

  // Base cases
  if (a == NULL)
     return(b);
  else if (b==NULL)
     return(a);

  // Pick either a or b, and recur
  if (a->data <= b->data) {
     result = a;
     result->next = SortedMerge(a->next, b);
  } else {
     result = b;
     result->next = SortedMerge(a, b->next);
  }
  m_Display(result);
  //  return(result);
}
*/

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

void quit(void *_ptr) {
  printf ("Good Bye! \n");
  exit(0);
}
