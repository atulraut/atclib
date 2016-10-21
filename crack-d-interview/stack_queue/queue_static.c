#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 2

typedef struct _q {
  int rear;
  int front;
  int *buf;
} queue;

queue *m_init (void *_ptr, int size);
int m_insert (void *_ptr, int val);
int m_remove (void *_ptr);
int m_display (void *_ptr);

int main () {
  int i, j;
  j = 0;
  queue q, *qptr;
  qptr  = m_init(&q, MAX);
  if (NULL == qptr)
    return -1;
  printf ("[q_main] rear=%d, front=%d\n", qptr->rear, qptr->front);
  for (i=0; i<MAX; i++) {
    j = i + 1;
    m_insert(qptr, j);
  }
  m_display(qptr);
  j =  m_remove(qptr);
  printf ("[m_main] remove val = %d \n", j);
  m_display(qptr);
  j =  m_remove(qptr);
  printf ("[m_main] remove val = %d \n", j);
  m_display(qptr);
  m_insert(qptr, j);
  m_display(qptr);
}

queue *m_init (void *_ptr, int size) {
  queue *q = (queue *)_ptr;
  memset((void *)q, 0, sizeof(queue));
  q->rear = -1;
  q->front= -1;
  q->buf = (int *) malloc (size * sizeof(int));
  if (NULL == q->buf)
    return;
  else
    return q;
}

int m_insert (void *_ptr, int val) {
  queue *q = (queue *)_ptr;
  if (q->rear == MAX-1) {
    printf ("[m_insert] Quque is FULL \n");
    return -1;
  }
  if (q->front == -1 && q->rear == -1) {
    q->front = q->rear = 0;
  } else {
    q->rear = q->rear + 1; 
  }
  printf ("[m_insert] val=%d added at q->rear=%d \n", val, q->rear);
  q->buf[q->rear] = val;
}

int m_remove (void *_ptr) {
  int val;
  queue *q = (queue *)_ptr;
  if (q->front == -1 || q->front > q->rear)
    printf ("[m_remove] Empty \n");
  else {
    val = q->buf[q->front];
    printf ("[m_remvoe] val = %d at q->front = %d\n",val, q->front);
    q->front = q->front + 1;
    return val;
  }
}

int m_display (void *_ptr) {
  int i;
  queue *q = (queue *)_ptr;
  printf ("[m_display] q->rear = %d  q->front =%d\n", q->rear, q->front);
  if (q->front == -1 || q->front > q->rear) {
    printf ("[m_remove] Empty \n");
    return;
  }
  for (i=q->front; i<q->rear+1; i++) {
    printf ("[m_display] q->buf[%d] = %d \n",i, q->buf[i]);
  }/*
  printf ("q->rear = %d  q->front =%d\n", q->rear, q->front);
  while (q->front != q->rear) {
    printf ("q->buf[%d] = %d \n",q->front, q->buf[q->front]);
    q->front++;
  }
  q->front = 0;
   */
}
