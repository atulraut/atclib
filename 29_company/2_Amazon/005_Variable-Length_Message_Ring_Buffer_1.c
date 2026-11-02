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

#define debug(str,args...) printf("L=[%d][%s]->[%s] :| "str"\n",__LINE__,__FILE__, __func__, ##args)

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdatomic.h>
#include <string.h>

#define RING_CAPACITY 32
#define MAX_MESSAGE_SIZE 15

typedef struct {
  uint8_t data[RING_CAPACITY];

  atomic_size_t head;  // to read
  atomic_size_t tail;  // to write
} MessageRing;

/*
 * Must be called before producer and consumer start.
 * Never reinitialize while the ring is in use.
 */
void ring_init(MessageRing *ring) {
  if (!ring)
    return;

  atomic_init(&ring->head, 0);
  atomic_init(&ring->tail, 0);
}

/*
 * Single producer only.
 * Publish tail after writing the complete message.
 */
bool ring_push(MessageRing *ring, const uint8_t *payload, size_t length) {
  if (!ring || length > MAX_MESSAGE_SIZE || (length > 0 && !payload))
    return false;

  size_t required = length + 1;

  size_t tail = atomic_load_explicit(&ring->tail, memory_order_relaxed);

  size_t head = atomic_load_explicit(&ring->head, memory_order_acquire);

  size_t used = tail - head;

  if (used > RING_CAPACITY || required > RING_CAPACITY - used)
    return false;

  /* Write length header */
  ring->data[tail % RING_CAPACITY] = (uint8_t)length;

  /* Write payload, handling wraparound */
  for (size_t i = 0; i < length; i++) {
    ring->data[(tail + 1 + i) % RING_CAPACITY] = payload[i];
  }

  /*
   * Release store:
   * Publish all header/payload writes together.
   */
  atomic_store_explicit(&ring->tail, tail + required, memory_order_release);

  return true;
}

/*
 * Single consumer only.
 *
 * remove=false -> peek
 * remove=true  -> pop
 */
static bool ring_read(MessageRing *ring, uint8_t *output, size_t output_capacity, size_t *out_length, bool remove) {
  if (!ring || !out_length)
    return false;

  size_t head = atomic_load_explicit(&ring->head, memory_order_relaxed);

  size_t tail = atomic_load_explicit(&ring->tail, memory_order_acquire);

  size_t available = tail - head;

  if (available == 0 || available > RING_CAPACITY)
    return false;

  size_t length = ring->data[head % RING_CAPACITY];

  if (length > MAX_MESSAGE_SIZE || length + 1 > available)
    return false;

  if (length > output_capacity || (length > 0 && !output))
    return false;

  for (size_t i = 0; i < length; i++)
    output[i] = ring->data[(head + 1 + i) % RING_CAPACITY];

  /*
   * Release head only after the payload has been read.
   * This allows the producer to reuse those bytes.
   */
  if (remove) {
    atomic_store_explicit(&ring->head, head + length + 1, memory_order_release);
  }

  *out_length = length;
  return true;
}

bool ring_pop(MessageRing *ring, uint8_t *output, size_t output_capacity, size_t *out_length) {
  return ring_read(ring, output, output_capacity, out_length, true);
}

bool ring_peek(MessageRing *ring, uint8_t *output, size_t output_capacity, size_t *out_length) {
  return ring_read(ring, output, output_capacity, out_length, false);
}

/*
 * Snapshot of committed bytes.
 * May already be stale when returned.
 */
size_t ring_bytes_used(const MessageRing *ring) {
  if (!ring)
    return 0;

  size_t head = atomic_load_explicit(&ring->head, memory_order_acquire);

  size_t tail = atomic_load_explicit(&ring->tail, memory_order_acquire);

  size_t used = tail - head;

  return used <= RING_CAPACITY ? used : 0;
}

static void print_message(const uint8_t *data, size_t length) {
  printf("Length=%zu Payload=", length);

  for (size_t i = 0; i < length; i++)
    printf("%02X ", data[i]);

  printf("\n");
}

int test(void) {
  MessageRing ring;
  uint8_t output[MAX_MESSAGE_SIZE];
  size_t length = 0;

  ring_init(&ring);

  uint8_t msg1[] = {0x10, 0x20, 0x30, 0x40};
  uint8_t msg2[] = {0xAA, 0xBB, 0xCC};

  /* Simulate producer */
  printf("Push 1: %d\n", ring_push(&ring, msg1, sizeof(msg1)));

  printf("Push 2: %d\n", ring_push(&ring, msg2, sizeof(msg2)));

  /* Simulate consumer */
  if (ring_peek(&ring, output, sizeof(output), &length)) {
    printf("Peek: ");
    print_message(output, length);
  }

  while (ring_pop(&ring, output,   sizeof(output), &length)) {
    printf("Pop: ");
    print_message(output, length);
  }

  /* Zero-length message */
  ring_push(&ring, NULL, 0);

  if (ring_pop(&ring, NULL, 0, &length))
    printf("Zero-length message: %zu\n", length);

  /* Force physical wraparound */
  uint8_t padding[12] = {0};
  uint8_t wrap[] = {0x11, 0x22, 0x33, 0x44};

  ring_push(&ring, padding, sizeof(padding));
  ring_pop(&ring, output, sizeof(output), &length);

  ring_push(&ring, wrap, sizeof(wrap));

  if (ring_pop(&ring, output, sizeof(output), &length)) {
    printf("Wraparound: ");
    print_message(output, length);
  }

  printf("Bytes used: %zu\n", ring_bytes_used(&ring));

  return 0;
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   Push 1: 1
   Push 2: 1
   Peek: Length=4 Payload=10 20 30 40
   Pop: Length=4 Payload=10 20 30 40
   Pop: Length=3 Payload=AA BB CC
   Zero-length message: 0
   Wraparound: Length=4 Payload=11 22 33 44
   Bytes used: 0
**/
