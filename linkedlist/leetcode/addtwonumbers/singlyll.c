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

struct list *list1 = NULL;
struct list *list2 = NULL;
struct list *l_base = NULL;

static int get_input(char *cmd) {
  int res = 1;

  printf ("Enter number! \n");

  while(fgets (cmd, 20, stdin) && cmd[0] != '\n') {
    res = atoi(cmd);
    //    printf ("atoi=%d, cmd=%s \n", res, cmd);
  }
  return res;
}

struct list* getLLType() {
  int llType = 0;
  int cmd;

  printf ("Select Linked List Type ? 1 : 2 \n");
  scanf ("%d", &cmd);
  llType = cmd;
  printf ("llType = %d, cmd = %d \n", llType, cmd);
  if (llType == 1)
    l_base = list1;
  if (llType == 2)
    l_base = list2;
  printf ("Selected Linked List Type l=%p L1=%p L2=%p\n", l_base, list1, list2);
  return l_base;
}

struct list* m_Init (struct list *ll){
  struct list *list = NULL;
  memset((void *)ll, 0, sizeof(struct list));
  list = (struct list *)malloc (sizeof (struct list));
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

  /* Set Linked List Type ? 1 : 2 */
  list = getLLType();
  printf ("Selected Linked List Type l=%p L1=%p L2=%p\n", l_base, list1, list2);

  data = get_input(cmd);
  nn = m_CreateNodeL (data);
  nn->data = data;
  if (NULL == l_base->head) {
    l_base->head = (struct list_node *)nn;
    nn->next = NULL;
  } else {
    struct list_node *trav;
    trav = (struct list_node *)l_base->head;
    nn->next = trav;
    l_base->head = (struct list_node *)nn;
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
  struct list *ll = (struct list *)ptr;
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
  https://leetcode.com/problems/add-two-numbers/
***/
//struct list* addTwoNumbers(struct list* l1, struct list* l2) {
void addTwoNumbers(void *ptr) {
  struct list *temp;
  struct list_node *temp_nn;
  struct list_node *trav1;
  struct list_node *trav2;
  int remainder = 0, sum;

  /* Set Linked List Type ? 1 : 2 */
  getLLType();

  trav1 = (struct list_node *)list1->head;
  trav2 = (struct list_node *)list2->head;

  temp_nn->data = 0;
  temp_nn->next = NULL;
  struct list_node* curr = temp_nn;

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

void m_Display(void *ptr){
  struct list *list = (struct list *)ptr;

  /* Set Linked List Type ? 1 : 2 */
  getLLType();

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
