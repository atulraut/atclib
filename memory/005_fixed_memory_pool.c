/* Fixed-size memory pool: C11, no heap allocation, O(1) alloc/free. */
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define POOL_BLOCK_SIZE 64u
#define POOL_CAPACITY   128u

/* A union guarantees that every block is suitably aligned for ordinary C types. */
typedef union PoolBlock PoolBlock;
union PoolBlock {
    PoolBlock *next;
    max_align_t alignment;
    unsigned char bytes[POOL_BLOCK_SIZE];
};

typedef struct {
    PoolBlock blocks[POOL_CAPACITY];
    PoolBlock *free_list;
    bool in_use[POOL_CAPACITY];
    size_t used;
} MemoryPool;

void pool_init(MemoryPool *pool)
{
    assert(pool != NULL);
    pool->used = 0;
    pool->free_list = &pool->blocks[0];

    for (size_t i = 0; i < POOL_CAPACITY; ++i) {
        pool->in_use[i] = false;
        pool->blocks[i].next =
            (i + 1 < POOL_CAPACITY) ? &pool->blocks[i + 1] : NULL;
    }
}

/* Returns NULL when the pool is exhausted. */
void *pool_alloc(MemoryPool *pool)
{
    if (pool == NULL || pool->free_list == NULL)
        return NULL;

    PoolBlock *block = pool->free_list;
    pool->free_list = block->next;
    size_t index = (size_t)(block - pool->blocks);
    pool->in_use[index] = true;
    ++pool->used;
    return block->bytes;
}

/* Returns false for a pointer outside the pool or a double free. */
bool pool_free(MemoryPool *pool, void *ptr)
{
    if (pool == NULL || ptr == NULL)
        return false;

    uintptr_t start = (uintptr_t)&pool->blocks[0];
    uintptr_t address = (uintptr_t)ptr;
    uintptr_t offset = address - start;

    /* Unsigned subtraction also rejects addresses below 'start'. */
    if (address < start || offset >= sizeof(pool->blocks) ||
        offset % sizeof(PoolBlock) != 0)
        return false;

    size_t index = (size_t)(offset / sizeof(PoolBlock));
    if (!pool->in_use[index])
        return false;

    pool->in_use[index] = false;
    PoolBlock *block = &pool->blocks[index];
    block->next = pool->free_list;
    pool->free_list = block;
    --pool->used;
    return true;
}

size_t pool_available(const MemoryPool *pool)
{
    return pool == NULL ? 0 : POOL_CAPACITY - pool->used;
}

int main(void)
{
    MemoryPool pool;
    pool_init(&pool);

    void *allocated[POOL_CAPACITY];
    for (size_t i = 0; i < POOL_CAPACITY; ++i) {
        allocated[i] = pool_alloc(&pool);
        assert(allocated[i] != NULL);
    }

    assert(pool_available(&pool) == 0);
    assert(pool_alloc(&pool) == NULL); /* Exhaustion */

    for (size_t i = 0; i < POOL_CAPACITY; ++i)
        assert(pool_free(&pool, allocated[i]));

    assert(!pool_free(&pool, allocated[0])); /* Double-free rejection */
    assert(pool_available(&pool) == POOL_CAPACITY);

    void *reused = pool_alloc(&pool);
    assert(reused != NULL);
    assert(pool_free(&pool, reused));

    puts("All memory pool tests passed.");
    return 0;
}
