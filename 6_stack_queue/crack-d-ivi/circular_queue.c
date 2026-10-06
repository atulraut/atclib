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
 Date : Sun Sep 10 03:07:04 PM PDT 2023
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
  int head; // front - Remove
  int tail;  // rear - Insert
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
  q->head = -1;
  q->tail  = -1;
  q->qsize = sz;

  if(NULL == (q->buf = (int *)calloc(sz, sizeof(int))))
    return NULL;
  else
    return q;
}

bool is_Empty(void *_ptr) {
  struct queue *q = (struct queue *)_ptr;
  return (q->head == -1);

  if (q->head == -1) {
    debug ("[m_remove] Empty");
    return true;
  } else
    return false;
}

bool is_Full(void *_ptr) {
  struct queue *q = (struct queue *)_ptr;
  //  debug ("((q->tail + 1) % q->qsize)=%d q->head=%d ", ((q->tail + 1) % q->qsize), q->head);
  return ((q->tail + 1) % q->qsize) == q->head;

  if (q->tail == q->qsize-1)
    return true;
  else
    return false;
}

/** Get the head item from the queue. */
int Head(void *_ptr) {
  struct queue *thisQ = (struct queue *)_ptr;
  if (is_Empty(thisQ)) {
    return -1;
  }
  return thisQ->buf[thisQ->head];
}

/** Get the last item from the queue. */
int Tail(void *_ptr) {
  struct queue *thisQ = (struct queue *)_ptr;
  if (is_Empty(thisQ)) {
    return -1;
  }
  return thisQ->buf[thisQ->tail];
}

int m_enqueue (void *_ptr, int data) {
  struct queue *q = (struct queue *)_ptr;
  //debug (" is_Full(q) = %d", is_Full(q));
  if (is_Full(q) && q->head == 0) {
    debug ("Q is Full, Reseting q->tail=%d q->head=%d Q=%d", q->tail, q->head, data);
    q->tail = 0;
  } else if (q->tail == -1 || q->head == -1) {
    q->tail = q->head = 0;
  } else if (q->tail == q->qsize-1 && q->head != 0) {
    q->tail = 0;
  } else {
    q->tail = q->tail+1;
  }
  debug ("tail=%d, head=%d data=%d", q->tail, q->head, data);
  q->buf[q->tail] = data;
}

int m_dequeue (void *_ptr) {
  int val;
  struct queue *q = (struct queue *)_ptr;
  if (is_Empty(q)) {
    debug ("[m_remove] Queue is Empty\n");
    val = -1;
    return val;
  }
  val = q->buf[q->head];
  if (q->head == q->tail ) {
    q->head = q->tail = -1;
  } else if (q->head == q->qsize-1 ) {
    q->head = 0;
  }
  else
    q->head = q->head+1;
  debug ("DeQueue = %d", val);
  return val;
}

void m_display (void *_ptr) {
  int i;
  struct queue *q = (struct queue *)_ptr;
  printf ("[m_display] Inside q->head=%d q->tail=%d\n", q->head, q->tail);
  for (i=q->head; i<=q->tail; i++) {
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

/**
   >> ./a.out
   [m_enqueue] L=116 :tail=0, head=0 data=5
   [m_enqueue] L=116 :tail=1, head=0 data=10
   [m_enqueue] L=116 :tail=2, head=0 data=15
   [m_enqueue] L=116 :tail=3, head=0 data=20
   [m_enqueue] L=116 :tail=4, head=0 data=25
   [m_dequeue] L=136 :DeQueue = 5
   [m_enqueue] L=116 :tail=0, head=1 data=30
   [m_dequeue] L=136 :DeQueue = 10
   [test] L=166 :->[10]
   [m_dequeue] L=136 :DeQueue = 15
   [test] L=166 :->[15]
   [m_dequeue] L=136 :DeQueue = 20
   [test] L=166 :->[20]
   [m_dequeue] L=136 :DeQueue = 25
   [test] L=166 :->[25]
   [m_dequeue] L=136 :DeQueue = 30
   [test] L=166 :->[30]
*/
