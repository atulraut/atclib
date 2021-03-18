/***
    https://leetcode.com/problems/design-hashmap/
    Design a HashMap without using any built-in hash table libraries.

    Implement the MyHashMap class:

    MyHashMap() initializes the object with an empty map.
    void put(int key, int value) inserts a (key, value) pair into the HashMap.
    If the key already exists in the map, update the corresponding value.
    int get(int key) returns the value to which the specified key is mapped,
    or -1 if this map contains no mapping for the key.
    void remove(key) removes the key and its corresponding value if the map
    contains the mapping for the key.

    Example 1:
    Input
    ["MyHashMap", "put", "put", "get", "get", "put", "get", "remove", "get"]
    [[], [1, 1], [2, 2], [1], [3], [2, 1], [2], [2], [2]]
    Output
    [null, null, null, 1, -1, null, 1, null, -1]

    Explanation
    MyHashMap myHashMap = new MyHashMap();
    myHashMap.put(1, 1); // The map is now [[1,1]]
    myHashMap.put(2, 2); // The map is now [[1,1], [2,2]]
    myHashMap.get(1);    // return 1, The map is now [[1,1], [2,2]]
    myHashMap.get(3);    // return -1 (i.e., not found), The map is now [[1,1], [2,2]]
    myHashMap.put(2, 1); // The map is now [[1,1], [2,1]] (i.e., update the existing value)
    myHashMap.get(2);    // return 1, The map is now [[1,1], [2,1]]
    myHashMap.remove(2); // remove the mapping for 2, The map is now [[1,1]]
    myHashMap.get(2);    // return -1 (i.e., not found), The map is now [[1,1]]

    Constraints:
    0 <= key, value <= 10^6
    At most 104 calls will be made to put, get, and remove.

    Date : 18 March 2021
    San Diego, CA
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define debug(str, args...) printf("[%s] L=%d: "str" \n", __func__, __LINE__, ##args)

#define TABLE_SIZE 1000000
#define NO_MAPPING (int)-1

typedef struct {
  int *data;
} MyHashMap;

int getHashIndex(int key) {
  return key % TABLE_SIZE;
}

/***
     Initialize your data structure here.
*/
MyHashMap* myHashMapCreate() {
  // Allocate hash map object
  MyHashMap* map = (MyHashMap*)malloc(sizeof(MyHashMap));

  // Allocate hash map data
  map->data = (int *)malloc(TABLE_SIZE * sizeof(int));

  // Initialize with -1's
  memset(map->data, NO_MAPPING, TABLE_SIZE * sizeof(int));

  return map;
}

/***
     value will always be non-negative.
*/
void myHashMapPut(MyHashMap* obj, int key, int value) {
  int hash_index = getHashIndex(key);

  if (obj) {
    obj->data[hash_index] = value;
  }
}

/***
     Returns the value to which the specified key is mapped, or -1
     if this map contains no mapping for the key
*/
int myHashMapGet(MyHashMap* obj, int key) {
  int hash_index = getHashIndex(key);
  int value = NO_MAPPING;

  if (obj) {
    value = obj->data[hash_index];
  }

  //printf("key=%d\tvalue=%d\n", hash_index, value);

  return value;
}

/***
     Removes the mapping of the specified value key if this map contains
     a mapping for the key
*/
void myHashMapRemove(MyHashMap* obj, int key) {
  int hash_index = getHashIndex(key);

  if (obj) {
    obj->data[hash_index] = NO_MAPPING;
  }
}

void myHashMapFree(MyHashMap* obj) {
  if (obj) {
    // Free data array
    free(obj->data);

    // Free hash map object
    free(obj);
  }
}

/**
 * Your MyHashMap struct will be instantiated and called as such:
 * MyHashMap* obj = myHashMapCreate();
 * myHashMapPut(obj, key, value);

 * int param_2 = myHashMapGet(obj, key);

 * myHashMapRemove(obj, key);

 * myHashMapFree(obj);
 */

int main () {
  int ret;
  MyHashMap *tObj = myHashMapCreate ();
  if (NULL == tObj)
    return -1;

  myHashMapPut(tObj, 1, 1); // The map is now [[1,1]]
  myHashMapPut(tObj, 2, 2); // The map is now [[1,1], [2,2]]
  ret = myHashMapGet(tObj, 1);    // return 1, The map is now [[1,1], [2,2]]
  debug ("ret = %d", ret);
  ret = myHashMapGet(tObj, 3);    // return -1 (i.e., not found), The map is now [[1,1], [2,2]]
  debug ("ret = %d", ret);
  myHashMapPut(tObj, 2, 1); // The map is now [[1,1], [2,1]] (i.e., update the existing value)
  ret = myHashMapGet(tObj, 2);    // return 1, The map is now [[1,1], [2,1]]
  debug ("ret = %d", ret);
  myHashMapRemove(tObj, 2); // remove the mapping for 2, The map is now [[1,1]]
  ret = myHashMapGet(tObj, 2);    // return -1 (i.e., not found), The map is now [[1,1]]
  debug ("ret = %d", ret);
  return 1;
}

/**
   => ./a.out
   [main] L=128: ret = 1
   [main] L=130: ret = -1
   [main] L=133: ret = 1
   [main] L=136: ret = -1
**/
