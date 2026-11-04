/***
    13. Implement a binary min-heap priority queue

    You're building a task scheduler for an embedded system.
    Each task has an integer priority and a task ID.

    Implement a priority queue using a binary min-heap, where
    the task with the smallest priority value is removed first.

    For example, priority 1 is more urgent than priority 5.

    Your queue must support insertion, removing the minimum-priority task,
    and viewing the minimum without removing it.

    Functional requirements
    1. init() — Initialize an empty priority queue with fixed capacity.
    2. push() — Insert a task with a given ID and priority.
    3. pop() — Remove and return the task with the smallest priority.
    4. peek() — Return the minimum-priority task without removing it.
    5. is_empty() — Check whether the queue is empty.
    6. is_full() — Check whether the queue is full.
       If two tasks have equal priority, remove the task with the smaller
       task ID first. You do not need to preserve insertion order.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Sun Nov  1 10:46:23 PST 2026
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
#include <assert.h>

#define debug(str,args...) printf("L=[%d][%s]->[%s] :| "str"\n",__LINE__,__FILE__, __func__, ##args)

struct Task {
  int task_id;
  int priority;
};

struct heap {
  struct Task *buf;
  int hSize;
  int capacity;
};

/* Return index of parent node */
int parent(int i) {
  return (i - 1) / 2;
}

/* Return index of left child */
int left_child(int i) {
  return 2 * i + 1;
}

/* Return index of right child */
int right_child(int i) {
  return 2 * i + 2;
}

/*
 * Return true if a should come before b.
 *
 * Smaller priority wins.
 * For equal priority, smaller task ID wins.
 */
bool is_smaller(struct Task a, struct Task b) {
  if (a.priority != b.priority)
    return a.priority < b.priority;

  return a.task_id < b.task_id;
}

void swap(struct Task *x, struct Task *y) {
  struct Task temp = *x;
  *x = *y;
  *y = temp;
}

/* Initialize heap with given capacity */
struct heap *heap_init(int sz) {
  if (sz <= 0)
    return NULL;

  struct heap *thisHeap = malloc(sizeof(struct heap));

  if (thisHeap == NULL)
    return NULL;

  thisHeap->buf = malloc(sizeof(struct Task) * (size_t)sz);

  if (thisHeap->buf == NULL) {
    free(thisHeap);
    return NULL;
  }

  thisHeap->hSize = 0;
  thisHeap->capacity = sz;

  return thisHeap;
}

/*
 * MIN HEAPIFY - SIFT DOWN
 *
 * Compare root with left and right children.
 * Move the smallest element to the root.
 *
 * Used after deleting the minimum element.
 *
 * Time: O(log N)
 */
void min_heapify(struct heap *heapObj, int root_index) {
  int smallest = root_index;

  int left_child_index = left_child(root_index);
  int right_child_index = right_child(root_index);

  /* Check left child */
  if (left_child_index < heapObj->hSize && is_smaller(heapObj->buf[left_child_index], heapObj->buf[smallest]))
    smallest = left_child_index;

  /* Check right child */
  if (right_child_index < heapObj->hSize && is_smaller(heapObj->buf[right_child_index], heapObj->buf[smallest]))
    smallest = right_child_index;

  /*
   * If a child is smaller than the root,
   * swap and recursively fix that subtree.
   */
  if (smallest != root_index) {
    swap(heapObj->buf + smallest, heapObj->buf + root_index);
    min_heapify(heapObj, smallest);
  }
}

/*
 * INSERT - SIFT UP
 *
 * 1. Insert at the last position.
 * 2. Compare with parent.
 * 3. Swap while child is smaller.
 *
 * Time: O(log N)
 */
bool heap_push(struct heap *heapObj, int task_id, int priority) {

  if (heapObj == NULL || heapObj->hSize == heapObj->capacity)
    return false;

  int i = heapObj->hSize;

  heapObj->buf[i].task_id = task_id;
  heapObj->buf[i].priority = priority;

  heapObj->hSize++;

  /* Move the inserted task upward */
  while (i > 0) {
    int p = parent(i);

    if (!is_smaller(heapObj->buf[i], heapObj->buf[p]))
      break;

    swap(heapObj->buf + i, heapObj->buf + p);

    i = p;
  }

  return true;
}

/*
 * REMOVE MINIMUM - SIFT DOWN
 *
 * 1. Save root (minimum task).
 * 2. Replace root with last task.
 * 3. Reduce heap size.
 * 4. Restore min-heap property.
 *
 * Time: O(log N)
 */
bool heap_pop(struct heap *heapObj, struct Task *out) {
  if (heapObj == NULL || out == NULL || heapObj->hSize == 0)
    return false;

  /* Root always contains minimum task */
  *out = heapObj->buf[0];

  heapObj->hSize--;

  if (heapObj->hSize > 0) {
    heapObj->buf[0] =  heapObj->buf[heapObj->hSize];

    min_heapify(heapObj, 0);
  }

  return true;
}

/* Return minimum without removing it: O(1) */
bool heap_peek(struct heap *heapObj, struct Task *out) {
  if (heapObj == NULL || out == NULL || heapObj->hSize == 0)
    return false;

  *out = heapObj->buf[0];
  return true;
}

bool heap_is_empty(struct heap *heapObj) {
  return heapObj == NULL || heapObj->hSize == 0;
}

bool heap_is_full(struct heap *heapObj) {
  return heapObj != NULL && heapObj->hSize == heapObj->capacity;
}

/*
 * BUILD MIN HEAP FROM ARRAY
 * 0  1  2  3      4  5  6  7
 * [3][6][5][0]    [8][2][1][9]
 * |Internal Notes||  Leaves  |

  Range of Leaves --> |N/2|(floor) + 1 to N.    --> [n/2+1]
  Range of internal Nodes -> 1 to |N/2|(floor). --> [n/2-1]

 * Start at the last internal node: n/2 - 1.
 * Leaves already satisfy the heap property.
 *
 * Time: O(N), not O(N log N).
 */
bool build_min_heap(struct heap *heapObj, const struct Task *arr, int n) {

  if (heapObj == NULL || n < 0 || n > heapObj->capacity || (n > 0 && arr == NULL))
    return false;

  for (int i = 0; i < n; i++)
    heapObj->buf[i] = arr[i];

  heapObj->hSize = n;

  for (int i = n / 2 - 1; i >= 0; i--)
    min_heapify(heapObj, i);

  return true;
}

void heap_print(struct heap *heapObj) {
  if (heapObj == NULL)
    return;

  printf("Heap: ");

  for (int i = 0; i < heapObj->hSize; i++) {
    printf("(%d,%d) ", heapObj->buf[i].task_id, heapObj->buf[i].priority);
  }

  printf("\n");
}

void heap_destroy(struct heap *heapObj) {
  if (heapObj == NULL)
    return;

  free(heapObj->buf);
  free(heapObj);
}

/* ---------------- MAIN / TESTS ---------------- */

int test(void) {
  struct heap *heapObj = heap_init(5);
  struct Task task;

  assert(heapObj != NULL);

  printf("Test 1: Insert tasks\n");

  assert(heap_push(heapObj, 101, 5));
  assert(heap_push(heapObj, 102, 2));
  assert(heap_push(heapObj, 103, 8));
  assert(heap_push(heapObj, 104, 1));
  assert(heap_push(heapObj, 105, 3));

  heap_print(heapObj);

  /* Full heap must reject insertion */
  assert(heap_is_full(heapObj));
  assert(!heap_push(heapObj, 106, 0));

  printf("\nTest 2: Peek minimum\n");

  assert(heap_peek(heapObj, &task));
  assert(task.task_id == 104);
  assert(task.priority == 1);

  printf("Minimum: ID=%d Priority=%d\n", task.task_id, task.priority);

  printf("\nTest 3: Pop in priority order\n");

  int expected_ids[] = {104, 102, 105, 101, 103};
  int expected_priorities[] = {1, 2, 3, 5, 8};

  for (int i = 0; i < 5; i++) {
    assert(heap_pop(heapObj, &task));

    assert(task.task_id == expected_ids[i]);
    assert(task.priority == expected_priorities[i]);

    printf("Popped: ID=%d Priority=%d\n", task.task_id, task.priority);
  }

  assert(heap_is_empty(heapObj));
  assert(!heap_pop(heapObj, &task));
  assert(!heap_peek(heapObj, &task));

  printf("\nTest 4: Equal priorities\n");

  assert(heap_push(heapObj, 30, 5));
  assert(heap_push(heapObj, 10, 5));
  assert(heap_push(heapObj, 20, 5));

  assert(heap_pop(heapObj, &task) && task.task_id == 10);
  assert(heap_pop(heapObj, &task) && task.task_id == 20);
  assert(heap_pop(heapObj, &task) && task.task_id == 30);

  printf("Equal priority ordering PASS\n");

  printf("\nTest 5: Negative and extreme priorities\n");

  assert(heap_push(heapObj, 1, INT_MAX));
  assert(heap_push(heapObj, 2, INT_MIN));
  assert(heap_push(heapObj, 3, -5));

  assert(heap_pop(heapObj, &task) && task.task_id == 2);
  assert(heap_pop(heapObj, &task) && task.task_id == 3);
  assert(heap_pop(heapObj, &task) && task.task_id == 1);

  printf("Negative/extreme priorities PASS\n");

  printf("\nTest 6: Build heap from array\n");

  struct Task arr[] = {
    {101, 9},
    {102, 4},
    {103, 7},
    {104, 1},
    {105, 3}
  };

  assert(build_min_heap(heapObj, arr, 5));
  heap_print(heapObj);

  assert(heap_pop(heapObj, &task));
  assert(task.task_id == 104);

  heap_destroy(heapObj);

  printf("\nTest 7: Invalid capacity\n");

  assert(heap_init(0) == NULL);
  assert(heap_init(-1) == NULL);

  struct heap *single = heap_init(1);
  assert(single != NULL);

  assert(heap_push(single, 42, 0));
  assert(!heap_push(single, 43, 1));
  assert(heap_pop(single, &task) && task.task_id == 42);
  assert(!heap_pop(single, &task));

  heap_destroy(single);

  printf("\nAll tests passed!\n");

  return 0;
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   Test 1: Insert tasks
   Heap: (104,1) (102,2) (103,8) (101,5) (105,3)

   Test 2: Peek minimum
   Minimum: ID=104 Priority=1

   Test 3: Pop in priority order
   Popped: ID=104 Priority=1
   Popped: ID=102 Priority=2
   Popped: ID=105 Priority=3
   Popped: ID=101 Priority=5
   Popped: ID=103 Priority=8

   Test 4: Equal priorities
   Equal priority ordering PASS

   Test 5: Negative and extreme priorities
   Negative/extreme priorities PASS

   Test 6: Build heap from array
   Heap: (104,1) (105,3) (103,7) (102,4) (101,9)

   Test 7: Invalid capacity

   All tests passed!
**/
