/***

    FB  - Implement a non-blocking circular queue of bytes.
    Reads can be of arbitrary length (but should return the
    max available),
    writes can be of arbitrary length (but should return the
    bytes actually written).

    gcc.... -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Thu Mar  5 13:49:48 PST 2026
    MacOs
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

enum num_q {
  READ_Q = 1,
  WRITE_Q = 2,
  QUIT = 3,
};

struct CircularByteQueue {
  unsigned char *buffer;  // underlying storage
  size_t capacity;        // total buffer size
  size_t head;            // read index
  size_t tail;            // write index
  size_t size;            // current number of bytes stored
};

// Initialize the queue
int cbq_init(struct CircularByteQueue *q, size_t capacity) {

  if (capacity == 0)
    return -1;
  q->buffer = (unsigned char *)malloc(capacity);
  if (!q->buffer)
    return -1;
  q->capacity = capacity;
  q->head = 0;
  q->tail = 0;
  q->size = 0;
  return 0;
}

// Free the queue
void cbq_free(struct CircularByteQueue *q) {

  free(q->buffer);
  q->buffer = NULL;
  q->capacity = q->size = q->head = q->tail = 0;
}

// Write bytes to the queue; returns number of bytes actually written
size_t cbq_write(struct CircularByteQueue *q, const unsigned char *data, size_t len) {

  if (len == 0 /*|| q->size == q->capacity*/) {
    debug ("q->size=%zu q->capacity=%zu", q->size, q->capacity);
    return 0;
  }

  size_t bytes_to_write = len;
  debug ("bytes_to_write=%zu, q->capacity-q->size=%zu", bytes_to_write, (q->capacity-q->size));
  if (bytes_to_write > q->capacity - q->size)
    bytes_to_write = q->capacity - q->size;

  size_t first_part = q->capacity - q->tail;
  if (first_part > bytes_to_write)
    first_part = bytes_to_write;

  memcpy(q->buffer + q->tail, data, first_part);

  size_t second_part = bytes_to_write - first_part;
  debug ("second_part=%zu bytes_to_write=%zu, q->capacity-q->size=%zu",second_part, bytes_to_write, (q->capacity-q->size));
  if (second_part > 0) {
    memcpy(q->buffer, data + first_part, second_part);
  }

  q->tail = (q->tail + bytes_to_write) % q->capacity;
  q->size += bytes_to_write;

  return bytes_to_write;
}

// Read bytes from the queue; returns number of bytes actually read
size_t cbq_read(struct CircularByteQueue *q, unsigned char *dest, size_t len) {

  if (len == 0 || q->size == 0)
    return 0;

  size_t bytes_to_read = len;
  if (bytes_to_read > q->size)
    bytes_to_read = q->size;

  size_t first_part = q->capacity - q->head;
  if (first_part > bytes_to_read)
    first_part = bytes_to_read;

  memcpy(dest, q->buffer + q->head, first_part);

  size_t second_part = bytes_to_read - first_part;
  if (second_part > 0) {
    memcpy(dest + first_part, q->buffer, second_part);
  }

  q->head = (q->head + bytes_to_read) % q->capacity;
  q->size -= bytes_to_read;

  return bytes_to_read;
}

// Return bytes available to read
size_t cbq_available_to_read(struct CircularByteQueue *q) {
  return q->size;
}

// Return bytes available to write
size_t cbq_available_to_write(struct CircularByteQueue *q) {
  return q->capacity - q->size;
}

// Default Test
int test_1 () {

  struct CircularByteQueue q;
  if (cbq_init(&q, 10) != 0) {
    fprintf(stderr, "Failed to initialize queue\n");
    return 1;
  }

  unsigned char data[] = "hello world"; // 12 bytes
  debug ("data sz = %ld", sizeof(data));
  size_t written = cbq_write(&q, data, sizeof(data)-1);
  printf("Written bytes: %zu\n", written); // should be 10 (capacity)

  unsigned char buffer[6];
  size_t read_bytes = cbq_read(&q, buffer, 5);
  buffer[read_bytes] = '\0';
  printf("Read bytes: %zu, Data: %s\n", read_bytes, buffer); // "hello"

  read_bytes = cbq_read(&q, buffer, 10);
  buffer[read_bytes] = '\0';
  printf("Read remaining bytes: %zu, Data: %s\n", read_bytes, buffer); // " worl"

  cbq_free(&q);
  return 0;
}

// Write overwrite Test
int test_2 () {

  struct CircularByteQueue q;
  size_t written = 0;
  if (cbq_init(&q, 10) != 0) {
    fprintf(stderr, "Failed to initialize queue\n");
    return 1;
  }

  unsigned char data[] = "hello world"; // 12 bytes
  debug ("data sz = %ld", sizeof(data));
  written = cbq_write(&q, data, sizeof(data)-1);
  printf("1. Written bytes: %zu\n", written); // should be 10 (capacity)
  unsigned char data2[] = "ATUL";
  written = cbq_write(&q, data2, sizeof(data2)-1);
  printf("2. Written bytes: %zu\n", written); // should be 10 (capacity)

  unsigned char buffer[6];
  size_t read_bytes = cbq_read(&q, buffer, 5);
  buffer[read_bytes] = '\0';
  printf("3. Read bytes: %zu, Data: %s\n", read_bytes, buffer); // "hello"

  written = cbq_write(&q, data2, sizeof(data2)-1);
  printf("4. Written bytes: %zu\n", written); // should be 10 (capacity)

  read_bytes = cbq_read(&q, buffer, 10);
  buffer[read_bytes] = '\0';
  printf("5. Read remaining bytes: %zu, Data: %s\n", read_bytes, buffer); // " worl"

  cbq_free(&q);
  return 0;
}

// Manual way of testing different scenarios
int test3() {

  static size_t read_bytes;
  static size_t written;
  unsigned char *buffer = (unsigned char*)malloc(sizeof(unsigned char) * 6);
  unsigned char data[] = "hello world";
  debug ("data = %s", data);
  struct CircularByteQueue q;
  debug ("data sz = %ld", sizeof(data));

  if (cbq_init(&q, 10) != 0) {
    fprintf(stderr, "Failed to initialize queue\n");
    return 1;
  }

  while(1) {
    debug ("1:Read...2:Write...3:Quit\n");
    int option;
    scanf("%d", &option);

    switch(option) {
    case READ_Q:
      read_bytes = cbq_read(&q, buffer, 5);
      buffer[read_bytes] = '\0';
      printf("Read bytes: %zu, Data: %s\n", read_bytes, buffer); // "hello"

      read_bytes = cbq_read(&q, buffer, 10);
      buffer[read_bytes] = '\0';
      printf("Read remaining bytes: %zu, Data: %s\n", read_bytes, buffer); // " worl"
      break;
    case WRITE_Q:
      written = cbq_write(&q, data, sizeof(data)-1);
      printf("Written bytes: %zu\n", written); // should be 10 (capacity)
      break;
    case QUIT:
      cbq_free(&q);
      exit(1);
      break;
    default:
      break;
    }
    printf ("");
  }
}

int main() {

  int ret = test_2();
  if (ret)
    return ret;
  return 0;
}
