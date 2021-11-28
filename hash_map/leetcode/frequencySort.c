/***
    https://leetcode.com/problems/sort-array-by-increasing-frequency/
    Sort Array by Increasing Frequency

    Given an array of integers nums, sort the array in increasing
    order based on the frequency of the values. If multiple
    values have the same frequency, sort them in decreasing order.

    Return the sorted array.

    Input: nums = [1,1,2,2,2,3]
    Output: [3,1,1,2,2,2]
    Explanation: '3' has a frequency of 1, '1' has a frequency of 2, and '2' has a frequency of 3.

    Input: nums = [2,3,1,3,2]
    Output: [1,3,3,2,2]
    Explanation: '2' and '3' both have a frequency of 2, so they are sorted in decreasing order.

    Input: nums = [-1,1,-6,4,5,-6,1,4,1]
    Output: [5,-1,4,4,-6,-6,1,1,1]

    Constraints:
    1 <= nums.length <= 100
    -100 <= nums[i] <= 100

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 27 Nov 2021
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

static int hash[201];

static int cmp(const int *a, const int *b) {
  int count_a = hash[*a + 100];
  int count_b = hash[*b + 100];
  return (count_a != count_b) ? (count_a - count_b) : *b - *a;
}

int* frequencySort2(int* nums, int numsSize, int* returnSize){
  int i;

  memset(hash, 0, sizeof(hash));
  for(i=0; i<numsSize; i++)
    hash[nums[i] + 100]++;

  qsort(nums, numsSize, sizeof(int), cmp);
  *returnSize = numsSize;

  return nums;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* frequencySort(int* nums, int numsSize, int* returnSize) {
  int* ans = malloc(sizeof(int)*numsSize);
  int size = 0;
  int rec[201] = {};
  *returnSize = numsSize;
  for(int i = 0; i < numsSize; i++) {
    rec[nums[i]+100]++;
  }
  for(int i = 1; i <= numsSize; i++) {
    for(int j = 200; j >= 0; j--) {
      if(rec[j] == i) {
	for(int k = 0; k < i; k++) {
	  ans[size++] = j-100;
	}
      }
    }
    if(size == numsSize)
      break;
  }
  return ans;
}

int main (int argc, char **argv) {
  int *ret;
  int nums[] = {1,1,2,2,2,3};
  int numsSize = 6;
  int returnSize;

  ret = frequencySort(nums, numsSize, &returnSize);

  for (int i=0; i<returnSize; ++i)
    debug("Output = %d", ret[i]);
  return 0;
}

/**
   => ./a.out
   [main] L=93 :Output = 3
   [main] L=93 :Output = 1
   [main] L=93 :Output = 1
   [main] L=93 :Output = 2
   [main] L=93 :Output = 2
   [main] L=93 :Output = 2
**/
