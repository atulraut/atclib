/***
 * LeetCode: Insert Delete GetRandom O(1)
 * Design a data structure that supports all following operations in average O(1) time.
 * insert(val): Inserts an item val to the set if not already present.
 * remove(val): Removes an item val from the set if present.
 * getRandom: Returns a random element from current set of elements. Each element must have the same probability of being returned.
 * Example:
 * // Init an empty set.
 * RandomizedSet randomSet = new RandomizedSet();
 * // Inserts 1 to the set. Returns true as 1 was inserted successfully.
 * randomSet.insert(1);
 * // Returns false as 2 does not exist in the set.
 * randomSet.remove(2);
 * // Inserts 2 to the set, returns true. Set now contains [1,2].
 * randomSet.insert(2);
 * // getRandom should return either 1 or 2 randomly.
 *  randomSet.getRandom();
 * // Removes 1 from the set, returns true. Set now contains [2].
 * randomSet.remove(1);
 *  // 2 was already in the set, so return false.
 *  randomSet.insert(2);
 * // Since 2 is the only number in the set, getRandom always return 2.
 * randomSet.getRandom();
 * Status: Compilatoin Error
 * Refer: https://leetcode.com/explore/featured/card/june-leetcoding-challenge/540/week-2-june-8th-june-14th/3358/
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int currentSize;
  int maxSize;
  int *arr;
} RandomizedSet;

int __randomizedSetRemove(RandomizedSet *obj, int val);

/** Initialize your data structure here. */
void resize(RandomizedSet *obj, int n) {
  obj->maxSize = n;
  int *t = (int*) malloc(sizeof(int)*n);
  memcpy(t, obj->arr, obj->currentSize*sizeof(int));
  free(obj->arr);
  obj->arr=t;

}

RandomizedSet* randomizedSetCreate() {
  RandomizedSet* t = (RandomizedSet*) malloc(sizeof(RandomizedSet));
  t->arr=(int*) malloc(sizeof(int)*4);
  t->currentSize=0;
  t->maxSize=4;
  return t;
}

/** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
int randomizedSetInsert(RandomizedSet *obj, int val) {
  int i;

  for(i = 0; i < obj->currentSize; ++i)
    if (obj->arr[i] == val)
      return -1;

  if (obj->currentSize==obj->maxSize)
    resize(obj,obj->currentSize*2);

  obj->arr[obj->currentSize] = val;
  obj->currentSize++;

  return 1;
}

/** Removes a value from the set. Returns true if the set contained the specified element. */
int __randomizedSetRemove(RandomizedSet *obj, int val) {
  int i;

  for(i = 0; i < obj->currentSize; ++i)
    if (obj->arr[i] == val) {
      for(; i<obj->currentSize-1; ++i)
        obj->arr[i]=obj->arr[i+1];
      obj->currentSize--;
      return 1;
    }

  return -1;
}

/** Get a random element from the set. */
int randomizedSetGetRandom(RandomizedSet *obj) {
  return obj->arr[rand() % obj->currentSize];
}

void randomizedSetFree(RandomizedSet *obj) {
  free(obj->arr);
  free(obj);
}

int main () {
int ret;
  /// Init an empty set.
  RandomizedSet *randomSet = randomizedSetCreate();

  // Inserts 1 to the set. Returns true as 1 was inserted successfully.
  randomizedSetInsert(randomSet, 1);

   // Returns false as 2 does not exist in the set.
   ret = __randomizedSetRemove(randomSet, 2);

   // Inserts 2 to the set, returns true. Set now contains [1,2].
   randomizedSetInsert(randomSet, 2);

   // getRandom should return either 1 or 2 randomly.
   ret = randomizedSetgetRandom(randomSet);

   // Removes 1 from the set, returns true. Set now contains [2].
   ret = __randomizedSetremove(randomSet, 1);

   // 2 was already in the set, so return false.
   ret = randomizedSetInsert(randomSet, 2);

   // Since 2 is the only number in the set, getRandom always return 2.
   ret = randomizedSetgetRandom(randomSet);

   return 0;
}

/**
 * Your RandomizedSet struct will be instantiated and called as such:
 * RandomizedSet* obj = randomizedSetCreate();
 * bool param_1 = randomizedSetInsert(obj, val);

 * bool param_2 = randomizedSetRemove_(obj, val);

 * int param_3 = randomizedSetGetRandom(obj);

 * randomizedSetFree(obj);
 */
