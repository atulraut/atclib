/**

   Implement a FIFO queue using a fixed-size array

   Sat Oct 31 16:26:15 PDT 2026
   Folsom, CA

**/
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

#define CAPACITY 5

typedef struct {
  int data[CAPACITY];
  size_t front;
  size_t count;
} CircularDeque;

void deque_init(CircularDeque *dq) {
  dq->front = 0;
  dq->count = 0;
}

bool is_empty(const CircularDeque *dq) {
  return dq->count == 0;
}

bool is_full(const CircularDeque *dq) {
  return dq->count == CAPACITY;
}

bool push_front(CircularDeque *dq, int value) {
  if (is_full(dq))
    return false;

  dq->front = (dq->front + CAPACITY - 1) % CAPACITY;
  dq->data[dq->front] = value;
  dq->count++;

  return true;
}

bool push_back(CircularDeque *dq, int value) {
  if (is_full(dq))
    return false;

  size_t rear = (dq->front + dq->count) % CAPACITY;

  dq->data[rear] = value;
  dq->count++;

  return true;
}

bool pop_front(CircularDeque *dq, int *value) {
  if (value == NULL || is_empty(dq))
    return false;

  *value = dq->data[dq->front];

  dq->front = (dq->front + 1) % CAPACITY;
  dq->count--;

  return true;
}

bool pop_back(CircularDeque *dq, int *value) {
  if (value == NULL || is_empty(dq))
    return false;

  size_t rear = (dq->front + dq->count - 1) % CAPACITY;

  *value = dq->data[rear];
  dq->count--;

  return true;
}

bool peek_front(const CircularDeque *dq, int *value) {
  if (value == NULL || is_empty(dq))
    return false;

  *value = dq->data[dq->front];
  return true;
}

bool peek_back(const CircularDeque *dq, int *value) {
  if (value == NULL || is_empty(dq))
    return false;

  size_t rear = (dq->front + dq->count - 1) % CAPACITY;

  *value = dq->data[rear];
  return true;
}

void deque_print(const CircularDeque *dq) {
  printf("Deque: [");

  for (size_t i = 0; i < dq->count; i++) {
    size_t index = (dq->front + i) % CAPACITY;

    printf("%d", dq->data[index]);

    if (i + 1 < dq->count)
      printf(", ");
  }

  printf("]\n");
}

int main(void) {
  CircularDeque dq;
  int value;

  deque_init(&dq);

  push_back(&dq, 10);
  push_back(&dq, 20);
  push_front(&dq, 5);
  deque_print(&dq);       // [5, 10, 20]

  pop_front(&dq, &value);
  printf("Pop front: %d\n", value);

  push_back(&dq, 30);
  push_front(&dq, 7);
  push_back(&dq, 40);

  deque_print(&dq);       // [7, 10, 20, 30, 40]

  if (!push_back(&dq, 50))
    printf("Deque is full\n");

  pop_back(&dq, &value);
  printf("Pop back: %d\n", value);

  deque_print(&dq);       // [7, 10, 20, 30]

  return 0;
}
