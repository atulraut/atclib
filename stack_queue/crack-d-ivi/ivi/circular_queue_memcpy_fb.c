/***
    ॐ
    जय भवानी, जय शिवाजी!

    fb - Implement a non-blocking circular queue of bytes.
    Reads can be of arbitrary length (but should return the
    max available),
    writes can be of arbitrary length (but should return the
    bytes actually written).

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Mon Dec  4 07:12:45 PM PST 2023
    Folsom, CA.
*/

/*----------------------------------- Header --------------------------------------*/
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

#define MAX 8
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

/**
   Print/Return the Element in the head of the queue
*/
int
Q_Peek(void *_ptr) {

  Queue_Desc *Q = (Queue_Desc *)_ptr;
  /* If the queue is empty */
  if (Q->Head == -1) {
    debug("The Queue doesn't have any Elements!");
    return false;
  } else {
    /* Printing the element in the head of the queue */
    debug("Head of queue -> [%d] ", Q->pBuf[Q->Head]);
    return Q->pBuf[Q->Head];
  }
}

bool Q_is_Empty(void *_ptr) {
  Queue_Desc *Q = (Queue_Desc *)_ptr;
  if (Q->Head == -1) {
    printf ("[m_remove] Empty \n");
    return true;
  } else
    return false;
}

/**
   Get the number of items in the queue
*/
int
Q_get_Size(void* _ptr) {

  Queue_Desc *Q  = (Queue_Desc *)_ptr;
  debug ("Enter! Head=%ld Tail=%ld", Q->Head, Q->Tail);
  /* If the queue is empty, return 0 */
  if(Q_is_Empty(Q) == true) {
    debug ("Q is Empty!");
    return 0;
  }
  /* The number of items in the queue is the difference between head and tail */
  debug ("Q size = %d", (Q->Tail - Q->Head + 1));
  return (Q->Tail - Q->Head + 1);
}

int Q_is_Full(void *_ptr) {
  Queue_Desc *Q  = (Queue_Desc *)_ptr;
  if (Q->Tail == Q->QSize -1  && Q->Head == 0)
    return 1;
  else
    return -1;
}

int Enqueue_write(void *_ptr, char *dataPtr, int datalen) {
  Queue_Desc *Q = (Queue_Desc *)_ptr;
  int i = 0;

  if (datalen >= Q->QSize)
    datalen = Q->QSize;
  /*else if (datalen > (Q->QSize - Q->ElemCnt)) {
    datalen = (Q->QSize - Q->ElemCnt); // To avoid overwrite Queue.
    debug ("***__Space Left__*** = %ld so accomodate only = %d Element!", (Q->QSize - Q->ElemCnt), datalen);
    }*/

  while (datalen > 0/* && Q->ElemCnt <= Q->QSize*/) {
    if (Q->Tail == Q->QSize -1 && Q->Head == 0) { // Q_is_Full Condition
      //debug("Queue is FULL, _OverFlow_ RESET! ");
      Q->Tail = 0;
    }  else if (Q->Tail == -1 && Q->Head == -1) { // Reset Q HT| | | |
      Q->Tail = Q->Head = 0;
    } else if (Q->Tail == Q->QSize-1 && Q->Head != 0) { // Reach End of Q, hence Reset
      Q->Tail = 0;
    } else {
      Q->Tail += 1;
    }

    // Q->pBuf[Q->Tail] = dataPtr[i++];

    /* Des, Src, Size */
    memcpy (Q->pBuf + (Q->Tail * Q->DataTypeSz), (dataPtr + i), Q->DataTypeSz);
    i++;

    datalen -= 1;
    Q->ElemCnt += 1;
  }
  debug("[%d] datalen=%d Q->Tail=%ld Q->Head=%ld Q->ElemCnt=%ld", i, datalen, Q->Tail, Q->Head, Q->ElemCnt);

  return i;
  return QUEUE_OK;
}

/**
  Reads can be of arbitrary length (but should return the
  max available),
*/
int
Denqueue_read(void *_ptr, char *pOld, int datalen) {

  Queue_Desc *Q = (Queue_Desc *)_ptr;

  bool Q_is_Empty(void *_ptr) { // Return H| | | |
    return QUEUE_EMPTY;
  }

  debug ("DataLength = %d", datalen);
  if (datalen >= Q->QSize)
    datalen = Q->QSize;

  while (datalen > 0 && Q->Head <= Q->QSize -1) {
    char lOld = Q->pBuf[Q->Head * Q->DataTypeSz];
    //memcpy(pOld, Q->pBuf + (Q->Head * Q->DataTypeSz), Q->DataTypeSz);

    debug ("Q->Head = %ld Q->Tail =%ld", Q->Head, Q->Tail);
    Q->pBuf[Q->Head * Q->DataTypeSz] = '\0';
    if (Q->Head == Q->Tail) {   // | | | |HT
      Q->Head = Q->Tail = -1;
    } else if (Q->Head == (Q->QSize)) {  // | | | |H
      Q->Head = 0;
    } else {
      if (Q->Head != Q->QSize-1) // Dont increament if Head reach to End of Queue
	Q->Head += 1;
    }
    datalen -= 1;
    Q->ElemCnt -= 1;
  }

  debug("Q->Head=%ld Q->Tail=%ld Q->ElemCnt=%ld", Q->Head, Q->Tail, Q->ElemCnt);
  return (Q->QSize - Q->ElemCnt);
  return QUEUE_OK;
}

void Q_Display (void *_ptr) {
  int i;
  Queue_Desc *Q = (Queue_Desc *)_ptr;
  //  printf ("[m_display] q->front=%lu q->rear=%lu Sz=%lu\n", Q->Head, Q->Tail, Q->QSize);

  for (i=0; i<Q->QSize; i++) {
    printf ("[%d]-[%c]\n", i, *(Q->pBuf+i*Q->DataTypeSz));
  }
  printf("Q->Head=%ld Q->Tail=%d\n", Q->Head, Q->Tail);
}

void Q_Free (void *_ptr) {
  Queue_Desc *Q = (Queue_Desc *)_ptr;
  printf ("[Free] Q= %p pBuf = %p \n", Q, Q->pBuf);
  if(Q->pBuf)
    free((unsigned char *)Q->pBuf);
}

/***** Let's Test the Code *****/
struct task {
  int (*compute)(void *_ptr, char *dataPtr, int datalen);
  char* name;
  int key;
};


int quit() {
  printf ("Good Bye! \n");
  exit(0);
}

struct task func_stat[] = {
  {
    .compute = Enqueue_write,
    .key     = '1',
    .name    = "Enque",
  },
  {
    .compute = Denqueue_read,
    .key     = '2',
    .name    = "Deque",
  },
  {
    .compute = Q_Display,
    .key     = '7',
    .name    = "Dispaly",
  },
  {
    .compute = Q_is_Empty,
    .key = '3',
    .name = "Empty",
  },
  {
    .compute = Q_is_Full,
    .key = '4',
    .name = "Full",
  },
    {
    .compute = Q_Peek,
    .key = '5',
    .name = "Peek",
  },
  {
    .compute = Q_get_Size,
    .key = '6',
    .name = "QSize",
  },
  {
    .compute = Q_Free,
    .key = '8',
    .name = "Free",
  },
  {
    .compute = quit,
    .key = '9',
    .name = "Quit",
  },
};

#define NB_FUNCS (sizeof(func_stat)/(sizeof(struct task)))

void print_all_func() {
  for (int i=0; i<NB_FUNCS; ++i)
    printf ("Press Key %c for %s \n", func_stat[i].key, func_stat[i].name);
}

int test1() {
  char cmd[20];
  char* data = "AtulRaut";
  int length = 6;
  int dataLen;
  Queue_Desc q, *qptr;
  qptr = Q_Init (&q, MAX, sizeof(char));

  printf ("sz = %ld \n", NB_FUNCS);
  printf ("sz=%ld %ld \n", (sizeof(func_stat)), (sizeof(struct task)) );
  if(qptr == NULL)
    return 0;

  printf ("Welcome to Queue 2.0 (advanced)\n");
  printf ("===================================\n");
  print_all_func();
  printf ("===================================\n");

  while (1) {
    debug ("Enter a command");
    fgets(cmd, 20, stdin);

    for (int i=0; i<NB_FUNCS; ++i) {
      if(func_stat[i].key == cmd[0]) {	
	debug ("Calling Command: %s ", func_stat[i].name);	
	debug ("Bytes = %d", func_stat[i].compute(qptr, data, length));
	break;
      }
    }
  }
}

int main () {
  test1();
  //testQ();
  return 0;
}
