/***
    Implement event buffer with duplicate ID updates.

    Our diagnostic system receives events from running tests.
    Each event contains a unique integer ID and a message.

    We want to retain at most N events in a MyEventBuffer.

    Your buffer must support three operations:
    1. add(id, message) — Add a new event. If the ID already exists,
       replace its message and move it to the newest position.
    2. get(id) — Return the message associated with an ID.
       Reading an event must not change its position.
    3. get_recent(k) — Return up to k most recent events, ordered
       from oldest to newest within the selected results.

    When the buffer is full and a new ID is added, evict the oldest event.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Sun Nov  1 09:54:19 PST 2026
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <pthread.h>
#include <assert.h>

#define MAX_EVENTS 100
#define MAX_MESSAGE_LEN 64
#define HASH_SIZE 257

typedef struct {
  int id;
  char message[MAX_MESSAGE_LEN];
} Event;

typedef struct Node {
  Event event;
  struct Node *prev, *next;
  struct Node *hash_next;
  struct Node *free_next;
} Node;

typedef struct {
  Node nodes[MAX_EVENTS];
  Node *buckets[HASH_SIZE];
  Node *free_list;
  Node *oldest, *newest;
  size_t capacity, count;
  pthread_mutex_t mutex;
} MyEventBuffer;

static size_t hash_id(int id) {
  uint32_t x = (uint32_t)id;
  x ^= x >> 16;
  x *= UINT32_C(0x7feb352d);
  x ^= x >> 15;
  x *= UINT32_C(0x846ca68b);
  x ^= x >> 16;
  return x % HASH_SIZE;
}
static Node *find_node(MyEventBuffer *b, int id) {
  for (Node *n = b->buckets[hash_id(id)]; n; n = n->hash_next)
    if (n->event.id == id) return n;
  return NULL;
}
static void unlink_order(MyEventBuffer *b, Node *n) {
  if (n->prev)
    n->prev->next = n->next;
  else
    b->oldest = n->next;
  if (n->next)
    n->next->prev = n->prev;
  else
    b->newest = n->prev;
  n->prev = n->next = NULL;
}

static void append_newest(MyEventBuffer *b, Node *n) {
  n->next = NULL;
  n->prev = b->newest;
  if (b->newest)
    b->newest->next = n;
  else
    b->oldest = n;
  b->newest = n;
}

static void hash_remove(MyEventBuffer *b, Node *n) {
  Node **p = &b->buckets[hash_id(n->event.id)];
  while (*p && *p != n)
    p = &(*p)->hash_next;
  assert(*p == n);
  *p = n->hash_next;
  n->hash_next = NULL;
}
static void hash_insert(MyEventBuffer *b, Node *n) {
  size_t i = hash_id(n->event.id);
  n->hash_next = b->buckets[i];
  b->buckets[i] = n;
}

bool event_buffer_init(MyEventBuffer *b, size_t capacity) {
  if (!b || capacity == 0 || capacity > MAX_EVENTS)
    return false;
  memset(b, 0, sizeof(*b));
  if (pthread_mutex_init(&b->mutex, NULL) != 0)
    return false;
  b->capacity = capacity;
  for (size_t i = 0; i < capacity; ++i) {
    b->nodes[i].free_next = b->free_list;
    b->free_list = &b->nodes[i];
  }
  return true;
}

static size_t bounded_length(const char *s) {
  size_t n = 0;
  while (n < MAX_MESSAGE_LEN && s[n] != '\0')
    ++n;
  return n;
}

bool event_buffer_add(MyEventBuffer *b, int id, const char *message) {
  if (!b || !message)
    return false;
  size_t len = bounded_length(message);
  if (len == MAX_MESSAGE_LEN)
    return false;
  pthread_mutex_lock(&b->mutex);
  Node *n = find_node(b, id);
  if (n) {
    memcpy(n->event.message, message, len + 1);
    if (n != b->newest) {
      unlink_order(b, n);
      append_newest(b, n);
    }
  } else {
    if (b->count == b->capacity) {
      n = b->oldest;
      unlink_order(b, n);
      hash_remove(b, n);
    } else {
      n = b->free_list;
      b->free_list = n->free_next;
      b->count++;
    }
    n->event.id = id;
    memcpy(n->event.message, message, len + 1);
    append_newest(b, n);
    hash_insert(b, n);
  }
  pthread_mutex_unlock(&b->mutex);
  return true;
}

bool event_buffer_get(MyEventBuffer *b, int id, char *out, size_t out_size) {
  if (!b || !out || !out_size)
    return false;

  pthread_mutex_lock(&b->mutex);
  Node *n = find_node(b, id);
  if (!n || strlen(n->event.message) + 1 > out_size) {
    pthread_mutex_unlock(&b->mutex);
    return false;
  }
  strcpy(out, n->event.message);
  pthread_mutex_unlock(&b->mutex);
  return true;
}

size_t event_buffer_get_recent(MyEventBuffer *b, size_t k, Event *out, size_t out_capacity) {
  if (!b || !out || !out_capacity || !k)
    return 0;

  pthread_mutex_lock(&b->mutex);
  size_t take = k < b->count ? k : b->count;
  if (take > out_capacity) take = out_capacity;
  Node *n = b->newest;
  for (size_t i = 1; i < take; ++i) n = n->prev;
  for (size_t i = 0; i < take; ++i) {
    out[i] = n->event;
    n = n->next;
  }

  pthread_mutex_unlock(&b->mutex);
  return take;
}
void event_buffer_destroy(MyEventBuffer *b) {
  if (b)
    pthread_mutex_destroy(&b->mutex);
}

static void *writer(void *arg) {
  MyEventBuffer *b = arg;
  for (int i = 0; i < 10000; ++i)
    assert(event_buffer_add(b, i % 50, "updated"));
  return NULL;
}

static void *reader(void *arg) {
  MyEventBuffer *b = arg;
  char message[MAX_MESSAGE_LEN];
  Event recent[10];
  for (int i = 0; i < 10000; ++i) {
    event_buffer_get(b, i % 50, message, sizeof(message));
    size_t n = event_buffer_get_recent(b, 10, recent, 10);
    assert(n <= 10);
  }
  return NULL;
}

int test(void) {
  MyEventBuffer b;
  char msg[MAX_MESSAGE_LEN];
  Event recent[3];
  assert(event_buffer_init(&b, 3));
  assert(event_buffer_add(&b, 1, "Started"));
  assert(event_buffer_add(&b, 2, "GPU detected"));
  assert(event_buffer_add(&b, 3, "Warning"));
  assert(event_buffer_add(&b, 1, "Restarted"));
  assert(event_buffer_get_recent(&b, 3, recent, 3) == 3);
  assert(recent[0].id == 2 && recent[1].id == 3 && recent[2].id == 1);
  assert(event_buffer_add(&b, 4, "Failed"));
  assert(!event_buffer_get(&b, 2, msg, sizeof(msg)));
  assert(event_buffer_get(&b, 1, msg, sizeof(msg)) && strcmp(msg, "Restarted") == 0);
  assert(event_buffer_get_recent(&b, 2, recent, 3) == 2);
  assert(recent[0].id == 1 && recent[1].id == 4);
  assert(event_buffer_get_recent(&b, 3, recent, 1) == 1 && recent[0].id == 4);
  assert(!event_buffer_add(&b, 5, NULL));
  char too_long[65]; memset(too_long, 'x', 64); too_long[64] = '\0';
  assert(!event_buffer_add(&b, 5, too_long));
  event_buffer_destroy(&b);
  assert(event_buffer_init(&b, 1));
  assert(event_buffer_add(&b, -1, "one"));
  assert(event_buffer_add(&b, -1, "two"));
  assert(event_buffer_add(&b, 0, "three"));
  assert(!event_buffer_get(&b, -1, msg, sizeof(msg)));
  event_buffer_destroy(&b);
  assert(event_buffer_init(&b, 50));
  pthread_t threads[4];
  assert(pthread_create(&threads[0], NULL, writer, &b) == 0);
  assert(pthread_create(&threads[1], NULL, writer, &b) == 0);
  assert(pthread_create(&threads[2], NULL, reader, &b) == 0);
  assert(pthread_create(&threads[3], NULL, reader, &b) == 0);
  for (int i = 0; i < 4; ++i) assert(pthread_join(threads[i], NULL) == 0);
  assert(b.count == 50);
  event_buffer_destroy(&b);
  puts("All tests passed");
  return 0;
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**

 **/
