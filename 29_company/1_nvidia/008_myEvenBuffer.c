/**
   BACKGROUND

   Our diagnostic tool receives events from running tests.
   Each event has a unique identifier and a message.

   We can retain at most N events. Implement a MyEventBuffer with:

   * add(id, message) — add an event.
   If the ID already exists, replace its message and move it to the newest position.
   If capacity is exceeded, evict the oldest event.

   * get(id) — return the message for a retained ID.
   If ID isn't present, return none.

   Notes:
   * Reading an event does not change its position.
   * Communicate your thought process.
   * Test your code.

   Example:
   buffer = MyEventBuffer(3)

   buffer.add(1, "Started")
   buffer.add(2, "GPU detected")
   buffer.add(3, "Warning")

   buffer.add(1, "Restarted")
   buffer.get_recent(3)
   → [(2, "GPU detected"), (3, "Warning"), (1, "Restarted")]

   buffer.add(4, "Failed")
   buffer.get(2)
   → None

   Date: Mon Oct 26 20:31:33 PDT 2026
   Folsom, CA
**/
/**
   Design :

   I store events in an array ordered oldest → newest, so events[0] is the eviction candidate
   and events[count-1] is the newest. add has three steps:

   Copy the message first. If malloc fails, the buffer is left untouched.
   Make room: if the ID exists, remove it, which frees the old message
   and shifts the later events down. Otherwise, if the buffer is full, evict events[0].
   Append the new event at the end. This step now runs on every path.

   get is a linear scan that never reorders anything. add and get are O(N), which is fine for a
   small diagnostic buffer.
   If N were large, I’d switch to a hash map plus a doubly linked list or ring buffer for O(1).

   For get_recent(n), I fill a caller-provided array of const Event* oldest→newest and return
   how many were written (at most min(n, count)). The pointers stay valid until the
   next add or destroy.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct {
  int id;
  char *message;
} Event;

typedef struct {
  Event *events;   /* ordered oldest -> newest */
  int capacity;
  int count;
} EventBuffer;

void event_buffer_init(EventBuffer *buffer, int capacity) {
  buffer->capacity = capacity > 0 ? capacity : 0;
  buffer->count = 0;
  buffer->events = buffer->capacity ? calloc(buffer->capacity, sizeof(Event)) : NULL;
  if (!buffer->events)
    buffer->capacity = 0;
}

static int find_index(const EventBuffer *b, int id) {
  for (int i = 0; i < b->count; ++i)
    if (b->events[i].id == id)
      return i;
  return -1;
}

void event_buffer_add(EventBuffer *buffer, int event_id, const char *message) {
  if (!buffer || !buffer->events || !message)
    return;

  char *copy = malloc(strlen(message) + 1);   /* allocate first: on failure, no change */
  if (!copy)
    return;
  strcpy(copy, message);

  int pos = find_index(buffer, event_id);
  if (pos != -1) {
    /* duplicate: drop old entry, will re-append as newest */
    free(buffer->events[pos].message);
    memmove(&buffer->events[pos], &buffer->events[pos + 1], (buffer->count - pos - 1) * sizeof(Event));
    buffer->count--;
  } else if (buffer->count == buffer->capacity) {
    /* full: evict oldest */
    free(buffer->events[0].message);
    memmove(&buffer->events[0], &buffer->events[1], (buffer->count - 1) * sizeof(Event));
    buffer->count--;
  }

  /* always append as newest */
  buffer->events[buffer->count].id = event_id;
  buffer->events[buffer->count].message = copy;
  buffer->count++;
}

/* Returns NULL if the ID is absent. Does not change ordering. */
const char *event_buffer_get(const EventBuffer *buffer, int event_id) {
  if (!buffer || !buffer->events)
    return NULL;
  int pos = find_index(buffer, event_id);
  return pos == -1 ? NULL : buffer->events[pos].message;
}

/* Fills out[] with up to n most recent events, ordered oldest -> newest.
   out must have room for n pointers. Returns number written.
   Pointers are valid until the next add/destroy. */
int event_buffer_get_recent(const EventBuffer *buffer, int n, const Event **out) {
  if (!buffer || !buffer->events || !out || n <= 0)
    return 0;
  int k = n < buffer->count ? n : buffer->count;
  int start = buffer->count - k;
  for (int i = 0; i < k; ++i)
    out[i] = &buffer->events[start + i];
  return k;
}

void event_buffer_destroy(EventBuffer *buffer) {
  if (!buffer) return;
  for (int i = 0; i < buffer->count; ++i)
    free(buffer->events[i].message);
  free(buffer->events);
  buffer->events = NULL;
  buffer->count = buffer->capacity = 0;
}

/* ---------- tests ---------- */
static void check_recent(const EventBuffer *b, int n, const int *ids, const char **msgs, int expected) {
  const Event *out[8];
  int k = event_buffer_get_recent(b, n, out);
  assert(k == expected);
  for (int i = 0; i < k; ++i) {
    assert(out[i]->id == ids[i]);
    assert(strcmp(out[i]->message, msgs[i]) == 0);
  }
}

int main(void) {
  EventBuffer b;

  /* Example from the spec */
  event_buffer_init(&b, 3);
  event_buffer_add(&b, 1, "Started");
  event_buffer_add(&b, 2, "GPU detected");
  event_buffer_add(&b, 3, "Warning");
  event_buffer_add(&b, 1, "Restarted");               /* replace + move to newest */
  check_recent(&b, 3, (int[]){2, 3, 1}, (const char *[]){"GPU detected", "Warning", "Restarted"}, 3);

  assert(strcmp(event_buffer_get(&b, 3), "Warning") == 0);   /* get doesn't reorder */
  check_recent(&b, 3, (int[]){2, 3, 1}, (const char *[]){"GPU detected", "Warning", "Restarted"}, 3);

  event_buffer_add(&b, 4, "Failed");                  /* evicts oldest (2) */
  assert(event_buffer_get(&b, 2) == NULL);
  check_recent(&b, 3, (int[]){3, 1, 4},
	       (const char *[]){"Warning", "Restarted", "Failed"}, 3);
  check_recent(&b, 2, (int[]){1, 4},
	       (const char *[]){"Restarted", "Failed"}, 2);  /* n < count */
  check_recent(&b, 8, (int[]){3, 1, 4},
	       (const char *[]){"Warning", "Restarted", "Failed"}, 3); /* n > count */
  event_buffer_destroy(&b);

  /* Your original scenario: expect [2 GPU Detected], [1 Warning] */
  event_buffer_init(&b, 3);
  event_buffer_add(&b, 1, "Started");
  event_buffer_add(&b, 2, "GPU Detected");
  event_buffer_add(&b, 1, "Warning");
  printf("Recent events\n");
  for (int i = 0; i < b.count; i++)
    printf("->[%d]-[%s]\n", b.events[i].id, b.events[i].message);
  event_buffer_destroy(&b);

  /* Edge: capacity 1 */
  event_buffer_init(&b, 1);
  event_buffer_add(&b, 1, "a");
  event_buffer_add(&b, 2, "b");
  assert(event_buffer_get(&b, 1) == NULL && strcmp(event_buffer_get(&b, 2), "b") == 0);
  event_buffer_add(&b, 2, "c");                       /* replace in a full buffer: no eviction */
  assert(strcmp(event_buffer_get(&b, 2), "c") == 0 && b.count == 1);
  event_buffer_destroy(&b);

  /* Edge: capacity 0 / invalid */
  event_buffer_init(&b, 0);
  event_buffer_add(&b, 1, "x");
  assert(event_buffer_get(&b, 1) == NULL);
  event_buffer_destroy(&b);

  puts("All tests passed");
  return 0;
}
