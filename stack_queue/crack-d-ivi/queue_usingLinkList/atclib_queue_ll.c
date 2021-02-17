/*
* atclib Implementation of Queue LinkList.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct qnode {
  int data;
  struct qnode *next;
};

struct queue {
  struct qnode *head;
  struct qnode *tail;
};

struct queue* m_init_Q(void *_ptr) {
  struct queue *thisQ = (struct queue *)(_ptr);
  if (NULL == _ptr)
    return NULL;
  memset((void *)thisQ, 0, sizeof(struct queue));
  if(NULL == (thisQ = (struct queue*)malloc(sizeof(struct queue)))) {
    return NULL;
  } else {
   thisQ->head = NULL;
   thisQ->tail = NULL;
   return thisQ;
  }
}

int empty (void *_ptr) {
  struct queue *thisQ = (struct queue *)(_ptr);
  if(thisQ->head == NULL)
    return 1;
  else
    return 0;
}

void enque(void *_ptr, int val) {
  struct queue *thisQ = (struct queue *)(_ptr);
  
  struct qnode *nn = (struct qnode *)malloc(sizeof(struct qnode));
  if(nn == NULL)
    return;
  nn->data = val;
  
  if(empty(thisQ)) {
    nn->next = thisQ->tail;
    thisQ->tail = nn;
    thisQ->head = nn;
  } else {
    thisQ->tail->next = nn;
    thisQ->tail = nn;
  }
}

void deque(void *_ptr) {
  int data;
  struct queue *thisQ = (struct queue *)(_ptr);
  struct qnode *temp = NULL;
  
  if(thisQ->head == NULL) {
    printf ("Queue is NULL, returning!");
    return;
  } else {
    temp = (struct qnode*)thisQ->head;
    data = temp->data;
    printf("::-->[%d]", data);    
    thisQ->head = thisQ->head->next;
    if(thisQ->head == NULL)
      thisQ->tail = NULL;
    free(temp);
    temp = NULL;
  }
}

int main () {
  int n;
  struct queue *qptr, q;
  struct qnode temp;
  qptr = m_init_Q(&q);
  if(NULL == qptr)
    return -1;
  printf ("Enter positive integer! \n");
  scanf("%d", &n);
 
  while (n>0) {
    temp.data = n%10;
    enque(qptr, temp.data);
    n = n/10;
  }
  printf ("Printing Queues in reverse order! \n");
  while(!empty(qptr)) {
      deque(qptr);
      //printf(":::->[%d]", temp.data);
  }
  printf ("\n");
  return 0;
}
