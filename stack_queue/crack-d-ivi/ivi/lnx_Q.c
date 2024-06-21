/**
 * Aim : Queue Implementation for IVI
 * Date : Sat Dec  2 08:35:13 AM PST 2023
 * San Diego, CA
 * By : Atul R. Raut
 * Q->[FIFO] : First In First Out
 * Insert --> Rear++ - Tail++
 * Remove --> Front++ - Head++
 * rear -> front = -1
 Ref: https://www.scaler.com/topics/queue-in-c/
 */
/* -------------------------------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)
int min(int x, int y) { return x < y ? x : y; }
/*
 * See Documentation/core-api/circular-buffers.rst for more information.
 */

struct circ_buf {
  char *buf;
  int size;
  int head;
  int tail;
};

struct item {
  int val;
  char name;
};

/* Return count in buffer.  */
#define CIRC_CNT(head,tail,size) (((head) - (tail)) & ((size)-1))

/* Return space available, 0..size-1.  We always leave one free char
   as a completely full buffer has head == tail, which is the same as
   empty.  */
#define CIRC_SPACE(head,tail,size) CIRC_CNT((tail),((head)+1),(size))

/* Return count up to the end of the buffer.  Carefully avoid
   accessing head and tail more than once, so they can change
   underneath us without returning inconsistent results.  */
#define CIRC_CNT_TO_END(head,tail,size) \
	({int end = (size) - (tail); \
	  int n = ((head) + end) & ((size)-1); \
	  n < end ? n : end;})

/* Return space available up to the end of the buffer.  */
#define CIRC_SPACE_TO_END(head,tail,size) \
	({int end = (size) - 1 - (head); \
	  int n = (end + (tail)) & ((size)-1); \
	  n <= end ? n : end+1;})

char enque_producer (struct circ_buf *fifo, int val) {
  if (CIRC_SPACE(fifo->head, fifo->tail, fifo->size) >= 1) {
    fifo->buf[fifo->head] = val;
    debug ("IQ = %c", val);
    fifo->head += 1;
  }
}

char deque_consumer(struct circ_buf *fifo) {
  char c;
  debug ("Buffer Cnt = [%d]", (CIRC_CNT(fifo->head,   fifo->tail, fifo->size)) );
  //debug ("Buffer Spc = [%d]", (CIRC_SPACE(fifo->head, fifo->tail, fifo->size)) );

    if (CIRC_CNT(fifo->head, fifo->tail, fifo->size) >= 1) {
      c = fifo->buf[fifo->tail];
      fifo->tail += 1;
      debug ("DQ = [%c]", c);
    }
    return c;
}

struct circ_buf* q_init (int size) {
  struct circ_buf *circ = (struct circ_buf *)malloc(sizeof(struct circ_buf));
  //u_int32_t data_buf[32];
  u_int32_t *data_buf = (int *)malloc(sizeof(u_int32_t));

  circ->buf = (char *)data_buf; // could be malloced
  circ->head = 0;
  circ->tail = 0;
  circ->size = size;
  return circ;
}

void test () {
  struct circ_buf *circ = q_init (5); // default size is 32
  char local_buf[] = "Atul Ramesh Raut";
  for (int i=50; i<56; ++i)
    enque_producer (circ, i);

  for (int i=50; i<56; ++i) {
    char j = deque_consumer (circ);
    debug ("-> [%c]", j);
  }
}

int main () {
  test ();
}
