/***
    Top K Frequent Elements

    Given an integer array nums and an integer k, return the k
    most frequent elements. You may return the answer in any order.

    Input: nums = [1,1,1,2,2,3], k = 2
    Output: [1,2]

    Input: nums = [1], k = 1
    Output: [1]

    Constraints:
    1 <= nums.length <= 105
    k is in the range [1, the number of unique elements in the array].
    It is guaranteed that the answer is unique.

    Follow up: Your algorithm's time complexity must be better than O(n log n), where n is the array's size.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    https://www.youtube.com/watch?v=Wh3A29psE_Y&t=252s

    Date: Sat Mar 12 13:40:10 PST 2022
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
#define max(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a > _b ? _a : _b; })
#define min(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

/***
    1. Build HashMap: "Element --> its Frequency
*/
struct hashmap {
  int key;
  int val;
  int size;
  //  struct hashmap **buf;
};

struct hashmap* systab[NASH];

enum hash_ops_type {
  HASH_SEARCH = 1,
  HASH_INSERT = 2
} has_ops;

struct hashmap* m_init(struct hashmap* obj, int size) {
  memset((void *)obj, 0, sizeof(struct hashmap));
  // obj->buf = (struct hashmap *)malloc(sizeof(struct hashmap) * size);
  // memset(obj, 0, sizeof(struct hashmap));
  obj->size = size;
  return obj;
}

int get_hash(struct hashmap* obj, int val) {
  return (val % obj->size);
}

struct hashmap* lookup(struct hashmap* obj, int val, int isCreate) {
  struct hashmap* thisObj =  NULL;
  int key = (obj, val);
  // first lookup
  thisObj = systab[key];
  if (NULL == thisObj) {
    thisObj = (struct hashmap*)malloc(sizeof(struct hashmap));
    thisObj->key = key;
    thisObj->val = 1;
    systab[key] = thisObj;
  } else {
    thisObj = systab[key];
    thisObj->val += 1;
  }
  return thisObj;
}
/***
     2. Build Heap of K most frequest elements
*/

/***
     3. Build an output array
*/

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* topKFrequent(int* nums, int numsSize, int k, int* returnSize) {
  debug ("size = %d",  numsSize);
  int *result = NULL;
  struct hashmap obj;
  /* 1. Build HashMap: "Element --> its Frequency " */
  struct hashmap* thisObj = m_init(&obj, numsSize);
  for (int i=0; i<numsSize; ++i) {
    thisObj = lookup(thisObj, nums[i], 0);
   debug("val = %d Freq :thisObj = %d", nums[i], thisObj->val);
  }
  /* 2. Build Heap of K most frequest elements */

  /* 3. Build an output array */
  return result;
}

void test() {
  int nums[] = {1, 1, 1, 2, 2, 3};
  int k = 2;
  int *ret;
  int numsSize = sizeof(nums)/sizeof(nums[0]);
  int returnSize;

  ret = topKFrequent(nums, numsSize, k, &returnSize);
  for (int i=0; i<returnSize; ++i)
    debug("Output = %d", ret[i]);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**

 **/
