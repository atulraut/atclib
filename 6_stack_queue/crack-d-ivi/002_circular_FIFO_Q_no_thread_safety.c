/**
   Circular Queue for IVI

   Also thread safe Queue :
   https://github.com/atulraut/atclib/blob/master/thread/crack-d-ivi/1_thread_safe_fifo.c

   Date :
   Folsom, CA, USA.
**/

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

/*----------------------------------- Micro --------------------------------------*/
#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

#define FIFO_SIZE 8

typedef struct {
  int buffer[FIFO_SIZE];

  int head;       // next position to read
  int tail;       // next position to write
  int count;      // number of elements currently stored
} fifo_t;

/* Initialize FIFO */
int fifo_init(fifo_t *q) {
  if (q == NULL)
    return -1;

  q->head = 0;
  q->tail = 0;
  q->count = 0;

  return 0;
}

/* PUSH: false -> FIFO full */
bool fifo_push(fifo_t *q, int value) {
  if (q == NULL)
    return false;

  /* FIFO full */
  if (q->count == FIFO_SIZE)
    return false;
  /* Write at tail */
  q->buffer[q->tail] = value;
  /*  Move tail circularly. */
  q->tail = (q->tail + 1) % FIFO_SIZE;
  q->count++;

  return true; // success
}

/* POP : false -> FIFO empty */
bool fifo_pop(fifo_t *q, int *value) {
  if (q == NULL || value == NULL)
    return false;

  /* FIFO empty */
  if (q->count == 0)
    return false;
  /* Read from head. */
  *value = q->buffer[q->head];
  /* Move head circularly. */
  q->head = (q->head + 1) % FIFO_SIZE;
  q->count--;

  return true; // success
}

bool fifo_is_empty(fifo_t *q) {
  if (q == NULL)
    return true;

  return q->count == 0;
}

bool fifo_is_full(fifo_t *q) {
  if (q == NULL)
    return false;

  return q->count == FIFO_SIZE;
}

int fifo_count(fifo_t *q) {
  if (q == NULL)
    return 0;
  return q->count;
}

int main(void) {
    fifo_t fifo;

  fifo_init(&fifo);

  /* Producer-like operations */
  for (int i = 1; i <= 5; i++) {
    if (fifo_push(&fifo, i * 10))
      debug("PUSH -> %d", i * 10);
    else
      debug("FIFO FULL");
  }
  debug("Elements in FIFO: %d", fifo_count(&fifo));

  /* Consumer-like operations */
  int value;
  while (fifo_pop(&fifo, &value)) {
    debug("POP  <- %d", value);
  }
  debug("FIFO empty = %s", fifo_is_empty(&fifo) ? "yes" : "no");

  return 0;
}

/**
   [main] L=142 :PUSH -> 10
   [main] L=142 :PUSH -> 20
   [main] L=142 :PUSH -> 30
   [main] L=142 :PUSH -> 40
   [main] L=142 :PUSH -> 50
   [main] L=147 :Elements in FIFO: 5
   [main] L=155 :POP  <- 10
   [main] L=155 :POP  <- 20
   [main] L=155 :POP  <- 30
   [main] L=155 :POP  <- 40
   [main] L=155 :POP  <- 50
   [main] L=158 :FIFO empty = yes
**/
