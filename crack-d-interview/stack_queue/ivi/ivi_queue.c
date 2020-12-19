/*
	Quick way to implement Circular Queue
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Q --> IR++ RF++
 Insert --> Rear++, Tail
 Remove --> Front++ Head

 * Insert --> if (read == MAX-1) --> Overflow
 * Remove --> if (front > rear)  --> Underflow
 */

#define Q_SIZE 5

struct q_Desc {
  int sz;
  int cnt;
  int *buf;
};

struct q_Desc* m_Init (void *_ptr, int size) {
  struct q_Desc *q = (struct q_Desc*)_ptr;

  memset((void *)q, 0, sizeof(struct q_Desc));

  if(NULL == (q->buf = (int *)calloc(size, sizeof(int))))
  if (NULL == q->buf)
    return NULL;

  q->cnt = -1;
  q->sz = size;

  return q;
}

int m_IsFull(void *_ptr) {
  struct q_Desc *q = (struct q_Desc*)_ptr;
  if (q->cnt == q->sz)
    return 1;
  else
    return -1;
}

int m_IsEmpty(void *_ptr) {
  struct q_Desc *q = (struct q_Desc*)_ptr;
  if (q->cnt <= 0)
    return 1;
  else
    return -1;
}

void m_Insert(void *_ptr, int val) {
  struct q_Desc *q = (struct q_Desc*)_ptr;
  if (q->cnt == q->sz-1)
    q->cnt = 0;
  else if (q->cnt == -1)
    q->cnt++;
  else
    q->cnt++;
  printf ("[%s] cnt=%d val=%d \n", __func__, q->cnt, val);
  q->buf[q->cnt] = val;
}

int m_Remove(void *_ptr) {
  int val = 0;
  struct q_Desc *q = (struct q_Desc*)_ptr;
  if (m_IsEmpty(q))
    return 1;
  val = q->buf[q->cnt];
  q->cnt--;
  return val;
}

int m_Display(void *_ptr) {
  struct q_Desc *q = (struct q_Desc*)_ptr;
  int i;
  if (m_IsEmpty(q))
    return 1;
  for (i=0; i <= q->cnt; i++)
    printf ("[%s] i=%d \n", __func__, q->buf[i]);
}

int main () {
  int i = 0, j = 0;
  struct q_Desc qe, *qptr;
  qptr = m_Init(&qe, Q_SIZE);

  /* Insert Elements */
  for (i=0; i < Q_SIZE; i++) {
    m_Insert(qptr, i+1);
  }
  m_Display(qptr);
  /* Overflow Test */
  m_Insert(qptr, i+0);
  m_Insert(qptr, i+1);

  /* Remove Elements */
  for (i=0; i <qptr->cnt; i++) {
    m_Remove(qptr);
  }
  m_Display(qptr);

  m_Insert(qptr, i+2);
  m_Insert(qptr, i+3);
  m_Insert(qptr, i+4);
  m_Insert(qptr, i+5);
  m_Insert(qptr, i+6);
  m_Display(qptr);

  return 0;
}
