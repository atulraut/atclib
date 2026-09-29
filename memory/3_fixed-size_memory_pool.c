/**

   Implement a fixed-size memory pool

   Date: Tue Sep 29 14:22:28 PDT 2026
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

/**
   Conceptually we have MemoryPool :

   blocks[]
   +----------+----------+----------+----------+-----+
   | block[0] | block[1] | block[2] | block[3] | ... |
   +----------+----------+----------+----------+-----+
   64 B       64 B       64 B       64 B

   Why Union : A union means the members share the same memory.
   Block
   +--------------------------------+
   |                                |
   |          same memory           |
   |                                |
   +--------------------------------+
   ^                              ^
   |                              |
   next                           data[64]

 **/

#define BLOCK_SIZE  64
#define BLOCK_COUNT 8

typedef union Block {
  union Block *next;
  unsigned char data[BLOCK_SIZE];
} Block;

typedef struct {
  Block blocks[BLOCK_COUNT];
  Block *free_list;
} MemoryPool;

void pool_init(MemoryPool *pool) {
  if (pool == NULL)
    return;

  for (int i = 0; i < BLOCK_COUNT - 1; i++)
    pool->blocks[i].next = &pool->blocks[i + 1];

  pool->blocks[BLOCK_COUNT - 1].next = NULL;
  pool->free_list = &pool->blocks[0];
}

void *pool_alloc(MemoryPool *pool) {
  if (pool == NULL || pool->free_list == NULL)
    return NULL;

  Block *block = pool->free_list;
  pool->free_list = block->next;

  return block->data;
}

void pool_free(MemoryPool *pool, void *ptr) {
  if (pool == NULL || ptr == NULL)
    return;

  Block *block = (Block *)ptr;

  block->next = pool->free_list;
  pool->free_list = block;
}

int main(void) {
  MemoryPool pool;

  pool_init(&pool);

  void *a = pool_alloc(&pool);
  void *b = pool_alloc(&pool);
  void *c = pool_alloc(&pool);

  printf("a = %p\n", a);
  printf("b = %p\n", b);
  printf("c = %p\n", c);

  pool_free(&pool, b);

  void *d = pool_alloc(&pool);

  printf("d = %p\n", d);

  return 0;
}

/**
   a = 0x16d4b2eb0
   b = 0x16d4b2ef0
   c = 0x16d4b2f30
   d = 0x16d4b2ef0
**/
