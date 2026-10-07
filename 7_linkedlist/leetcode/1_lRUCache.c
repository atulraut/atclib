/***
    https://leetcode.com/problems/lru-cache
    LRU Cache

    Design a data structure that follows the constraints
    of a Least Recently Used (LRU) cache.

    Implement the LRUCache class:

    LRUCache(int capacity) Initialize the LRU cache with positive
    size capacity.
    int get(int key) Return the value of the key if the key
    exists, otherwise return -1.
    void put(int key, int value) Update the value of the key if
    the key exists. Otherwise, add the key-value pair to the cache.
    If the number of keys exceeds the capacity from this operation,
    evict the least recently used key.
    The functions get and put must each run in O(1) average time complexity.

    Input
    ["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
    [[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
    Output
    [null, null, null, 1, null, -1, null, -1, 3, 4]

    Explanation
    LRUCache lRUCache = new LRUCache(2);
    lRUCache.put(1, 1); // cache is {1=1}
    lRUCache.put(2, 2); // cache is {1=1, 2=2}
    lRUCache.get(1);    // return 1
    lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
    lRUCache.get(2);    // returns -1 (not found)
    lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
    lRUCache.get(1);    // return -1 (not found)
    lRUCache.get(3);    // return 3
    lRUCache.get(4);    // return 4

    Constraints:
    1 <= capacity <= 3000
    0 <= key <= 104
    0 <= value <= 105
    At most 2 * 105 calls will be made to get and put.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address lRUCacheCreate.c -lm

    Date: Wed Oct  7 06:22:42 PDT 2026
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

#define HASH_SIZE 1009

typedef struct Node {
  int key;
  int value;

  /* LRU doubly linked list */
  struct Node *prev;
  struct Node *next;

  /* Hash bucket linked list */
  struct Node *hnext;
} Node;

typedef struct {
  int capacity;
  int size;

  /* LRU list */
  Node *head;    // MRU
  Node *tail;    // LRU

  /* Hash table */
  Node *table[HASH_SIZE];
} LRUCache;

/*--------------------------------------------------
 * Hash function
 *--------------------------------------------------*/
static unsigned int hash_key(int key) {
  return ((unsigned int)key) % HASH_SIZE;
}

/*--------------------------------------------------
 * Search hash table
 * Average O(1)
 *--------------------------------------------------*/
static Node *hash_find(LRUCache *cache, int key) {
  unsigned int index = hash_key(key);

  Node *cur = cache->table[index];

  while (cur != NULL) {
    if (cur->key == key)
      return cur;

    cur = cur->hnext;
  }

  return NULL;
}

/*--------------------------------------------------
 * Insert node into hash table
 *--------------------------------------------------*/
static void hash_insert(LRUCache *cache, Node *node) {
  unsigned int index = hash_key(node->key);

  node->hnext = cache->table[index];
  cache->table[index] = node;
}

/*--------------------------------------------------
 * Remove node from hash table
 *--------------------------------------------------*/
static void hash_remove(LRUCache *cache, Node *node) {
  unsigned int index = hash_key(node->key);

  Node **cur = &cache->table[index];

  while (*cur != NULL) {

    if (*cur == node) {
      *cur = node->hnext;
      node->hnext = NULL;
      return;
    }

    cur = &(*cur)->hnext;
  }
}

/*--------------------------------------------------
 * Remove from LRU doubly linked list
 *--------------------------------------------------*/
static void list_remove(LRUCache *cache, Node *node) {
  if (node->prev)
    node->prev->next = node->next;
  else
    cache->head = node->next;

  if (node->next)
    node->next->prev = node->prev;
  else
    cache->tail = node->prev;

  node->prev = NULL;
  node->next = NULL;
}

/*--------------------------------------------------
 * Add node at HEAD = MRU
 *--------------------------------------------------*/
static void list_add_head(LRUCache *cache, Node *node) {
  node->prev = NULL;
  node->next = cache->head;

  if (cache->head)
    cache->head->prev = node;
  else
    cache->tail = node;

  cache->head = node;
}

/*--------------------------------------------------
 * Create LRU
 *--------------------------------------------------*/
LRUCache *lRUCacheCreate(int capacity) {
  if (capacity <= 0)
    return NULL;

  LRUCache *cache = calloc(1, sizeof(*cache));

  if (!cache)
    return NULL;

  cache->capacity = capacity;

  return cache;
}

/*--------------------------------------------------
 * GET
 *--------------------------------------------------*/
int lRUCacheGet(LRUCache *cache, int key) {
  Node *node = hash_find(cache, key);

  if (!node)
    return -1;
  /*
   * Node was accessed.
   * Move it to HEAD => MRU.
   */
  list_remove(cache, node);
  list_add_head(cache, node);

  return node->value;
}

/*--------------------------------------------------
 * PUT
 *--------------------------------------------------*/
void lRUCachePut(LRUCache *cache, int key, int value) {
  Node *node = hash_find(cache, key);

  /*
   * CASE 1:
   * Key already exists.
   */
  if (node) {
    node->value = value;

    /* Make it MRU */
    list_remove(cache, node);
    list_add_head(cache, node);

    return;
  }

  /*
   * CASE 2:
   * Cache full.
   * Evict LRU = tail.
   */
  if (cache->size == cache->capacity) {
    Node *victim = cache->tail;

    /* Remove from hash table */
    hash_remove(cache, victim);
    /* Remove from LRU list */
    list_remove(cache, victim);
    free(victim);
    cache->size--;
  }

  /*
   * Create new cache entry.
   */
  node = malloc(sizeof(*node));
  if (!node)
    return;

  node->key = key;
  node->value = value;

  node->prev = NULL;
  node->next = NULL;
  node->hnext = NULL;

  /* Add to hash table */
  hash_insert(cache, node);
  /* Add as MRU */
  list_add_head(cache, node);

  cache->size++;
}

/*--------------------------------------------------
 * Free cache
 *--------------------------------------------------*/
void lRUCacheFree(LRUCache *cache) {
  if (!cache)
    return;

  Node *cur = cache->head;

  while (cur) {
    Node *next = cur->next;
    free(cur);
    cur = next;
  }
  free(cache);
}

/*--------------------------------------------------
 * Debug helper
 *--------------------------------------------------*/
void print_cache(LRUCache *cache) {
  Node *cur = cache->head;

  printf("MRU -> ");

  while (cur) {
    printf("[%d:%d] ", cur->key, cur->value);
    cur = cur->next;
  }
  printf("<- LRU\n");
}


int main(void) {
  LRUCache *cache = lRUCacheCreate(2);

  lRUCachePut(cache, 1, 10);
  lRUCachePut(cache, 2, 20);

  print_cache(cache);
  // MRU -> [2:20] [1:10] <- LRU

  printf("get(1) = %d\n", lRUCacheGet(cache, 1));

  print_cache(cache);
  // MRU -> [1:10] [2:20] <- LRU

  /*
   * Cache is full.
   * 2 is LRU, so 2 gets evicted.
   */
  lRUCachePut(cache, 3, 30);

  print_cache(cache);
  // MRU -> [3:30] [1:10] <- LRU

  printf("get(2) = %d\n", lRUCacheGet(cache, 2));
  // -1

  printf("get(3) = %d\n", lRUCacheGet(cache, 3));
  // 30

  print_cache(cache);
  lRUCacheFree(cache);

  return 0;
}

/**
   MRU -> [2:20] [1:10] <- LRU
   get(1) = 10
   MRU -> [1:10] [2:20] <- LRU
   MRU -> [3:30] [1:10] <- LRU
   get(2) = -1
   get(3) = 30
   MRU -> [3:30] [1:10] <- LRU
**/
