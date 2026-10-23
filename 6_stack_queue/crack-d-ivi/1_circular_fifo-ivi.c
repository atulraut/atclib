/***
    Circular ring buffer - FIFO

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Fri Oct 23 09:31:54 PDT 2026
    Folsom, CA.
 */

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

typedef struct {
  uint8_t *data;
  size_t capacity;
  size_t head;    // Next write position
  size_t tail;    // Next read position
  size_t count;   // Number of stored bytes
} RingBuffer;

/*
 * Return actual number of bytes written.
 */
size_t ring_write(RingBuffer *rb, const uint8_t *src, size_t len) {
  if (!rb || !rb->data || !src || rb->capacity == 0)
    return 0;

  // Calculate available space
  size_t avail = rb->capacity - rb->count;

  // Write only what fits
  if (len > avail)
    len = avail;

  if (len == 0)
    return 0;

  // Bytes that fit before end of array
  size_t first = rb->capacity - rb->head;

  if (first > len)
    first = len;

  // Copy first part
  memcpy(rb->data + rb->head, src, first);

  // Copy remaining bytes after wraparound
  if (len > first) {
    memcpy(rb->data,
	   src + first,
	   len - first);
  }

  // Update write position
  rb->head = (rb->head + len) % rb->capacity;

  rb->count += len;

  return len;  // Actual bytes written
}

/*
 * Return actual number of bytes read.
 */
size_t ring_read(RingBuffer *rb, uint8_t *dst, size_t len) {
  if (!rb || !rb->data || !dst || rb->capacity == 0)
    return 0;

  // Read only available data
  if (len > rb->count)
    len = rb->count;

  if (len == 0)
    return 0;

  // Bytes available before end of array
  size_t first = rb->capacity - rb->tail;

  if (first > len)
    first = len;

  // Copy first part
  memcpy(dst, rb->data + rb->tail, first);

  // Copy remaining bytes after wraparound
  if (len > first) {
    memcpy(dst + first,
	   rb->data,
	   len - first);
  }

  // Update read position
  rb->tail = (rb->tail + len) % rb->capacity;

  rb->count -= len;

  return len;  // Actual bytes read
}

int test(void) {
  uint8_t storage[8] = {0};

  RingBuffer rb = {
    .data = storage,
    .capacity = sizeof(storage),
    .head = 0,
    .tail = 0,
    .count = 0
  };

  uint8_t input1[] = {10, 20, 30, 40, 50, 60};
  uint8_t output[16] = {0};

  size_t written = ring_write(&rb, input1, 6);

  printf("Bytes written: %zu\n", written);

  size_t read = ring_read(&rb, output, 4);

  printf("Bytes read: %zu\n", read);

  for (size_t i = 0; i < read; i++)
    printf("%u ", output[i]);

  printf("\n");

  uint8_t input2[] = {70, 80, 90, 100, 110, 120, 130};

  written = ring_write(&rb, input2, 7);

  printf("Bytes written: %zu\n", written);

  read = ring_read(&rb, output, 10);

  printf("Bytes read: %zu\n", read);

  for (size_t i = 0; i < read; i++)
    printf("%u ", output[i]);

  printf("\n");

  return 0;
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   Bytes written: 6
   Bytes read: 4
   10 20 30 40
   Bytes written: 6
   Bytes read: 8
   50 60 70 80 90 100 110 120
**/
