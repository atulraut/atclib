/*
 * Aim : Simple Queue
 * Date : Friday, Oct 21 2016
 * San Diego, CA
 * By : Atul R. Raut
 * Q->[FIFO] : First In First Out
  * Q --> IR++ RF++ {Insert --> Rear++, Remove --> Front++}
 * Insert --> if (read == MAX-1) --> Overflow
 * Remove --> if (front > rear)  --> Underflow
 * Diagram Ref: http://www.studytonight.com/data-structures/queue-data-structure
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5

typedef struct _q {
  int front;
  int rear;
  int *buf;
} queue;

queue *m_init (void *_ptr, int sz) {
    queue *q = (queue *)_ptr;
    if(NULL == q) {
	printf ("memset needs valid pointer \n");
	exit(1);
    }
    memset ((void *)q, 0, sizeof(queue));
    q->front = -1;
    q->rear = -1;
    if(NULL == (q->buf = (int *)calloc(sz, sizeof(int))))
      return NULL;
    else
      return q;
}

int is_Empty(void *_ptr) {
  queue *q = (queue *)_ptr;
  if (q->front == -1) {
    printf ("[m_remove] Empty \n");
    return 1;
  } else
      return -1;
}

int is_Full(void *_ptr) {
  queue *q = (queue *)_ptr;
  if (q->rear == MAX-1)
    return 1;
  else
    return -1;
}

int m_insert (void *_ptr, int data) {
  queue *q = (queue *)_ptr;
  if (q->rear == MAX-1 && q->front == 0) {
    printf ("[m_insert] Queue is Full, reset Q\n");
    q->rear = 0;
  } else if (q->rear == -1 || q->front == -1) {
    q->rear = q->front = 0;
  } else if (q->rear == MAX-1 && q->front != 0) {
    q->rear = 0;
  } else {
     q->rear = q->rear+1;
  }
  printf ("[m_insert]11 rear=%d, front=%d\n", q->rear, q->front);
  q->buf[q->rear] = data;
}

int m_remove (void *_ptr) {
  int val;
  queue *q = (queue *)_ptr;
  printf ("[m_remove] Inside \n");
  if (q->front == -1) {
    printf ("[m_remove] Queue is Empty\n");
    val = -1;
    return val;
  }
  val = q->buf[q->front];
  if (q->front == q->rear ) {
    q->front = q->rear = -1;
  } else if (q->front == MAX-1 ) {
    q->front = 0;
  }
  else
    q->front = q->front+1;
  return val;
}

void m_display (void *_ptr) {
  int i;
  queue *q = (queue *)_ptr;
  printf ("[m_display] Inside q->front=%d q->rear=%d\n", q->front, q->rear);
  for (i=q->front; i<=q->rear; i++) {
    printf ("[m_display] = [%d]\n", q->buf[i]);
  }
}

int main () {
  int i, j;
  j = 0;
  queue q, *qptr;
  qptr = m_init(&q, MAX);
  if (NULL == qptr)
    return -1;
  for (i=0; i< MAX; i++) {
    j = i + 1;
    m_insert(qptr, j);
  }
  m_display(qptr);

  printf ("[%s] Test2 QOverflow & Reset Usecase \n", __func__);
  for (i=0; i< MAX; i++) {
    j = i + 4;
    m_insert(qptr, j);
  }
  m_display(qptr);

  j =  m_remove(qptr);
  printf ("[m_main] remove val = %d \n", j);
  m_display(qptr);
  m_remove(qptr); m_remove(qptr); m_remove(qptr); m_remove(qptr); m_remove(qptr);
  printf ("[m_main] remove val = %d \n", j);
  m_display(qptr);
  m_insert(qptr, j);
  m_display(qptr);
}
