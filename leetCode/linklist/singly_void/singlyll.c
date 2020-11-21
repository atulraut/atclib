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

  while(fgets (cmd, 20, stdin) && cmd[0] != '\n') {
    res = atoi(cmd);
    //    printf ("atoi=%d, cmd=%s \n", res, cmd);
  }
  return res;
}

struct list* m_Init (struct list *ll){
  struct list *list = NULL;
  memset((void *)ll, 0, sizeof(struct list));
  list = malloc (sizeof (struct list));
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

void m_RevlistKthNode(void *ptr) {
  struct list *ll = ptr;
  struct list_node *head = (struct list_node *)ll->head;
  struct list_node *trav;
  struct list_node *temp = head;
  struct list_node *start= head;
  head = NULL;
  int cnt = 0;
  char cmd[20] = {0};
  int k = 0;

  k = get_input(cmd);

  if(k<1) {
    printf ("Cant reverse the list! \n");
    return;
  }
  if(k==1)  /* if just 2 element in list we need this condition. */
    k=2;
  while (temp != NULL && cnt < k) {
    trav = temp->next;
    temp->next = head;
    head = temp;
    ll->head = (struct list_node *)head;
    temp = trav;
    cnt++;
  }
  start->next = trav;
  printf ("Reverse the kth Node! k = %d cnt =%d \n", k, cnt);
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

void m_ReturnNthNode_From_End(void *ptr) {
  struct list *ll = (struct list *)ptr;
  struct list_node *p1 = NULL;
  struct list_node *p2 = NULL;
  char cmd[20] = {0};
  int NthNode = 0;

  NthNode = get_input(cmd);

  p1 = p2 = (struct list_node *)ll->head;

  if (ll->head == NULL || NthNode < 1) {
      return;
  }
  for (int j = 0; j<(NthNode-1); ++j) { // skip n-1 steps ahead
      if (p2 == NULL) {
	return;// not found since list size < n
      }
      p2 = p2->next;
  }

  while (p2->next != NULL) {
      p1 = p1->next;
      p2 = p2->next;
  }
  printf ("\nval--> %d\n", p1->data);
}

/* Middle Most Node of a Linked List */
void m_RemoveDuplicateNodes(void *ptr) {
  struct list*ll = (struct list *)ptr;
  struct list_node *prev = NULL;
  struct list_node *current = NULL;

  prev = (struct list_node *)ll->head;
  current = prev->next;
  while (current != NULL) {
    struct list_node *runner = (struct list_node *)ll->head;
    while (runner != current) {
      if(runner->data == current->data) {
	struct list_node *temp = current->next; // remove current
	prev->next = temp;
	current = temp; // update current to next node
	break; // all other dups have removed
      }
      runner = runner->next;
    }
    if (runner == current) { // current not update, update now
      prev = current;
      current = current->next;
    }
  }
}

/* Our search should be able to tell us that 52 is
 *  in the list. On the other hand, if we searched for 25, our search
 *  should report that 25 is not in the list.
 */
void m_SearchData(void *ptr) {
  struct list *ll = (struct list *)ptr;
  struct list_node *current = (struct list_node *)ll->head;
  char cmd[20] = {0};
  int key = 0;

  key = get_input(cmd);
  while (current != NULL && current->data != key) {
    printf ("Found Key = %d \n",current->data);
  }
  printf ("Key Not Found! \n");
}

/*
 * LeetCode : https://leetcode.com/explore/challenge/card/november-leetcoding-challenge/564/week-1-november-1st-november-7th/3516/
 *  Convert Binary Number in a Linked List to Integer
 * Given head which is a reference node to a singly-linked list. The value of each node in the linked list is either 0 or 1.
 * The linked list holds the binary representation of a number.
 * Return the decimal value of the number in the linked list.

 Example 1:
 Input: head = [1,0,1]
 Output: 5
 Explanation: (101) in base 2 = (5) in base 10

 Example 2:
 Input: head = [0]
 Output: 0

 Example 3:
 Input: head = [1]
 Output: 1

 Example 4:
 Input: head = [1,0,0,1,0,0,1,1,1,0,0,0,0,0,0]
 Output: 18880

 Example 5:
 Input: head = [0,0]
 Output: 0

 Constraints:
 The Linked List is not empty.
 Number of nodes will not exceed 30.
 Each node's value is either 0 or 1.
***/
void getDecimalValue(void *ptr) {
  int i = 0, op = 0;
  struct list_node* trav = NULL;
  struct list *ll = (struct list *)ptr;

  struct list_node *head = (struct list_node *)ll->head;
  struct list_node *temp = (struct list_node*)ll->head;

  if (NULL == ll->head) {
    printf ("Empty link list \n");
    return;
  } else {
    /* Reverse the link list */
    head = NULL;
    while (temp != NULL) {
      trav = temp->next;
      temp->next = head;
      head = temp;
      ll->head = (struct list_node *)head;
      temp = trav;
    }

    temp = head;
    while (temp != NULL) {
      printf ("[%s] data-> %d op = %d \n",__func__, temp->data, (temp->data << i));
      op += temp->data << i++;// multiply by 2 power of i, which converts binary to decimal
      printf ("[%s] data-> %d op = %d \n",__func__, temp->data, op);
      temp = temp->next;
    }
  }
}

void m_Display(void *ptr){
  struct list *ll = (struct list *)ptr;
  printf ("\n----------:: Output ::-----------\n");
  struct list_node *temp = NULL;
  temp = (struct list_node*)ll->head;
  if (NULL == ll->head) {
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
