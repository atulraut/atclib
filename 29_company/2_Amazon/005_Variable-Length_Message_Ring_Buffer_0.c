/**

   Implement a variable-length message ring buffer using a fixed-size byte array,
   without dynamic memory allocation.

   Unlike a regular FIFO queue, where each element has the same size,
   this ring buffer stores messages of different lengths while preserving
   message boundaries.

   Round 1 — Problem statement
   Design a ring buffer for an embedded device that receives variable-length
   messages from UART, SPI, or another communication interface.

   Each message consists of a length header followed by payload bytes:
   +----------------+--------------------------+
   | Length (1 byte)| Payload (0 to 15 bytes)  |
   +----------------+--------------------------+


   The buffer must support three operations:
   - push() — append one complete message.
   - pop() — remove the oldest complete message.
   - peek() — inspect the oldest message without removing it.
   Messages must be returned in FIFO order.
   A message may wrap around the end of the underlying byte array.

   Variable-Length Message Ring Buffer — Complete C Implementation
   We'll use a 32-byte circular array that stores messages in this format:
   [Length][Payload bytes][Length][Payload bytes]...

   Each message uses one byte for its length and 0–15 bytes for its payload.
   Both the header and payload can wrap around the end of the array.

   The implementation below supports push, pop, peek, and queue statistics,
   with no dynamic memory allocation.

   Lock-Free SPSC Variable-Length Ring Buffer in C11
   We'll extend the previous implementation to support a UART interrupt
   producer and a worker-thread consumer, without a mutex.

   The key design change is to use two atomic counters:
   - head: the consumer's read position, published after consuming a complete message.
   - tail: the producer's write position, published after writing a complete message.
   This is a single-producer, single-consumer (SPSC) design.
   It is not safe for multiple producers or multiple consumers.

   Sat Oct 31 16:26:15 PDT 2026
   Folsom, CA.

    gcc -std=c11 -O2 -Wall -Wextra -pedantic 003_Variable-Length_Message_Ring_Buffer.c -o ring
**/

/*----------------------------------- Header --------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h> // va_arg
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */
#include <pthread.h>

#define debug(str,args...) printf("L=[%d][%s]->[%s] :| "str"\n",__LINE__,__FILE__, __func__, ##args)

/**
   Understanding is_full and is_empty
   Condition variable	Waiting thread	When it waits	Who signals it
   is_full	Producer	Insufficient free space	Consumer after removing a message
   is_empty	Consumer	No messages available	Producer after inserting a message
**/
#define RING_CAPACITY 32
#define MAX_MESSAGE_SIZE 15

typedef struct {
    uint8_t data[RING_CAPACITY];

    size_t head;
    size_t tail;
    size_t used;
    size_t message_count;

    pthread_mutex_t mutex;
    pthread_cond_t is_full;
    pthread_cond_t is_empty;

    bool closed;
} MessageRing;

bool ring_init(MessageRing *r) {
    if (r == NULL)
        return false;

    r->head = 0;
    r->tail = 0;
    r->used = 0;
    r->message_count = 0;
    r->closed = false;

    if (pthread_mutex_init(&r->mutex, NULL) != 0)
        return false;

    if (pthread_cond_init(&r->is_full, NULL) != 0) {
        pthread_mutex_destroy(&r->mutex);
        return false;
    }

    if (pthread_cond_init(&r->is_empty, NULL) != 0) {
        pthread_cond_destroy(&r->is_full);
        pthread_mutex_destroy(&r->mutex);
        return false;
    }

    return true;
}

/* Producer: insert a variable-length message */
bool ring_push(MessageRing *r, const uint8_t *payload, size_t length) {
  if (r == NULL || length > MAX_MESSAGE_SIZE || (length > 0 && payload == NULL))
    return false;

  size_t required = length + 1;

  pthread_mutex_lock(&r->mutex);

  /* Wait while there is insufficient space */
  while (!r->closed && RING_CAPACITY - r->used < required)
    pthread_cond_wait(&r->is_full, &r->mutex);

  if (r->closed) {
    pthread_mutex_unlock(&r->mutex);
    return false;
  }

  /* Store message length */
  r->data[r->tail] = (uint8_t)length;
  r->tail = (r->tail + 1) % RING_CAPACITY;

  /* Store payload */
  for (size_t i = 0; i < length; i++) {
    r->data[r->tail] = payload[i];
    r->tail = (r->tail + 1) % RING_CAPACITY;
  }

  r->used += required;
  r->message_count++;

  /* Notify consumer that data is available */
  pthread_cond_signal(&r->is_empty);

  pthread_mutex_unlock(&r->mutex);
  return true;
}

/* Consumer: remove oldest message */
bool ring_pop(MessageRing *r, uint8_t *output, size_t output_capacity, size_t *out_length) {
  if (r == NULL || out_length == NULL)
    return false;

  pthread_mutex_lock(&r->mutex);

  /* Wait while the ring is empty */
  while (r->message_count == 0 && !r->closed)
    pthread_cond_wait(&r->is_empty, &r->mutex);

  if (r->message_count == 0) {
    pthread_mutex_unlock(&r->mutex);
    return false;
  }

  size_t length = r->data[r->head];

  if (length > MAX_MESSAGE_SIZE || length + 1 > r->used || length > output_capacity || (length > 0 && output == NULL)) {
    pthread_mutex_unlock(&r->mutex);
    return false;
  }

  size_t pos = (r->head + 1) % RING_CAPACITY;

  for (size_t i = 0; i < length; i++) {
    output[i] = r->data[pos];
    pos = (pos + 1) % RING_CAPACITY;
  }

  r->head = pos;
  r->used -= length + 1;
  r->message_count--;

  *out_length = length;

  /* Notify producer that space is available */
  pthread_cond_broadcast(&r->is_full);

  pthread_mutex_unlock(&r->mutex);
  return true;
}

/* Close queue and wake waiting threads */
void ring_close(MessageRing *r) {
  if (r == NULL)
    return;

  pthread_mutex_lock(&r->mutex);

  r->closed = true;

  pthread_cond_broadcast(&r->is_empty);
  pthread_cond_broadcast(&r->is_full);

  pthread_mutex_unlock(&r->mutex);
}

/* Destroy only after all threads have exited */
void ring_destroy(MessageRing *r) {
  if (r == NULL)
    return;

  pthread_cond_destroy(&r->is_empty);
  pthread_cond_destroy(&r->is_full);
  pthread_mutex_destroy(&r->mutex);
}

void *producer_thread(void *arg) {
  MessageRing *r = arg;

  uint8_t msg1[] = {0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF};
  uint8_t msg2[] = {0xAA, 0xBB};
  uint8_t msg3[] = {0x11, 0x22, 0x33, 0x44};

  ring_push(r, msg1, sizeof(msg1));
  ring_push(r, msg2, sizeof(msg2));
  ring_push(r, msg3, sizeof(msg3));

  ring_close(r);

  return NULL;
}

void *consumer_thread(void *arg) {
  MessageRing *r = arg;

  uint8_t output[MAX_MESSAGE_SIZE];
  size_t length;

  while (ring_pop(r, output, sizeof(output), &length)) {

    printf("Consumed length=%zu: ", length);

    for (size_t i = 0; i < length; i++)
      printf("%02X ", output[i]);

    printf("\n");
  }

  return NULL;
}

int test(void) {
  MessageRing ring;
  pthread_t producer, consumer;

  if (!ring_init(&ring))
    return 1;

  if (pthread_create(&consumer, NULL, consumer_thread, &ring) != 0) {
    ring_destroy(&ring);
    return 1;
  }

  if (pthread_create(&producer, NULL, producer_thread, &ring) != 0) {
    ring_close(&ring);
    pthread_join(consumer, NULL);
    ring_destroy(&ring);
    return 1;
  }

  pthread_join(producer, NULL);
  pthread_join(consumer, NULL);

  ring_destroy(&ring);
  return 0;
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   Consumed length=15: 10 20 30 40 50 60 70 80 90 0A 0B 0C 0D 0E 0F
   Consumed length=2: AA BB
   Consumed length=4: 11 22 33 44
**/
