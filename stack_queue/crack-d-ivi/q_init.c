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

typedef struct {
  void **buffer;
  int head;
  int tail;
  int capacity;
} NonBlockingCircularQueue;

NonBlockingCircularQueue* create_queue(int capacity) {
  NonBlockingCircularQueue *queue = (NonBlockingCircularQueue *)malloc(sizeof(NonBlockingCircularQueue));
  queue->buffer = (void **)malloc(capacity * sizeof(void *));
  queue->head = 0;
  queue->tail = 0;
  queue->capacity = capacity;
  return queue;
}

int is_empty(NonBlockingCircularQueue *queue) {
  return queue->head == queue->tail;
}

int is_full(NonBlockingCircularQueue *queue) {
  return ((queue->tail + 1) % queue->capacity == queue->head);
}

int write(NonBlockingCircularQueue *queue, void **data, int data_length) {
  int available = queue->capacity - ((queue->tail + 1) % queue->capacity - queue->head);
  int write_len = (data_length < available) ? data_length : available;
  for (int i = 0; i < write_len; i++) {
    queue->buffer[queue->tail] = data[i];
    queue->tail = (queue->tail + 1) % queue->capacity;
  }
  return write_len;
}

void** read(NonBlockingCircularQueue *queue, int length, int *read_len) {
  int available = ((queue->tail + 1) % queue->capacity - queue->head);
  *read_len = (length < available) ? length : available;
  void **data = (void **)malloc((*read_len) * sizeof(void *));
  for (int i = 0; i < *read_len; i++) {
    data[i] = queue->buffer[queue->head];
    queue->head = (queue->head + 1) % queue->capacity;
  }
  return data;
}

void free_queue(NonBlockingCircularQueue *queue) {
  free(queue->buffer);
  free(queue);
}

int test() {

  char cmd[20];
  char* data = "AtulRaut";
  int length = 6;
  int dataLen = 4;

  char* str = "Atul Raut";

  NonBlockingCircularQueue* qPtr = create_init (MAX);

  if(qptr == NULL)
    return 0;

  printf ("Welcome to Queue 2.0 (advanced)\n");
  printf ("===================================\n");

  //  for (int i=0; i<MAX; ++i) {
    write(qPtr, &str, dataLen);
    //  }

}

int main () {
  test();
  return 0;
}
