/***
 * Hashing Data Structure : Using Division Method
 * Hashing is an important Data Structure which is designed to use a
 * special function called the Hash function which is used to map a given
 * value with a particular key for faster access of elements. The efficiency
 *  of mapping depends of the efficiency of the hash function used.b
 *
 * Let a hash function H(x) maps the value x at the index x%10 in an Array.
 * For example if the list of values is [11,12,13,14,15] it will be stored
 * at positions {1,2,3,4,5} in the array or Hash table respectively.
 * Ref : https://www.geeksforgeeks.org/hashing-data-structure/
 * Ref : http://www.martinbroadhurst.com/hash-table.html
 * https://www.youtube.com/watch?v=KyUTuwz_b7Q&t=255s
 * Main Logic : Key == array element % array size (1024)
*/

#include <stdio.h>
#include <stdlib.h>
#include "hash_lib.h"

#define DEBUG_T 0
#define DEBUG_L 1
#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

struct table* m_createTable(int size) {
  int i;
  struct table *t = (struct table *)malloc(sizeof(struct table));
  t->sz = size;
  t->list = (struct node**)malloc(size * sizeof(struct node*));
  for (i=0; i<size; i++)
    t->list[i] = NULL;

  return t;
}

int m_getHashCode(struct table *t, int key) {
  if (key < 0)
    return -(key % t->sz);
  return (key % t->sz);
}

void m_insert (struct table *t, int key) {
  int pos = m_getHashCode (t, key);
  struct node *list = t->list[pos];
  if (NULL == list)
    debug ("list is NULL! ");
  else
    debug ("list - %p ", list);

  struct node *nn = (struct node *)malloc(sizeof(struct node));

  struct node *temp = list;

  /* Collision Detection : Check if node with matching key is already present */
  while (temp) {
    if (temp->key == key) {
#ifdef DEBUG_T
      temp->val++;
#endif
#ifdef DEBUG_L
      temp->val = key; /* As it is same as val */
      debug ("key = %d val = %d \n", key, temp->val);
      return;
#endif
    }
    debug ("key = %d val = %d \n",key, temp->val);
    temp = temp->next;
  }
#ifdef DEBUG_T
      nn->val = 1;
#endif
#ifdef DEBUG_L
      nn->val = key;
#endif
  nn->key = key;
  nn->next = list;
  t->list[pos] = nn;
  debug("key = %d val = %d \n", key, nn->val);
}

int m_lookup (struct table *t, int key) {
  int pos = m_getHashCode(t, key);
  struct node *list = t->list[pos];
  struct node *temp = list;
  while (temp) {
    if (temp->key == key) {
      return temp->val;
      return temp->val++;
    } // if ends
    temp = temp->next;
  }
  return -1;
}

/***
    [m_TestFunc] --> sz=9
    m_insert 2. key = 11 val = 11
    m_insert 2. key = 12 val = 12
    m_insert 2. key = 13 val = 13
    m_insert 2. key = 14 val = 14
    m_insert 2. key = 15 val = 15
    m_insert 0. key = 11 val = 11
    m_insert 2. key = 27 val = 27
    m_insert 0. key = 13 val = 13
    m_insert 0. key = 11 val = 11
    [m_TestFunc] --> Search Eelement
    [m_TestFunc] --> Element Found = 11
    [m_TestFunc] --> Element Found = 12
    [m_TestFunc] --> Element Found = 13
    [m_TestFunc] --> Element Found = 14
    [m_TestFunc] --> Element Found = 15
    [m_TestFunc] --> Element Found = 11
    [m_TestFunc] --> Element Found = 27
    [m_TestFunc] --> Element Found = 13
    [m_TestFunc] --> Element Found = 11
*/
