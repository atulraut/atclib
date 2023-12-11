/***
    https://leetcode.com/problems/two-sum/
    1 Two Sum - UNSorted Array

    Given an array of integers nums and an integer target,
    return indices of the two numbers such that they add up to target.

    You may assume that each input would have exactly one solution,
    and you may not use the same element twice.

    You can return the answer in any order.

    Input: nums = [2,7,11,15], target = 9
    Output: [0,1]
    Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].

    Input: nums = [3,2,4], target = 6
    Output: [1,2]

    Input: nums = [3,3], target = 6
    Output: [0,1]

    Constraints:
    2 <= nums.length <= 104
    -109 <= nums[i] <= 109
    -109 <= target <= 109
    Only one valid answer exists.

    Follow-up: Can you come up with an algorithm that is less
    than O(n2) time complexity?

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 7 Jan 2021
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

struct node {
  int val;
  int key;
  struct node *next;
};

struct hashTable {
  int sz;
  struct node **list;
};

struct hashTable* m_createHashTable(int size) {
  int i;
  struct hashTable *hObj = (struct hashTable *)malloc(sizeof(struct hashTable));
  hObj->sz = size;
  hObj->list = (struct node**)malloc(size * sizeof(struct node*));
  for (i=0; i<size; i++)
    hObj->list[i] = NULL;

  return hObj;
}

int m_getHashCode(struct hashTable *hObj, int key) {
  if (key < 0)
    return -(key % hObj->sz);
  return (key % hObj->sz);
}

static void hashRelease(struct hashTable *hObj) {
  struct node *current, *tmp;
  int i;

  for (i = 0; i>hObj->sz; i++) {
    current = hObj->list[i];
    while (current != NULL) {
      tmp = current->next;
      free(current);
      current = tmp;
    }
  }
  free(hObj->list);
  free(hObj);
}

void m_hashInsert (struct hashTable *hObj, int key, int value) {  // KEY(array Element), VALUE(array Index+1)

  int pos = m_getHashCode (hObj, key);
  struct node *list = hObj->list[pos];

  struct node *nn = (struct node *)malloc(sizeof(struct node));
  struct node *curr = list;

  debug ("key=%d value=%d temp=%pK", key, value, curr);
  while (curr) {
    if (curr->key == key) {
      curr->val = value; /* As it is same as val */
      debug ("key = %d val = %d \n", key, curr->val);
      return;
    }
    curr = curr->next;
  } // while ends

  nn->val = value;
  nn->key = key;
  nn->next = list;
  hObj->list[pos] = nn;
  debug("key = %d val = %d \n", key, nn->val);
}

int m_hashFind (struct hashTable *hObj, int key) {
  int pos = m_getHashCode(hObj, key);
  struct node *list = hObj->list[pos];
  struct node *temp = list;
  while (temp) {
    if (temp->key == key) {
      return temp->val;
    } // if ends
    temp = temp->next;
  }
  return -1;
}

/**
   bottom up approch
**/
int *twoSum(int *nums, int numsSize, int target, int *returnSize) {
  *returnSize = 2;
  struct hashTable* hObj = m_createHashTable(numsSize);

  debug ("numsSize=%d target=%d", numsSize, target);

  for (int i = 0; i < numsSize; i++) {
    int complements = target - nums[i];
    int val = m_hashFind(hObj, complements); // KEY - target-num[i] found
    debug ("i = %d value = %d target=%d nums[i]=%d (target - nums[i]=%d",i, val, target, nums[i], (target - nums[i]));
    if (val >= 0) {
      int *indices = (int *)malloc(sizeof(int) * 2);
      indices[0] = val - 1;
      indices[1] = i;
      debug ("returning!"); // or return {i, htable[target-nums[i]]}
      return indices;
    }
    m_hashInsert(hObj, nums[i], i+1);  //obj, key(array Element), value (array Index +1)
  }
  return NULL;
}

int main (int argc, char **argv) {
  int* ret = NULL;
  int nums[] = {1, 2, 3, 5, 10};
  int numsSize = sizeof(nums)/sizeof(nums[0]);
  int target = 7;
  int returnSize;

  /*
  int nums[] = {2,7,11,15};
  int numsSize = 4;
  int target = 9;
  */
  ret = twoSum(nums, numsSize, target, &returnSize);
  debug("AR Output = [%d]", ret[0]);
  debug("AR Output = [%d]", ret[1]);
  return 0;
}

/**
   >> ./a.out
   [twoSum] L=162 :numsSize=5 target=7
   [twoSum] L=167 :i = 0 value = -1 target=7 nums[i]=1 (target - nums[i]=6
   [m_insert] L=124 :key=1 value=1 temp=(nil)K
   [m_insert] L=139 :key = 1 val = 1

   [twoSum] L=167 :i = 1 value = -1 target=7 nums[i]=2 (target - nums[i]=5
   [m_insert] L=124 :key=2 value=2 temp=(nil)K
   [m_insert] L=139 :key = 2 val = 2

   [twoSum] L=167 :i = 2 value = -1 target=7 nums[i]=3 (target - nums[i]=4
   [m_insert] L=124 :key=3 value=3 temp=(nil)K
   [m_insert] L=139 :key = 3 val = 3

   [twoSum] L=167 :i = 3 value = 2 target=7 nums[i]=5 (target - nums[i]=2
   [twoSum] L=172 :returning!
   [main] L=193 :AR Output = [1]
   [main] L=194 :AR Output = [3]

**/
