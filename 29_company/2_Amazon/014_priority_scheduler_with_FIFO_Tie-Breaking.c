***

    Implement Priority Scheduler with FIFO Tie-Breaking

    You're developing a scheduler for an embedded system that
    processes tasks from multiple subsystems.

    Each task has a unique ID, a priority, and a name.

    The scheduler must execute tasks according to two rules:
    1. Priority first: A lower numerical priority means a more
    urgent task. Priority 1 executes before priority 5.

    2. FIFO tie-breaking: If two tasks have the same priority, the
    task submitted earlier must execute first.
    For this interview, scheduling means selecting and removing the next task.
    You do not need to create OS threads or actually execute task functions.

    Functional requirements
    Implement a scheduler that supports:
    - scheduler_init() — Initialize an empty scheduler.
    - scheduler_add() — Add a task with a unique ID, priority, and name.
    - scheduler_next() — Remove and return the highest-priority task, using FIFO for equal priorities.
    - scheduler_peek() — View the next task without removing it.
    - scheduler_cancel() — Cancel a queued task by ID.
    - scheduler_size() — Return the number of queued tasks.
    For the initial version, duplicate task IDs must be rejected. Once a task
    has been removed or canceled, its ID may be reused.

    Constraints
    Property             Requirement
    Language             C11
    Maximum queued tasks 1,000
    Task ID              Any int, including negative values
    Priority             Integer from 0 to 9
    Task name            Up to 31 characters
    Allocation           Fixed-size storage; no malloc()
    Ordering             Priority first, FIFO on ties
    Add                  O(log N)
    Next                 O(log N)
    Peek                 O(1)
    Cancel by ID         O(N) acceptable initially
    Thread safety        Not required for first version

    You may use a binary min-heap. The important difference from the previous priority-queue
    problem is that equal priorities must preserve insertion order, rather than using
    task ID as the tie-breaker.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Sun Nov  1 11:43:53 PST 2026
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

#define MAX_TASK_NAME 32
#define MAX_TASKS 1000
/**
   In a min-heap, every parent must have a value smaller than or equal to its children.
**/
/*
 * Each task has:
 * - task_id: unique identifier
 * - priority: smaller number means higher priority
 * - sequence: arrival order, used for FIFO tie-breaking
 */
struct Task {
  int task_id;
  int priority;
  char name[MAX_TASK_NAME];
  uint64_t sequence;
};

struct heap {
  struct Task *buf;
  int hSize;
  int capacity;

  /* Incremented whenever a task is inserted */
  uint64_t next_sequence;
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
 * Compare two tasks.
 *
 * 1. Smaller priority executes first.
 * 2. If priorities match, earlier sequence executes first.
 *
 * Example:
 * Task A: priority=2, sequence=5
 * Task B: priority=2, sequence=8
 *
 * Task A executes first.
 */
bool is_smaller(struct Task a, struct Task b) {
  if (a.priority != b.priority)
    return a.priority < b.priority;

  return a.sequence < b.sequence;
}

/* Swap two tasks */
  void swap(struct Task *x, struct Task *y) {
    struct Task temp = *x;
    *x = *y;
    *y = temp;
  }

/* Initialize scheduler heap */
struct heap *heap_init(int sz) {
  if (sz <= 0 || sz > MAX_TASKS)
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
  thisHeap->next_sequence = 0;

  return thisHeap;
}

/*
 * MIN HEAPIFY - SIFT DOWN
 *
 * Used when removing or canceling a task.
 *
 * 1. Compare root with left and right children.
 * 2. Find the task that should execute first.
 * 3. Swap if the root is not the smallest.
 * 4. Recursively fix the affected subtree.
 *
 * Time: O(log N)
 */
void min_heapify(struct heap *heapObj, int root_index) {
  int smallest = root_index;

  int left_child_index = left_child(root_index);
  int right_child_index = right_child(root_index);

  if (left_child_index < heapObj->hSize && is_smaller(heapObj->buf[left_child_index], heapObj->buf[smallest])) {
    smallest = left_child_index;
  }

  if (right_child_index < heapObj->hSize && is_smaller(heapObj->buf[right_child_index], heapObj->buf[smallest])) {
    smallest = right_child_index;
  }

  if (smallest != root_index) {
    swap(heapObj->buf + smallest, heapObj->buf + root_index);

    min_heapify(heapObj, smallest);
  }
}

/*
 * SIFT UP
 * Also percolate_up : is an operation that restores the heap property after inserting a new element.
 * When inserting a new element, we place it at the end of the heap array.
 * If it is smaller than its parent, we swap them and continue moving upward until the heap property is satisfied.
 * Used after inserting a task.
 * Move task toward root while it should execute
 * before its parent.
 *
 * Time: O(log N)
 */
void heapify_up(struct heap *heapObj, int i) {
  while (i > 0) {
    int p = parent(i);

    if (!is_smaller(heapObj->buf[i], heapObj->buf[p]))
      break;

    swap(heapObj->buf + i, heapObj->buf + p);
    i = p;
  }
}

/*
 * ADD TASK
 *
 * 1. Validate inputs.
 * 2. Reject duplicate task IDs.
 * 3. Insert at last position.
 * 4. Assign sequence number.
 * 5. Restore heap property using sift-up.
 *
 * Time: O(N) because duplicate IDs are checked
 * by linear search. Heap insertion itself is O(log N).
 */
bool scheduler_add(struct heap *heapObj, int task_id, int priority, const char *name) {

  if (heapObj == NULL || name == NULL)
    return false;

  if (priority < 0 || priority > 9)
    return false;

  if (heapObj->hSize == heapObj->capacity)
    return false;

  /* Check name length without reading beyond limit */
  size_t len = 0;

  while (len < MAX_TASK_NAME && name[len] != '\0')
    len++;

  if (len == MAX_TASK_NAME)
    return false;

  /* Reject duplicate task IDs */
  for (int i = 0; i < heapObj->hSize; i++) {
    if (heapObj->buf[i].task_id == task_id)
      return false;
  }

  /*
   * Prevent sequence overflow.
   * Reusing sequence numbers could break FIFO ordering.
   */
  if (heapObj->next_sequence == UINT64_MAX)
    return false;

  int i = heapObj->hSize;

  heapObj->buf[i].task_id = task_id;
  heapObj->buf[i].priority = priority;
  memcpy(heapObj->buf[i].name, name, len + 1);

  /* Earlier tasks get smaller sequence numbers */
  heapObj->buf[i].sequence = heapObj->next_sequence++;

  heapObj->hSize++;

  heapify_up(heapObj, i);

  return true;
}

/*
 * NEXT TASK - REMOVE MINIMUM
 *
 * 1. Root contains highest-priority task.
 * 2. Copy root into output.
 * 3. Move last task to root.
 * 4. Decrease heap size.
 * 5. Restore heap property with min_heapify
 *
 * Time: O(log N)
 */
bool scheduler_next(struct heap *heapObj, struct Task *out) {
  if (heapObj == NULL || out == NULL ||
      heapObj->hSize == 0)
    return false;

  *out = heapObj->buf[0];

  heapObj->hSize--;

  if (heapObj->hSize > 0) {
    heapObj->buf[0] = heapObj->buf[heapObj->hSize];

    min_heapify(heapObj, 0);
  }

  return true;
}

/* Read next task without removing it: O(1) */
bool scheduler_peek(struct heap *heapObj, struct Task *out) {
  if (heapObj == NULL || out == NULL ||
      heapObj->hSize == 0)
    return false;

  *out = heapObj->buf[0];
  return true;
}

/*
 * CANCEL TASK BY ID
 *
 * 1. Search for the task.
 * 2. Replace it with the last task.
 * 3. Restore heap property.
 *
 * Replacement may need to move UP or DOWN.
 *
 * Time: O(N) search + O(log N) repair.
 */
bool scheduler_cancel(struct heap *heapObj, int task_id) {
  if (heapObj == NULL)
    return false;

  int i;

  for (i = 0; i < heapObj->hSize; i++) {
    if (heapObj->buf[i].task_id == task_id)
      break;
  }

  if (i == heapObj->hSize)
    return false;

  heapObj->hSize--;

  /* If canceled task was last, no repair needed */
  if (i == heapObj->hSize)
    return true;

  /* Fill the hole with the last task */
  heapObj->buf[i] = heapObj->buf[heapObj->hSize];

  /*
   * If replacement is smaller than its parent,
   * move upward; otherwise, move downward.
   */
  if (i > 0 && is_smaller(heapObj->buf[i], heapObj->buf[parent(i)])) {
    heapify_up(heapObj, i);
  } else {
    min_heapify(heapObj, i);
  }

  return true;
}

int scheduler_size(struct heap *heapObj) {
  if (heapObj == NULL)
    return 0;

  return heapObj->hSize;
}

void heap_print(struct heap *heapObj) {
  if (heapObj == NULL)
    return;

  printf("Heap array:\n");

  for (int i = 0; i < heapObj->hSize; i++) {
    printf("[%d] ID=%d Priority=%d Sequence=%llu Name=%s\n", i, heapObj->buf[i].task_id, heapObj->buf[i].priority,
	   (unsigned long long)heapObj->buf[i].sequence, heapObj->buf[i].name);
  }
}

void heap_destroy(struct heap *heapObj) {
  if (heapObj == NULL)
    return;

  free(heapObj->buf);
  free(heapObj);
}

int test(void) {
  struct heap *heapObj = heap_init(5);
  struct Task task;

  assert(heapObj != NULL);

  printf("Test 1: Add tasks\n");

  assert(scheduler_add(heapObj, 101, 3, "Network"));
  assert(scheduler_add(heapObj, 102, 1, "Sensor"));
  assert(scheduler_add(heapObj, 103, 3, "Logging"));
  assert(scheduler_add(heapObj, 104, 1, "Safety"));
  assert(scheduler_add(heapObj, 105, 2, "Storage"));

  heap_print(heapObj);

  printf("\nTest 2: Reject invalid insertions\n");

  assert(!scheduler_add(heapObj, 101, 3, "Duplicate"));
  assert(!scheduler_add(heapObj, 106, 2, "Full"));
  assert(!scheduler_add(heapObj, 107, -1, "Invalid"));

  printf("\nTest 3: Peek\n");

  assert(scheduler_peek(heapObj, &task));
  assert(task.task_id == 102);
  assert(scheduler_size(heapObj) == 5);

  printf("Next: %s (ID=%d, Priority=%d)\n", task.name, task.task_id, task.priority);

  printf("\nTest 4: Priority + FIFO execution\n");

  int expected[] = {102, 104, 105, 101, 103};

  for (int i = 0; i < 5; i++) {
    assert(scheduler_next(heapObj, &task));
    assert(task.task_id == expected[i]);

    printf("Execute: ID=%d Priority=%d Name=%s\n", task.task_id, task.priority, task.name);
  }

  assert(scheduler_size(heapObj) == 0);
  assert(!scheduler_next(heapObj, &task));

  printf("\nTest 5: Cancel task\n");

  assert(scheduler_add(heapObj, 201, 4, "Task A"));
  assert(scheduler_add(heapObj, 202, 1, "Task B"));
  assert(scheduler_add(heapObj, 203, 2, "Task C"));
  assert(scheduler_add(heapObj, 204, 3, "Task D"));

  assert(scheduler_cancel(heapObj, 202));
  assert(!scheduler_cancel(heapObj, 999));

  assert(scheduler_next(heapObj, &task));
  assert(task.task_id == 203);

  assert(scheduler_next(heapObj, &task));
  assert(task.task_id == 204);

  assert(scheduler_next(heapObj, &task));
  assert(task.task_id == 201);

  printf("Cancel test PASS\n");

  printf("\nTest 6: FIFO with same priority\n");

  assert(scheduler_add(heapObj, 30, 5, "First"));
  assert(scheduler_add(heapObj, 10, 5, "Second"));
  assert(scheduler_add(heapObj, 20, 5, "Third"));

  assert(scheduler_next(heapObj, &task) && task.task_id == 30);
  assert(scheduler_next(heapObj, &task) && task.task_id == 10);
  assert(scheduler_next(heapObj, &task) && task.task_id == 20);

  printf("FIFO test PASS\n");

  heap_destroy(heapObj);

  printf("\nAll tests passed!\n");
  return 0;
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   Test 1: Add tasks
   Heap array:
   [0] ID=102 Priority=1 Sequence=1 Name=Sensor
   [1] ID=104 Priority=1 Sequence=3 Name=Safety
   [2] ID=103 Priority=3 Sequence=2 Name=Logging
   [3] ID=101 Priority=3 Sequence=0 Name=Network
   [4] ID=105 Priority=2 Sequence=4 Name=Storage

   Test 2: Reject invalid insertions

   Test 3: Peek
   Next: Sensor (ID=102, Priority=1)

   Test 4: Priority + FIFO execution
   Execute: ID=102 Priority=1 Name=Sensor
   Execute: ID=104 Priority=1 Name=Safety
   Execute: ID=105 Priority=2 Name=Storage
   Execute: ID=101 Priority=3 Name=Network
   Execute: ID=103 Priority=3 Name=Logging

   Test 5: Cancel task
   Cancel test PASS

   Test 6: FIFO with same priority
   FIFO test PASS

   All tests passed!
**/
