/*
 * Aim : Queue
 * Date : Saturday, Oct 23 2016
 * San Diego, CA
 * By : Atul R. Raut
 * Q->[FIFO] : First In First Out
 * Insert --> Rear++ - Tail++
 * Remove --> Front++ - Head++
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

typedef struct _Q {
  unsigned long Head; /* FRONT */
  unsigned long Tail; /* REAR  */
  unsigned char *pBuf;
  unsigned long DataTypeSz; /* Data Type Size, that we are adding to Ring buffer */
  unsigned long QSize; /* Ring Buffer Size*/
} Queue_Desc;

Queue_Desc *Q_Init(void *_ptr, int QSz, int DatabitSz) {
  Queue_Desc *Q = (Queue_Desc *)_ptr;
  if(NULL == Q) {
	printf ("memset needs valid pointer \n");
	exit(1);
  }
  memset((void *)Q, 0, sizeof(Queue_Desc));
  Q->Head = Q->Tail = -1;
  Q->DataTypeSz = DatabitSz;
  Q->QSize = QSz;
  if(NULL == (Q->pBuf = (unsigned char *)calloc(Q->QSize, Q->DataTypeSz) ))
    return;
  else {
    printf ("Q = %p pBuf = %p \n", Q, Q->pBuf);
    return Q;
  }
}

int Q_Insert(void *_ptr, unsigned char *pNew) {
  Queue_Desc *Q = (Queue_Desc *)_ptr;

  if (Q->Tail == (Q->Head + Q->QSize) && Q->Head == 0) { // Reset Q Tail H| | |T|
    printf ("[m_Insert] Reset Q =0 ");
    Q->Tail = 0;
  } else if (Q->Tail == -1 && Q->Head == -1) { // Reset Q HT| | | | 
    Q->Tail = Q->Head = 0;
  } else if (Q->Tail == (Q->Head + Q->QSize) && Q->Head != 0) { // | |H|T|
    Q->Tail = 0;
  } else {
    Q->Tail += 1;
  }
  printf ("[insert]p=%d [%lu]->[%d]\n", *pNew, Q->Tail, Q->pBuf[Q->Tail*Q->DataTypeSz]);
  memcpy (Q->pBuf + (Q->Tail * Q->DataTypeSz), pNew, Q->DataTypeSz);
  return QUEUE_OK;
}

int Q_Remove(void *_ptr, unsigned char *pOld) {
  Queue_Desc *Q = (Queue_Desc *)_ptr;
  if (Q->Head == -1) {       // Return H| | | |
    return QUEUE_EMPTY;
  }
  memcpy(pOld, Q->pBuf + (Q->Head * Q->DataTypeSz), Q->DataTypeSz);
  printf ("[remove]p=%d [%lu]->[%d]\n", *pOld, Q->Head, Q->pBuf[Q->Tail*Q->DataTypeSz]);
  if (Q->Head == Q->Tail) {   // | | | |HT
    Q->Head = Q->Tail = -1;
  } else if (Q->Head == (Q->QSize)) {  // | | | |H
    Q->Head = 0;
  } else
      Q->Head += 1;
  return pOld;
  return QUEUE_OK;
}

void Q_Display (void *_ptr) {
  int i;
  Queue_Desc *Q = (Queue_Desc *)_ptr;
  printf ("[m_display] q->front=%lu q->rear=%lu\n", Q->Head, Q->Tail);
  for (i=Q->Head; i<Q->Tail+1; i++) {
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
  int i, data;
  Queue_Desc q, *qptr;
  qptr = Q_Init (&q, MAX, sizeof(int));
  if(qptr == NULL)
    return;
  for (i = 0; i < MAX+1; i++) {
      data = i * i;
      if(QUEUE_FULL == Q_Insert(qptr, (unsigned char *)&data)) {
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
