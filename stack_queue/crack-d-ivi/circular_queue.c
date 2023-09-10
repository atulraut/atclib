/*
 * Aim : Simple Queue
 * Date : Friday, Oct 21 2016
 * San Diego, CA
 * By : Atul R. Raut
 * Q->[FIFO] : First In First Out
 * Q --> IR++ RF++ {Insert --> Rear++, Remove --> Front++}
 * Insert --> if (rear == MAX-1) --> Overflow
 * Remove --> if (front > rear)  --> Underflow
 * Diagram Ref: http://www.studytonight.com/data-structures/queue-data-structure
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */
//#define qsize 5
/*----------------------------------- Micro --------------------------------------*/
#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)
#define atsizeof(object) (char *)(&object+1) - (char*)(&object)
#define arrsz(x)  (sizeof(x) / sizeof((x)[0]))
#define max(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a > _b ? _a : _b; })
#define min(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

struct queue {
  int front; // head - Remove
  int rear;  // tail - Insert
  int *buf;
  int qsize;
};

struct queue *m_init (void *_ptr, int sz) {
  struct queue *q = (struct queue *)_ptr;
  if(NULL == q) {
    printf ("memset needs valid pointer \n");
    exit(1);
  }
  memset ((void *)q, 0, sizeof(struct queue));
  q->front = -1;
  q->rear  = -1;
  q->qsize = sz;

  if(NULL == (q->buf = (int *)calloc(sz, sizeof(int))))
    return NULL;
  else
    return q;
}

bool is_Empty(void *_ptr) {
  struct queue *q = (struct queue *)_ptr;
  return (q->front == -1);

  if (q->front == -1) {
    debug ("[m_remove] Empty");
    return true;
  } else
    return false;
}

bool is_Full(void *_ptr) {
  struct queue *q = (struct queue *)_ptr;
  //  debug ("((q->rear + 1) % q->qsize)=%d q->front=%d ", ((q->rear + 1) % q->qsize), q->front);
  return ((q->rear + 1) % q->qsize) == q->front;

  if (q->rear == q->qsize-1)
    return true;
  else
    return false;
}

/** Get the front item from the queue. */
int Front(void *_ptr) {
  struct queue *thisQ = (struct queue *)_ptr;
  if (is_Empty(thisQ)) {
    return -1;
  }
  return thisQ->buf[thisQ->front];
}

/** Get the last item from the queue. */
int Rear(void *_ptr) {
  struct queue *thisQ = (struct queue *)_ptr;
  if (is_Empty(thisQ)) {
    return -1;
  }
  return thisQ->buf[thisQ->rear];
}

int m_enqueue (void *_ptr, int data) {
  struct queue *q = (struct queue *)_ptr;
  //debug (" is_Full(q) = %d", is_Full(q));
  if (is_Full(q) && q->front == 0) {
    debug ("Q is Full, Reseting q->rear=%d q->front=%d Q=%d", q->rear, q->front, data);
    q->rear = 0;
  } else if (q->rear == -1 || q->front == -1) {
    q->rear = q->front = 0;
  } else if (q->rear == q->qsize-1 && q->front != 0) {
    q->rear = 0;
  } else {
    q->rear = q->rear+1;
  }
  debug ("rear=%d, front=%d data=%d", q->rear, q->front, data);
  q->buf[q->rear] = data;
}

int m_dequeue (void *_ptr) {
  int val;
  struct queue *q = (struct queue *)_ptr;
  if (is_Empty(q)) {
    debug ("[m_remove] Queue is Empty\n");
    val = -1;
    return val;
  }
  val = q->buf[q->front];
  if (q->front == q->rear ) {
    q->front = q->rear = -1;
  } else if (q->front == q->qsize-1 ) {
    q->front = 0;
  }
  else
    q->front = q->front+1;
  debug ("DeQueue = %d", val);
  return val;
}

void m_display (void *_ptr) {
  int i;
  struct queue *q = (struct queue *)_ptr;
  printf ("[m_display] Inside q->front=%d q->rear=%d\n", q->front, q->rear);
  for (i=q->front; i<=q->rear; i++) {
    printf ("[m_display] = [%d]\n", q->buf[i]);
  }
}

void test () {
  int i, j;
  j = 0;
  int size = 5;
  struct queue q, *qptr;
  qptr = m_init(&q, size);
  if (NULL == qptr)
    return;

  // EnQueue Ops
  for (i=1; i<=size; i++)
    m_enqueue(qptr, (i*5));

  m_dequeue(qptr);
  m_enqueue(qptr, (6*5));
  // DeQueue Ops
  for (i=1; i<=size; i++)
    debug ("->[%d]", m_dequeue(qptr));

}

int main () {
  test ();
}
