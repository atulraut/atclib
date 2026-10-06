/***
 * atclib Implementation of Queue LinkList.
 */
#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

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

int is_empty (void *_ptr) {
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

  if(is_empty(thisQ)) {
    nn->next = thisQ->tail;
    thisQ->tail = nn;
    thisQ->head = nn;
  } else {
    thisQ->tail->next = nn;
    thisQ->tail = nn;
  }
}

int deque(void *_ptr) {
  int data;
  struct queue *thisQ = (struct queue *)(_ptr);
  struct qnode *temp = NULL;

  if(thisQ->head == NULL) {
    printf ("Queue is NULL, returning!");
    return;
  } else {
    temp = (struct qnode*)thisQ->head;
    data = temp->data;
    thisQ->head = thisQ->head->next;
    if(thisQ->head == NULL)
      thisQ->tail = NULL;
    free(temp);
    temp = NULL;
  }
  return data;
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
    debug ("enque->[%d]", temp.data);
    enque(qptr, temp.data);
    n = n/10;
    debug ("n = %d", n);
  }
  printf ("Printing Queues in reverse order! \n");
  while(!is_empty(qptr)) {
      int data = deque(qptr);
      printf("->[%d]", data);
  }
  printf ("\n");
  return 0;
}
