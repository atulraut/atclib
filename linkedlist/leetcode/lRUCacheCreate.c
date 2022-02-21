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

    Date: Mon Feb 21 08:47:35 PST 2022
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
#define atsizeof(object) (char *)(&object+1) - (char*)(&object)
#define arrsz(x)  (sizeof(x) / sizeof((x)[0]))
#define max(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a > _b ? _a : _b; })
#define min(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/
#define MAX_KEYS 10001

typedef struct node_t_ {
  int key;
  int value;
  struct node_t_ *prev;
  struct node_t_ *next;
} node_t;

typedef struct {
  // input
  int capacity;           // LRU capacity

  // DLL - LRU order
  node_t *head;           // always points to the most recently used entry (last to be evicted)
  node_t *tail;           // always points to the least recently used entry (first to be evicted)

  //DT - LRU presence
  int size;               // LRU usage
  node_t *node[MAX_KEYS]; // direct table is faster and cheaper than hash since MAX CAPACITY is 3000
  node_t *nodes;          // allocated LRU entries
} LRUCache;

LRUCache* lRUCacheCreate(int capacity) {
  LRUCache *obj;

  if ((obj = calloc(1, sizeof(LRUCache))) != NULL) {                  // successfully allocated object
    if ((obj->nodes = calloc(capacity, sizeof(node_t))) == NULL) {  // if unable to allocate entries
      free(obj);                                                  // free object
      return NULL;                                                // cache create call fails
    }
    obj->capacity = capacity;                                       // set capacity to capacity
  }
  return obj;                                                         // return allocated object
}

void list_add(LRUCache* obj, node_t *node)
{
  node->next = obj->head;                                             // node's next points to head node
  node->prev = NULL;                                                  // node's prev points to NULL
  if (obj->head == NULL) {                                            // if DLL is emtpy
    obj->tail = node;                                               // tail now points to the new node
  } else {
    obj->head->prev = node;                                         // otherwise, head node's prev points to new
  }
  obj->head = node;                                                   // and head now points to node
}

void list_remove(LRUCache* obj, node_t *node)
{
  if (node == obj->tail) {                                            // if we are removing tail node
    obj->tail = node->prev;                                         // tail now points to node's prev
  } else {
    node->next->prev = node->prev;                                  // node's next's prev points to node's prev
  }
  if (node == obj->head) {                                            // if we are removing head node
    obj->head = node->next;                                         // head now points to node's next
  } else {
    node->prev->next = node->next;                                  // node's prev's next points to node's next
  }
}

int lRUCacheGet(LRUCache* obj, int key) {
  node_t* node = obj->node[key];                                      // get node from direct table
  if (node == NULL) {                                                 // key is not in LRU
    return -1;                                                      // return -1
  }
  list_remove(obj, node);                                             // remove node from LRU
  list_add(obj, node);                                                // put it back at the head
  return node->value;                                                 // return value associated with key
}

void lRUCachePut(LRUCache* obj, int key, int value) {
  node_t* node = obj->node[key];                                      // get node from direct table
  if (node == NULL) {                                                 // key is not in LRU
    if (obj->size == obj->capacity) {                               // and LRU is full
      node = obj->node[obj->tail->key];                           // recycle oldest entry
      obj->node[obj->tail->key] = NULL;                           // remove key from cache
      list_remove(obj, obj->tail);                                // remove tail node
    } else {
      node = &obj->nodes[obj->size++];                            // allocate a new entry
    }
    obj->node[key] = node;                                          // add key to cache
  } else {
    list_remove(obj, node);                                     // remove node from list
  }
  node->key = key;                                                // set node key
  node->value = value;                                            // set node value
  list_add(obj, node);                                            // add node back at the head
}

void lRUCacheFree(LRUCache* obj) {
  free(obj->nodes);
  free(obj);
}

/**
 * Your LRUCache struct will be instantiated and called as such:
 * struct LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);
 * lRUCachePut(obj, key, value);
 * lRUCacheFree(obj);
 */

void test() {
  int ret = 0;
  LRUCache* lRUCache = lRUCacheCreate(2);
  lRUCachePut(lRUCache, 1, 1); // cache is {1=1}
  lRUCachePut(lRUCache, 2, 2); // cache is {1=1, 2=2}
  ret = lRUCacheGet(lRUCache, 1);    // return 1
  debug("Output = %d", ret);
  lRUCachePut(lRUCache, 3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
  ret = lRUCacheGet(lRUCache, 2);    // returns -1 (not found)
  debug("Output = %d", ret);
  lRUCachePut(lRUCache, 4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
  ret = lRUCacheGet(lRUCache, 1);    // return -1 (not found)
  debug("Output = %d", ret);
  ret = lRUCacheGet(lRUCache, 3);    // return 3
  debug("Output = %d", ret);
  ret = lRUCacheGet(lRUCache, 4);    // return 4
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [test] L=185 :Output = 1
   [test] L=188 :Output = -1
   [test] L=191 :Output = -1
   [test] L=193 :Output = 3
   [test] L=195 :Output = 4
**/
