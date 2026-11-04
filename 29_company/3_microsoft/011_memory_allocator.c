/***
    Implement a Memory Allocator in C — Hard

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Tue Nov  3 19:39:23 PST 2026
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
#include <stddef.h>
#include <string.h>

#define POOL_BYTES (64u * 1024u)
#define ALIGNMENT _Alignof(max_align_t)

/* Metadata stored before each allocation. */
typedef struct Block {
  size_t size;       // Total block size, including header
  size_t prev_size;  // Previous physical block's size

  struct Block *prev_free;
  struct Block *next_free;

  bool is_free;
} Block;

/* Round header size up to required alignment. */
#define HEADER_BYTES						\
  (((sizeof(Block) + ALIGNMENT - 1) / ALIGNMENT) * ALIGNMENT)

#define MIN_BLOCK_BYTES (HEADER_BYTES + ALIGNMENT)

typedef struct Allocator {
  unsigned char *begin;
  unsigned char *end;
  Block *free_head;
} Allocator;

/* Safely round allocation size up to alignment. */
static bool align_up_size(size_t n, size_t *out) {
  size_t padding = (ALIGNMENT - n % ALIGNMENT) % ALIGNMENT;

  if (n > SIZE_MAX - padding)
    return false;

  *out = n + padding;
  return true;
}

/* Find the next block in physical memory. */
static Block *next_physical(const Allocator *a, const Block *b) {
  unsigned char *next = (unsigned char *)b + b->size;

  return next < a->end ? (Block *)next : NULL;
}

/* Remove a block from the free list. O(1). */
static void remove_free(Allocator *a, Block *b) {
  if (b->prev_free)
    b->prev_free->next_free = b->next_free;
  else
    a->free_head = b->next_free;

  if (b->next_free)
    b->next_free->prev_free = b->prev_free;

  b->prev_free = NULL;
  b->next_free = NULL;
}

/* Insert a block at the free-list head. O(1). */
static void insert_free(Allocator *a, Block *b) {
  b->is_free = true;
  b->prev_free = NULL;
  b->next_free = a->free_head;

  if (a->free_head)
    a->free_head->prev_free = b;

  a->free_head = b;
}

/* Initialize allocator using caller-supplied memory. */
bool allocator_init(Allocator *a,
                    void *memory,
                    size_t bytes)
{
  if (!a || !memory || (uintptr_t)memory % ALIGNMENT != 0)
    return false;

  bytes -= bytes % ALIGNMENT;

  if (bytes < MIN_BLOCK_BYTES)
    return false;

  a->begin = (unsigned char *)memory;
  a->end = a->begin + bytes;
  a->free_head = (Block *)a->begin;

  /* Initially the entire pool is one free block. */
  Block *first = a->free_head;
  first->size = bytes;
  first->prev_size = 0;
  first->prev_free = NULL;
  first->next_free = NULL;
  first->is_free = true;

  return true;
}

/* Allocate aligned memory using first-fit. */
void *allocator_alloc(Allocator *a, size_t bytes)
{
  if (!a || !a->begin || bytes == 0)
    return NULL;

  size_t payload;

  if (!align_up_size(bytes, &payload) ||
      payload > SIZE_MAX - HEADER_BYTES)
    return NULL;

  size_t needed = HEADER_BYTES + payload;

  /* Search the free list for a large enough block. */
  for (Block *b = a->free_head;
       b != NULL;
       b = b->next_free) {

    if (b->size < needed)
      continue;

    remove_free(a, b);

    size_t remainder = b->size - needed;

    /* Split only if remainder can be reused. */
    if (remainder >= MIN_BLOCK_BYTES) {

      b->size = needed;

      Block *tail = (Block *)((unsigned char *)b + needed);

      tail->size = remainder;
      tail->prev_size = needed;
      tail->prev_free = NULL;
      tail->next_free = NULL;
      tail->is_free = true;

      /* Update physical neighbor's metadata. */
      Block *after = next_physical(a, tail);

      if (after)
	after->prev_size = remainder;

      insert_free(a, tail);
    }

    /* Otherwise consume the entire block. */
    b->is_free = false;

    return (unsigned char *)b + HEADER_BYTES;
  }

  return NULL;
}

/* Free memory and merge physically adjacent free blocks. */
void allocator_free(Allocator *a, void *ptr) {
  if (!ptr)
    return;

  /*
   * Contract: ptr must refer to a live allocation
   * previously returned by this allocator.
   */
  Block *b = (Block *)((unsigned char *)ptr - HEADER_BYTES);

  /* Step 1: Merge with the next physical block. */
  Block *next = next_physical(a, b);

  if (next && next->is_free) {
    remove_free(a, next);
    b->size += next->size;
  }

  /* Step 2: Merge with the previous physical block. */
  if (b->prev_size != 0) {

    Block *prev =
      (Block *)((unsigned char *)b - b->prev_size);

    if (prev->is_free) {
      remove_free(a, prev);
      prev->size += b->size;
      b = prev;
    }
  }

  /* Step 3: Repair next block's prev_size. */
  Block *after = next_physical(a, b);

  if (after)
    after->prev_size = b->size;

  /* Step 4: Add merged block to free list. */
  insert_free(a, b);
}

int test(void) {
  static _Alignas(max_align_t)
    unsigned char pool[POOL_BYTES];

  Allocator a = {0};

  assert(allocator_init(&a, pool, sizeof(pool)));

  void *x = allocator_alloc(&a, 13);
  void *y = allocator_alloc(&a, 200);
  void *z = allocator_alloc(&a, 20);

  assert(x && y && z);

  /* Check alignment. */
  assert((uintptr_t)x % ALIGNMENT == 0);
  assert((uintptr_t)y % ALIGNMENT == 0);
  assert((uintptr_t)z % ALIGNMENT == 0);

  memset(x, 0xAB, 13);
  memset(y, 0xCD, 200);
  memset(z, 0xEF, 20);

  /* Verify reuse of a freed block. */
  allocator_free(&a, y);

  void *reused = allocator_alloc(&a, 16);
  assert(reused == y);

  allocator_free(&a, reused);
  allocator_free(&a, x);
  allocator_free(&a, z);

  /* All blocks should coalesce into one. */
  void *all =
    allocator_alloc(&a, POOL_BYTES - HEADER_BYTES);

  assert(all);
  assert(allocator_alloc(&a, 1) == NULL);

  allocator_free(&a, all);

  /* Edge cases. */
  assert(allocator_alloc(&a, SIZE_MAX) == NULL);
  assert(allocator_alloc(&a, 0) == NULL);

  puts("All allocator tests passed.");
  return 0;
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**

 **/
