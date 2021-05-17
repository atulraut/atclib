/*
 * Aim : Queue for FB
 * Date : Friday, May 14 2021
 * San Diego, CA
 * By : Atul R. Raut
 * Q->[FIFO] : First In First Out
 * Insert --> Rear++ - Tail++
 * Remove --> Front++ - Head++
 * rear -> front = -1
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

#define MAX 5
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
  unsigned long ElemCnt; /* How Many Element Inserted so far */
} Queue_Desc;

Queue_Desc *Q_Init(void *_ptr, const int QSz, int DatabitSz) {
  Queue_Desc *Q = (Queue_Desc *)_ptr;
  if(NULL == Q) {
	printf ("memset needs valid pointer \n");
	exit(1);
  }
  memset((void *)Q, 0, sizeof(Queue_Desc));
  Q->Head = Q->Tail = -1;
  Q->ElemCnt = 0;
  Q->DataTypeSz = DatabitSz;
  Q->QSize = QSz;
  if(NULL == (Q->pBuf = (unsigned char *)calloc(Q->QSize, Q->DataTypeSz) ))
    return NULL;
  else {
    printf ("Q = %p pBuf = %p \n", Q, Q->pBuf);
    return Q;
  }
}

int is_Empty(void *_ptr) {
  Queue_Desc *q = (Queue_Desc *)_ptr;
  if (q->Head == -1) {
    printf ("[m_remove] Empty \n");
    return 1;
  } else
      return -1;
}

int is_Full(void *_ptr) {
  Queue_Desc *q  = (Queue_Desc *)_ptr;
  if (q->Tail == MAX-1)
    return 1;
  else
    return -1;
}

int Q_Insert(void *_ptr, char *pNew, int datalen) {
  Queue_Desc *Q = (Queue_Desc *)_ptr;
  int i = 0;
  debug("String=%s Head= %ld Tail= %ld datalen= %d ElemCnt=%ld", pNew, Q->Head, Q->Tail, datalen, Q->ElemCnt);

  if (datalen > Q->QSize)
    datalen = Q->QSize;
  else if (datalen > (Q->QSize - Q->ElemCnt)) {
    datalen = (Q->QSize - Q->ElemCnt); // To avoid overwrite Queue.
    debug ("***__Space Left__*** = %ld so accomodate only = %d Element!", (Q->QSize - Q->ElemCnt), datalen);
  }

  while (datalen > 0 && Q->ElemCnt <= Q->QSize) {
    if (Q->Tail == Q->QSize -1 && Q->Head == 0) {
      debug("Queue is FULL, _OverFlow_! ");
    }  else if (Q->Tail == -1 && Q->Head == -1) { // Reset Q HT| | | |
      Q->Tail = Q->Head = 0;
    } else if (Q->Tail == Q->QSize-1 && Q->Head != 0) { // Reach End of Q, hence Reset
      Q->Tail = 0;
    } else {
      Q->Tail += 1;
    }

    datalen -= 1;
    Q->ElemCnt += 1;

    Q->pBuf[Q->Tail] = pNew[i++];

    /* Des, Src, Size */
    //memcpy (Q->pBuf + (Q->Tail * Q->DataTypeSz), pNew, Q->DataTypeSz);

    debug("Org=%c pBuf=%c Q->QSize=%ld datalen=%d Q->Tail=%ld Q->ElemCnt=%ld", pNew[i-1],
	  Q->pBuf[Q->Tail], Q->QSize, datalen, Q->Tail, Q->ElemCnt);
  }
  debug("datalen=%d Q->Tail=%ld Q->ElemCnt=%ld", datalen, Q->Tail, Q->ElemCnt);
  return QUEUE_OK;
}

int Q_Remove(void *_ptr, char *pOld, int datalen) {
  Queue_Desc *Q = (Queue_Desc *)_ptr;
  if (Q->Head == -1) {       // Return H| | | |
    return QUEUE_EMPTY;
  }

  while (datalen > 0 && Q->Head <= Q->QSize -1) {
    char lOld = Q->pBuf[Q->Head * Q->DataTypeSz];
    //memcpy(pOld, Q->pBuf + (Q->Head * Q->DataTypeSz), Q->DataTypeSz);
    debug ("[remove]p=%c Q->Head = %lu Q->Head=[%lu] c->[%c] datalen=%d", lOld, Q->Head,  (Q->Head*Q->DataTypeSz), Q->pBuf[Q->Head*Q->DataTypeSz], datalen);
    debug ("Q->Head = %ld Q->Tail =%ld", Q->Head, Q->Tail);
    Q->pBuf[Q->Head * Q->DataTypeSz] = -1;
    if (Q->Head == Q->Tail) {   // | | | |HT
      Q->Head = Q->Tail = 0;
    } else if (Q->Head == (Q->QSize)) {  // | | | |H
      Q->Head = 0;
      debug("Reached!");
    } else {
      if (Q->Head != Q->QSize-1) // Dont increament if Head reach to End of Queue
	Q->Head += 1;
    }
    datalen -= 1;
    Q->ElemCnt -= 1;
    debug("Q->Head=%ld datalen = %d Q->ElemCnt=%ld", Q->Head, datalen, Q->ElemCnt);
  }
  debug("Q->Head=%ld Q->ElemCnt=%ld", Q->Head, Q->ElemCnt);
  return QUEUE_OK;
}

void Q_Display (void *_ptr) {
  int i;
  Queue_Desc *Q = (Queue_Desc *)_ptr;
  printf ("[m_display] q->front=%lu q->rear=%lu Sz=%lu\n", Q->Head, Q->Tail, Q->QSize);

  for (i=0; i<Q->QSize; i++) {
    printf ("[m_display] = [%c]\n", Q->pBuf[i*Q->DataTypeSz]);
  }
}

void Q_Free (void *_ptr) {
  Queue_Desc *Q = (Queue_Desc *)_ptr;
  printf ("[Free] Q= %p pBuf = %p \n", Q, Q->pBuf);
  if(Q->pBuf)
    free((unsigned char *)Q->pBuf);
}

int testQ() {
  int dummy;
  int i, data;
  Queue_Desc q, *qptr;
  qptr = Q_Init (&q, MAX, sizeof(char));
  if(qptr == NULL)
    return 0;

  char *data1 = "AtulRaut";

  debug(" ___ Calling Insertion 1___");
  Q_Insert(qptr, data1, MAX);

  debug(" ___ Calling Display 2___");
  Q_Display (qptr);

  debug(" ___ Calling Remove 3___");
  if(QUEUE_EMPTY == Q_Remove((void *)qptr, (char *)&dummy, 3))
    printf("[m_main] Crap. Queue became Empty at %i.\n", i);

  debug(" ___ Calling Display 4___");
  Q_Display (qptr);

  debug(" ___ Calling Insertion 5___");
  Q_Insert(qptr, "VEDA", 4);

  debug(" ___ Calling Display 6___");
  Q_Display (qptr);


  debug(" ___ Calling Remove 7___");
  if(QUEUE_EMPTY == Q_Remove((void *)qptr, (char *)&dummy, 2))
    printf("[m_main] Crap. Queue became Empty at %i.\n", i);

  debug(" ___ Calling Display 8___");
  Q_Display (qptr);

  debug(" ___ Calling Insertion 9___");
  Q_Insert(qptr, "89", 2);

  debug(" ___ Calling Display 10___");
  Q_Display (qptr);
  Q_Free (qptr);
}

int main () {
  testQ();
  return 0;
}
