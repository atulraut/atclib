 /*
* Aim : Singly Linked List.
* Date : Monday, July 29 2016
* San Diego, CA
* By : Atul R. Raut
* valgrind -v --leak-check=full --show-reachable=yes ./main
***/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "../../../at_lib.h"

static int get_input(char *cmd) {
  int res = 1;

  printf ("Enter number! \n");

  while(fgets (cmd, 20, stdin) && cmd[0] != '\n') {
    res = atoi(cmd);
    //    printf ("atoi=%d, cmd=%s \n", res, cmd);
  }
  return res;
}

struct list * m_Init (struct list *ll) {
  struct list *list = NULL;
  memset((void *)ll, 0, sizeof(struct list));
  list = malloc (sizeof (struct list));
  list->head = NULL;
  return list;
}

static struct list_node* m_CreateNodeL (int data) {
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

void m_Freelist(void *ptr) {
  struct list *ll = (struct list *)ptr;
  struct list *listptr = (struct list*)head;
  struct list *nextptr;

  for(; listptr != NULL; listptr = nextptr) {
    nextptr = listptr->next;
    free(listptr);
  }
  head = NULL;
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
  debug("start = %p head = %p temp =%p trav = %p", start, head, temp, trav);
  debug("head->next = %p", head->next);
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
  This function uses one slow and one fast
  pointer to get to the middle of the LL.
  The slow pointer is advanced only by one node
  and the fast pointer is advanced by two nodes!
*/
void getTheMiddle(void *ptr) {
  struct list *head = (struct list *)ptr;
  struct list_node *p = (struct list_node *)head;
  struct list_node *q = (struct list_node *)head;

  if(q != NULL) {
    while((q->next) != NULL && (q->next->next) != NULL) {
      p=(p != (struct list_node *)NULL ? p->next : (struct list_node *)NULL);
      q=(q != (struct list_node *)NULL ? q->next : (struct list_node *)NULL);
      q=(q != (struct list_node *)NULL ? q->next : (struct list_node *)NULL);
    }
    debug("The middle element is [%d]",p->data);
  }
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

  debug ("prev = %p curr= %p ", prev, current);

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
    } // Inner While Ends
    if (runner == current) { // current not update, update now
      prev = current;
      current = current->next;
    } // if Ends
  } // 1st while Ends.
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

  for (; current != NULL; current = current->next)
    if (key == current->data) {  // if (strcmp(name, 1 i stp->name) == 0)
      debug ("Found %d ", current->data);
      //return current;
    }
  //debug ("Not Found!");
  //return NULL;
}

/*
  Detect Loop in Linked List
*/
void m_detect_loop (void *ptr) {
  struct list *ll = (struct list *)ptr;
  struct list_node *trav = (struct list_node *)ll->head;
  struct list_node *slow_p = trav;
  struct list_node *fast_p = trav;

  while (slow_p && fast_p && fast_p->next) {
    slow_p = slow_p->next;
    fast_p = fast_p->next->next;
    if (slow_p == fast_p) {
      printf ("Found Loop! \n");
      return;
    }
  }
}

bool hasCycle(struct ListNode *head) {
  if (head == NULL) {
    return false;
  }

  struct ListNode *slow = head;
  struct ListNode *fast = head->next;
  while (slow != fast) {
    if (fast == NULL || fast->next == NULL) {
      return false;
    }
    slow = slow->next;
    fast = fast->next->next;
  }
  return true;
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
	m_Middlenode(ptr);
}

void quit(void *_ptr) {
  printf ("Good Bye! \n");
  exit(0);
}
