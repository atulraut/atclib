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

int enque_producer (struct circ_buf *fifo, const void *buf, int sz) {
  //spin_lock(&producer_lock);
  const char *ptr = buf;

  /* The spin_unlock() and next spin_lock() provide needed ordering. */

  //	if (CIRC_SPACE(fifo->head, fifo->tail, fifo->size) >= 1) {
  while (sz > 0) {
    char *fptr = &fifo->buf[fifo->head];
    int n;
    if (CIRC_SPACE(fifo->head, fifo->tail, fifo->size)) {
      n = min(sz, CIRC_SPACE_TO_END(fifo->head, fifo->tail, fifo->size));
      memcpy (fptr, ptr, n);
      sz -= n;
      ptr += n;
      //      fifo[fifo->head] = val;
      //fifo->head += 1;
      // wakeup all
    }
  }
  /* insert one item into the buffer */
  //struct item *item = fifo[head];

  //		produce_item(item);

  //		smp_store_release(buffer->head,
  //				  (head + 1) & (buffer->size - 1));

  /* wake_up() will make sure that the head is committed before
   * waking anyone up */
  //		wake_up(consumer);
  //}
//	spin_unlock(&producer_lock);
}

int deque_consumer(struct circ_buf *fifo) {
  //	spin_lock(&consumer_lock);
  char val;
	/* Read index before reading contents at that index. */
  //	unsigned long head = smp_load_acquire(buffer->head);
        unsigned long head = fifo->head;
	unsigned long tail = fifo->tail;

	if (CIRC_CNT(fifo->head, fifo->tail, fifo->size) >= 1) {

		/* extract one item from the buffer */
		// struct item *item = buffer[tail];
	
	  val = fifo->buf[fifo->tail];
	  debug ("Op-< [%c]", val);
	  fifo->tail += 1;
	  //	consume_item(item);

		/* Finish reading descriptor before incrementing tail. */
	  //		smp_store_release(buffer->tail,
	  //			  (tail + 1) & (buffer->size - 1));
	}

	//	spin_unlock(&consumer_lock);
	return val;

}

struct circ_buf* q_init (int size) {
  struct circ_buf *circ = (struct circ_buf *)malloc(sizeof(struct circ_buf));
  //u_int32_t data_buf[32];
  u_int32_t *data_buf = (int *)malloc(sizeof(u_int32_t));

  circ->buf = (char *)data_buf; // could be malloced
  circ->head = -1;
  circ->tail = -1;
  circ->size = size;
  return circ;
}

void test () {
  struct circ_buf *circ = q_init (32); // default size is 32
  char local_buf[] = "Atul Ramesh Raut";
  //  for (int i=1; i<6; ++i)
  enque_producer (circ, local_buf, 4);

  for (int i=1; i<6; ++i) {
    int j = deque_consumer (circ);
    debug ("-> [%d]", j);
  }
}

int main () {
  test ();
}
