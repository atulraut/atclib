/*
 * Aim : Queue
 * Date : Saturday, Oct 22 2016
 * San Diego, CA
 * By : Atul R. Raut
 * Q->[FIFO] : First In First Out
 * rear -> front = -1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 3
/* Queue structure */
#define QUEUE_FULL 1
#define QUEUE_EMPTY -1
#define QUEUE_OK 0

struct _Q {
  unsigned long Head; /* FRONT */
  unsigned long Tail; /* REAR  */
  unsigned char *pBuf;
  unsigned long DataTypeSz;
  unsigned long QSize;
};

typedef struct _Q Queue_Desc;

Queue_Desc *Q_Init(void *_ptr, int QSz, int bitSize) {
  Queue_Desc *Q = (Queue_Desc *)_ptr;
  if(NULL == Q) {
	printf ("memset needs valid pointer \n");
	exit(1);
  }

  memset((void *)Q, 0, sizeof(Queue_Desc));
  Q->Head = Q->Tail = 0;
  Q->DataTypeSz = bitSize;
  Q->QSize = QSz;
  if(NULL == (Q->pBuf = (unsigned char *)calloc(Q->QSize, Q->DataTypeSz)))
    return;
  else {
    printf ("Q = %p pBuf = %p \n", Q, Q->pBuf);
    return Q;
  }
}

int Q_Insert(void *_ptr, unsigned char *pNew) {
  Queue_Desc *Q = (Queue_Desc *)_ptr;
  memcpy (Q->pBuf + (Q->Tail * Q->DataTypeSz), pNew, Q->DataTypeSz);
  if (Q->Tail == (Q->Head + Q->QSize) ) {
    return QUEUE_FULL;
    Q->Tail += 1;
  }
  printf ("[insert]p=%d [%lu]->[%d]\n", *pNew, Q->Tail, Q->pBuf[Q->Tail*Q->DataTypeSz]);                   Q->Tail += 1;
  return QUEUE_OK;
}

int Q_Remove(void *_ptr, unsigned char *pOld) {
  Queue_Desc *Q = (Queue_Desc *)_ptr;
  memcpy(pOld, Q->pBuf + (Q->Head * Q->DataTypeSz), Q->DataTypeSz);
  if (Q->Head == Q->Tail)
    return QUEUE_EMPTY;
  printf ("[remove]p=%d [%lu]->[%d]\n", *pOld, Q->Head, Q->pBuf[Q->Tail*Q->DataTypeSz]);
  Q->Head += 1;
  return QUEUE_OK;
}

void Q_Display (void *_ptr) {
  int i;
  Queue_Desc *Q = (Queue_Desc *)_ptr;
  printf ("[m_display] q->front=%lu q->rear=%lu\n", Q->Head, Q->Tail);
  for (i=Q->Head; i<Q->Tail; i++) {
    printf ("[m_display] = [%d]\n", Q->pBuf[i*Q->DataTypeSz]);
  }
}

void Q_Free (void *_ptr) {
  Queue_Desc *Q = (Queue_Desc *)_ptr;
  printf ("[Free] Q= %p pBuf = %p \n", Q, Q->pBuf);
  if(Q->pBuf)
    free((unsigned char *)Q->pBuf);
}

int main () {
  int i;
  Queue_Desc q, *qptr;
  qptr = Q_Init (&q, MAX, sizeof(int));
  if(qptr == NULL)
    return;
  for (i = 0; i < MAX+1; i++) {
      int dummy = i * i;
      if(QUEUE_FULL == Q_Insert(qptr, (unsigned char *)&dummy)) {
	printf("[m_main] Crap. Queue became full at %i.\n", i);
	break;
      }
  }
  Q_Display (qptr);
  for (i = 0; i < MAX+1; i++) {
    int dummy = i * i;
    if(QUEUE_EMPTY == Q_Remove(qptr, (unsigned char *)&dummy)) {
      printf("[m_main] Crap. Queue became Empty at %i.\n", i);
      break;
    }
  }
  Q_Display (qptr);
  Q_Free (qptr);
}
