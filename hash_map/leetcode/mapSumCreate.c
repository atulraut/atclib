/***
    Medium: Map Sum Pairs
    https://leetcode.com/problems/map-sum-pairs/

    Implement the MapSum class:

    MapSum() Initializes the MapSum object.
    void insert(String key, int val) Inserts the key-val pair into
    the map.
    If the key already existed, the original key-value pair will
    be overridden to the new one.
    int sum(string prefix) Returns the sum of all the pairs' value
    whose key starts with the prefix.

    Example 1:

    Input
    ["MapSum", "insert", "sum", "insert", "sum"]
    [[], ["apple", 3], ["ap"], ["app", 2], ["ap"]]
    Output
    [null, null, 3, null, 5]

    Explanation
    MapSum mapSum = new MapSum();
    mapSum.insert("apple", 3);
    mapSum.sum("ap");           // return 3 (apple = 3)
    mapSum.insert("app", 2);
    mapSum.sum("ap");           // return 5 (apple + app = 3 + 2 = 5)

    Constraints:
    1 <= key.length, prefix.length <= 50
    key and prefix consist of only lowercase English letters.
    1 <= val <= 1000
    At most 50 calls will be made to insert and sum.

    Date: 31 July 2021
    Fair Oaks, CA.
*/

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

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

int strcompare(char* a,char *b) {
  int alen=strlen(a);
  int blen=strlen(b);

  debug("alen = %d  blen = %d", alen, blen);
  if(alen != blen) {
    return 0;
  }

  while(*a!='\0') {
    if((*a) != (*b)) {
      return 0;
    }
    a++;
    b++;
  }
  return 1;
}

int strcomparesum(char* a,char *b) {
  int alen=strlen(a);
  int blen=strlen(b);

  debug("alen = %d  blen = %d", alen, blen);
  if(alen < blen) {
    return 0;
  }

  while(*b != '\0') {
    if((*a) != (*b)) {
      return 0;
    }
    a++;
    b++;
  }
  return 1;
}

typedef struct {
  char **strings;
  int *key;
  int count;
} MapSum;

/** Initialize your data structure here. */
MapSum* mapSumCreate() {
  MapSum* obj =(MapSum*)malloc(sizeof(MapSum));
  obj->count = 0;
  obj->strings = NULL;
  obj->key = NULL;
  return obj;
}

void mapSumInsert(MapSum* obj, char* key, int val) {
  int i=0;
  debug ("i = %d obj->count = %d", i, obj->count);
  while(i < obj->count) {
    if(strcompare(obj->strings[i], key)) {
      obj->key[i]=val;
      debug("Returning - %s", obj->strings[i]);
      return ;
    }
    i++;
  }
  obj->count++;
  debug ("i = %d obj->count = %d",i, obj->count);

  obj->strings = (char**)realloc(obj->strings,sizeof(char*)*(obj->count));
  obj->key = (int*)realloc(obj->key,sizeof(int)*(obj->count));
  obj->strings[obj->count-1] = key;
  obj->key[obj->count-1] = val;
}

int mapSumSum(MapSum* obj, char* prefix) {
  int sum = 0;
  int i = 0;

  debug ("i = %d obj->count = %d",i, obj->count);
  while(i < obj->count) {
    debug ("obj->strings[i] = %s Prefix_ = %s", obj->strings[i], prefix);
    if(strcomparesum(obj->strings[i], prefix)) {
      debug ("i = %d sum = %d obj->key[i]=%d", i, sum, obj->key[i]);
      sum = sum + obj->key[i];
      debug ("i = %d sum = %d", i, sum);
    }
    i++;
  }
  return sum;
}

void mapSumFree(MapSum* obj) {
  free(obj);
}

/**
 * Your MapSum struct will be instantiated and called as such:
 * struct MapSum* obj = mapSumCreate();
 * mapSumInsert(obj, key, val);
 * int param_2 = mapSumSum(obj, prefix);
 * mapSumFree(obj);
 */

int main () {
  int ret = 0;

  MapSum *mapSum = mapSumCreate();
  mapSumInsert(mapSum, "apple", 3);
  ret = mapSumSum(mapSum, "ap");           // return 3 (apple = 3)
  debug("Output = %d", ret);
  mapSumInsert(mapSum, "app", 2);
  ret = mapSumSum(mapSum, "ap");           // return 5 (apple + app = 3 + 2 = 5)

  debug("Output = %d", ret);
  return 0;
}

/**
   Hashmap : Intuition and Algorithm

   We can remember the answer for all possible prefixes in a HashMap score.
   When we get a new (key, val) pair, we update every prefix of key appropriately:
   each prefix will be changed by delta = val - map[key], where map is the
   previous associated value of key (zero if undefined.)

   Complexity Analysis :
   Time Complexity: Every insert operation is O(K2)O(K^2)O(K2), where K
   is the length of the key, as KKK strings are made of an average length
   of K. Every sum operation is O(1).

   Space Complexity: The space used by map and score is linear in the size
   of all input key and val values combined.
**/

/**
   => ./a.out
   [mapSumInsert] L=108 :i = 0 obj->count = 0
   [mapSumInsert] L=118 :i = 0 obj->count = 1
   [mapSumSum] L=130 :i = 0 obj->count = 1
   [mapSumSum] L=132 :obj->strings[i] = apple Prefix_ = ap
   [strcomparesum] L=76 :alen = 5  blen = 2
   [mapSumSum] L=134 :i = 0 sum = 0 obj->key[i]=3
   [mapSumSum] L=136 :i = 0 sum = 3
   [main] L=161 :Output = 3
   [mapSumInsert] L=108 :i = 0 obj->count = 1
   [strcompare] L=57 :alen = 5  blen = 3
   [mapSumInsert] L=118 :i = 1 obj->count = 2
   [mapSumSum] L=130 :i = 0 obj->count = 2
   [mapSumSum] L=132 :obj->strings[i] = apple Prefix_ = ap
   [strcomparesum] L=76 :alen = 5  blen = 2
   [mapSumSum] L=134 :i = 0 sum = 0 obj->key[i]=3
   [mapSumSum] L=136 :i = 0 sum = 3
   [mapSumSum] L=132 :obj->strings[i] = app Prefix_ = ap
   [strcomparesum] L=76 :alen = 3  blen = 2
   [mapSumSum] L=134 :i = 1 sum = 3 obj->key[i]=2
   [mapSumSum] L=136 :i = 1 sum = 5
   [main] L=165 :Output = 5
**/
