/***
    https://leetcode.com/problems/arithmetic-slices/
    Arithmetic Slices

    An integer array is called arithmetic if it consists
    of at least three elements and if the difference between
    any two consecutive elements is the same.

    For example, [1,3,5,7,9], [7,7,7,7], and [3,-1,-5,-9] are arithmetic sequences.
    Given an integer array nums, return the number of arithmetic subarrays of nums.

    A subarray is a contiguous subsequence of the array.

    Input: nums = [1,2,3,4]
    Output: 3
    Explanation: We have 3 arithmetic slices in nums: [1, 2, 3], [2, 3, 4] and [1,2,3,4] itself.

    Input: nums = [1]
    Output: 0

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Wed Mar  2 22:12:59 PST 2022

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

// Dynamic Programming
int numberOfArithmeticSlices(int* nums, int numsSize) {
  int* dp = (int *) calloc (numsSize, sizeof(int));
  int sum = 0;
  for (int i = 2; i < numsSize; i++) {
    if (nums[i] - nums[i - 1] == nums[i -1] - nums[i - 2]) {
      dp[i] = 1 + dp[i - 1];
      printf ("i=%d sum = %d dp[i] = %d\n",i, sum, dp[i]);
      sum += dp[i];
    }
  }
  return sum;
}

// Approach 1: Brute Force
int numberOfArithmeticSlices_(int* nums, int numsSize) {
  int count = 0;
  for (int s = 0; s < numsSize - 2; s++) {
    int d = nums[s + 1] - nums[s];
    for (int e = s + 2; e < numsSize; e++) {
      int i = 0;
      for (i = s + 1; i <= e; i++)
	if (nums[i] - nums[i - 1] != d)
	  break;
      if (i > e)
	count++;
    }
  }
  return count;
}

void test() {
  int ret = 0;
  int nums[] = {1, 2, 3, 4};
  int numsSize = 4;
  ret = numberOfArithmeticSlices(nums, numsSize);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   i=2 sum = 0 dp[i] = 1
   i=3 sum = 1 dp[i] = 2
   [test] L=90 :Output = 3
**/
