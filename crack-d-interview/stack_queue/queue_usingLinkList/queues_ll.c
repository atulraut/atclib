/*
* Advanced_Topics_In_C.pdf
*/
#include <stdio.h>

struct qdata {
  int num;
};

struct qnode {
  struct qdata data;
  struct qnode *next;
};

struct qtype {
  struct qnode *head;
  struct qnode *tail;
};

struct qtype* m_init_Q(void *_ptr) {
  struct qtype *q = (struct qtype*)_ptr;
  memset((void *)q, 0, sizeof(struct qtype));
  q = (struct qtype *)malloc(sizeof(struct qtype));
  if(NULL == q)
    return;
  q->head = NULL;
  q->tail = NULL;
  return q;
}

int empty (void *_ptr) {
  struct qtype *q =(struct qtype *)_ptr;
  if(q->head == NULL)
    return 1;
  else
    return 0;
}

int enque(void *_ptr, struct qdata temp) {
  struct qtype *qtype = (struct qtype *)_ptr;
  struct qnode *qnodePtr = (struct qnode *)malloc(sizeof(struct qnode));
  qnodePtr->data = temp;
  qnodePtr->next = NULL;
  if(empty(qtype)) {
    qtype->head = qnodePtr;
    qtype->tail = qnodePtr;
  } else {
    qtype->tail->next = qnodePtr;
    qtype->tail = qnodePtr;
  }
  printf("End of enque! \n");
}

struct qdata deque (void *_ptr) {
  struct qtype *qtype = (struct qtype *)_ptr;
  
  if(empty(qtype)) {
    printf("Attempt to remove from emptry queue! \n");
    return;
  }
  struct qdata hold = qtype->head->data;
  struct qnode *qnodePtr = qtype->head;
  qtype->head = qtype->head->next;
  qnodePtr->next = NULL;
  if(qtype->head == NULL)
    qtype->tail = NULL;
  free(qnodePtr);
  return hold;
} 

int main () {
  int n;
  struct qtype *qptr, q;
  struct qdata temp;
  qptr = m_init_Q(&q);
  if(NULL == qptr)
    return -1;
  printf ("Enter positive integer! \n");
  scanf("%d", &n);
 
  while (n>0) {
    temp.num = n%10;
    enque(qptr, temp);
    n = n/10;
  }
  printf ("Printing Queues in reverse order! \n");
  while(!empty(qptr)) {
    temp = deque(qptr);
    printf(":::->[%d]", temp.num);
  }
  printf ("\n");
  return 0;
}
