/*
 * Core A priority ingest queue (binary max-heap), using the interview's
 * exact prototypes:
 *
 *     int          enqueue(sensor_data *data);
 *     sensor_data *dequeue(void);
 *
 * dequeue() returns a pointer to the highest-priority message, or NULL
 * when empty. The pointer stays valid until the NEXT call to dequeue();
 * the caller must finish with (or copy) the message before calling again.
 *
 * Build & run:  gcc -Wall -Wextra -o heap_queue_ptr heap_queue_ptr.c && ./heap_queue_ptr
 *
 * Date : Sat Oct 31 14:26:08 PDT 2026
 * Folsom, CA
*/

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/* ============================ Queue ============================ */

#define CAPACITY     16
#define PAYLOAD_LEN  128

typedef struct {
  uint8_t priority;
  uint8_t payload[PAYLOAD_LEN];
} sensor_data;

typedef struct {
  sensor_data msg;
  uint32_t    seq;      /* arrival order: equal priorities stay FIFO */
} item_t;

static item_t      heap[CAPACITY];
static uint32_t    size;
static uint32_t    next_seq;
static sensor_data out_msg;   /* hand-off buffer owned by dequeue() */

/* Platform hooks. Host stubs; on target these disable/restore IRQs. */
static uint32_t irq_lock(void)          { return 0; }
static void     irq_unlock(uint32_t s)  { (void)s; }

static bool higher(const item_t *a, const item_t *b) {
  if (a->msg.priority != b->msg.priority)
    return a->msg.priority > b->msg.priority;
  return a->seq < b->seq;
}

static void swap(uint32_t i, uint32_t j) {
  item_t t = heap[i]; heap[i] = heap[j]; heap[j] = t;
}

static void sift_up(uint32_t i) {
  while (i > 0) {
    uint32_t parent = (i - 1) / 2;
    if (!higher(&heap[i], &heap[parent])) break;
    swap(i, parent);
    i = parent;
  }
}

static void sift_down(uint32_t i) {
  for (;;) {
    uint32_t l = 2 * i + 1, r = l + 1, best = i;
    if (l < size && higher(&heap[l], &heap[best])) best = l;
    if (r < size && higher(&heap[r], &heap[best])) best = r;
    if (best == i) break;
    swap(i, best);
    i = best;
  }
}

void queue_init(void) {
  size = 0;
  next_seq = 0;
}

/* Returns 0 on success, -1 if full (new message dropped). ISR-safe. */
int enqueue(sensor_data *data) {
  if (data == NULL) return -1;

  uint32_t s = irq_lock();
  if (size == CAPACITY) { irq_unlock(s); return -1; }

  heap[size].msg = *data;
  heap[size].seq = next_seq++;
  sift_up(size);
  size++;

  irq_unlock(s);
  return 0;
}

/*
 * Returns the highest-priority message, or NULL if empty.
 * The returned pointer is valid until the next dequeue() call.
 */
sensor_data *dequeue(void) {
  uint32_t s = irq_lock();
  if (size == 0) { irq_unlock(s); return NULL; }

  out_msg = heap[0].msg;        /* copy out under the lock ... */
  size--;
  heap[0] = heap[size];
  sift_down(0);

  irq_unlock(s);
  return &out_msg;              /* ... so the ISR can't touch what we return */
}

/* ===================== Core B <-> Core A link ===================== */

static volatile sensor_data shared_sram;
static volatile bool        data_ready;

static void dr_ack(void) { data_ready = false; }

void dr_isr(void) {
  sensor_data msg;
  msg.priority = shared_sram.priority;
  memcpy(msg.payload, (const void *)shared_sram.payload, PAYLOAD_LEN);
  dr_ack();
  if (enqueue(&msg) != 0)
    printf("  [ISR] queue full, dropped priority %u\n", msg.priority);
}

/* ============================ TEST ============================ */

static void core_b_send(uint8_t priority, uint8_t tag) {
  shared_sram.priority = priority;
  memset((void *)shared_sram.payload, tag, PAYLOAD_LEN);
  data_ready = true;
  dr_isr();
}

static int failures;

#define CHECK(cond, ...) do {						\
    if (cond) { printf("  PASS: " __VA_ARGS__); printf("\n"); }		\
    else      { printf("  FAIL: " __VA_ARGS__); printf("\n"); failures++; } \
  } while (0)

static void test_priority_order(void) {
  printf("Test 1: highest priority comes out first\n");
  queue_init();
  core_b_send(10, 'a');
  core_b_send(200, 'b');
  core_b_send(50, 'c');
  core_b_send(255, 'd');

  uint8_t expect[] = {255, 200, 50, 10};
  for (int i = 0; i < 4; i++) {
    sensor_data *m = dequeue();
    CHECK(m && m->priority == expect[i],
	  "dequeue #%d -> priority %u (expected %u)", i, m ? m->priority : 0, expect[i]);
  }
  CHECK(dequeue() == NULL, "returns NULL when empty");
}

static void test_fifo_within_priority(void) {
  printf("Test 2: equal priorities are FIFO\n");
  queue_init();
  core_b_send(100, '1');
  core_b_send(100, '2');
  core_b_send(100, '3');

  for (char c = '1'; c <= '3'; c++) {
    sensor_data *m = dequeue();
    CHECK(m && m->payload[0] == (uint8_t)c,
	  "dequeue -> payload tag '%c' (expected '%c')", m ? m->payload[0] : '?', c);
  }
}

static void test_payload_intact(void) {
  printf("Test 3: all 128 payload bytes survive the copy\n");
  queue_init();
  core_b_send(7, 0xAB);
  sensor_data *m = dequeue();
  bool ok = (m != NULL);
  for (int i = 0; ok && i < PAYLOAD_LEN; i++)
    if (m->payload[i] != 0xAB) ok = false;
  CHECK(ok, "payload matches");
}

static void test_full_queue(void) {
  printf("Test 4: Core B outruns Core A (queue fills, extras dropped)\n");
  queue_init();
  for (int i = 0; i < CAPACITY + 3; i++)
    core_b_send((uint8_t)i, (uint8_t)i);        /* 3 drops expected */

  int n = 0, prev = 256;
  bool ordered = true;
  sensor_data *m;
  while ((m = dequeue()) != NULL) {
    if (m->priority > prev) ordered = false;
    prev = m->priority;
    n++;
  }
  CHECK(n == CAPACITY, "drained %d messages (expected %d)", n, CAPACITY);
  CHECK(ordered, "drained in non-increasing priority order");
}

static void test_pointer_lifetime(void) {
  printf("Test 5: returned pointer stays valid while new data arrives\n");
  queue_init();
  core_b_send(9, 'y');
  sensor_data *m = dequeue();           /* caller is now holding 'y' */
  core_b_send(200, 'z');                /* ISR fires while caller still using m */
  CHECK(m && m->priority == 9 && m->payload[0] == 'y',
	"held message untouched by later enqueue");
  m = dequeue();
  CHECK(m && m->priority == 200, "next dequeue -> 200");
}

int main(void) {
  test_priority_order();
  test_fifo_within_priority();
  test_payload_intact();
  test_full_queue();
  test_pointer_lifetime();

  printf("\n%s (%d failure%s)\n",
	 failures ? "SOME TESTS FAILED" : "ALL TESTS PASSED",
	 failures, failures == 1 ? "" : "s");
  return failures ? 1 : 0;
}

/**
   Test 1: highest priority comes out first
   PASS: dequeue #0 -> priority 255 (expected 255)
   PASS: dequeue #1 -> priority 200 (expected 200)
   PASS: dequeue #2 -> priority 50 (expected 50)
   PASS: dequeue #3 -> priority 10 (expected 10)
   PASS: returns NULL when empty
   Test 2: equal priorities are FIFO
   PASS: dequeue -> payload tag '1' (expected '1')
   PASS: dequeue -> payload tag '2' (expected '2')
   PASS: dequeue -> payload tag '3' (expected '3')
   Test 3: all 128 payload bytes survive the copy
   PASS: payload matches
   Test 4: Core B outruns Core A (queue fills, extras dropped)
   [ISR] queue full, dropped priority 16
   [ISR] queue full, dropped priority 17
   [ISR] queue full, dropped priority 18
   PASS: drained 16 messages (expected 16)
   PASS: drained in non-increasing priority order
   Test 5: returned pointer stays valid while new data arrives
   PASS: held message untouched by later enqueue
   PASS: next dequeue -> 200

   ALL TESTS PASSED (0 failures)
**/
