/***
    https://leetcode.com/problems/two-sum/
    Two Sum

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

#define SIZE 50000

/* Optimal */
int hash(int key) {
  int r = key % SIZE;
  return r < 0 ? r + SIZE : r;
}

void insert(int *keys, int *values, int key, int value) {
  int index = hash(key);

  while (values[index]) {
    index = (index + 1) % SIZE;
  }

  keys[index] = key;
  values[index] = value;
}

int search(int *keys, int *values, int key) {
  int index = hash(key);

  while (values[index]) {
    if (keys[index] == key) {
      return values[index];
    }

    index = (index + 1) % SIZE;
  }

  return 0;
}

int *twoSum(int *nums, int numsSize, int target, int *returnSize) {
  *returnSize = 2;
  int keys[SIZE];
  int values[SIZE] = {0};

  for (int i = 0; i < numsSize; i++) {
    int complements = target - nums[i];
    int value = search(keys, values, complements);
    debug ("value = %d", value);
    if (value) {
      int *indices = (int *)malloc(sizeof(int) * 2);
      indices[0] = value - 1;
      indices[1] = i;
      return indices;
    }

    insert(keys, values, nums[i], i + 1);
  }

  return NULL;
}

int* twoSum_(int* nums, int numsSize, int target, int* returnSize) {
  int i = 0, j = 0, breakflag = 0;
  int* result = NULL;
  *returnSize = 2;

  for (int i = 0; i < (numsSize - 1); i++) {
    for (int j = (i+1); j < numsSize; j++) {
      if (target == (nums[i] + nums[j])) {
	result = (int*)malloc(sizeof(int) * (*returnSize));
	result[0] = i;
	result[1] = j;
	breakflag = 1;
	break;
      }
    }
    if (breakflag == 1)
      break;
  }
  return result;
}

int main (int argc, char **argv) {
  int* ret;
  int nums1[] = {3, 2, 4};
  int numsSize1 = 3;
  int target1 = 6;
  int returnSize;

  int nums[] = {2,7,11,15};
  int numsSize = 4;
  int target = 9;
  ret = twoSum(nums, numsSize, target, &returnSize);
  debug("Output = %d", ret[0]);
  debug("Output = %d", ret[1]);
  return 0;
}

/**
   => ./a.out
   [twoSum] L=75 :value = 0
   [twoSum] L=75 :value = 1
   [main] L=100 :Output = 0
   [main] L=101 :Output = 1
**/
