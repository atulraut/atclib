/***
    https://leetcode.com/problems/concatenation-of-array/
    Concatenation of Array

    Given an integer array nums of length n, you want to
    create an array ans of length 2n where
    ans[i] == nums[i] and ans[i + n] == nums[i] for 0 <= i < n (0-indexed).

    Specifically, ans is the concatenation of two nums arrays.
    Return the array ans.

    Input: nums = [1,2,1]
    Output: [1,2,1,1,2,1]
    Explanation: The array ans is formed as follows:
    - ans = [nums[0],nums[1],nums[2],nums[0],nums[1],nums[2]]
    - ans = [1,2,1,1,2,1]

    Input: nums = [1,3,2,1]
    Output: [1,3,2,1,1,3,2,1]
    Explanation: The array ans is formed as follows:
    - ans = [nums[0],nums[1],nums[2],nums[3],nums[0],nums[1],nums[2],nums[3]]
    - ans = [1,3,2,1,1,3,2,1]

    Constraints:
    n == nums.length
    1 <= n <= 1000
    1 <= nums[i] <= 1000

    Date: )ct 18, 2021
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

/**
 * Optimize
 */
int* getConcatenation(int* nums, int size_of_nums, int* size_of_ans) {
  int* ans = (int*)malloc(sizeof(int) * size_of_nums * 2);
  *size_of_ans = size_of_nums * 2;

  for(int i = 0; i < size_of_nums; i++) {
    ans[i] = nums[i];
    ans[(i + size_of_nums)] = ans[i];
  }

  return ans;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* __getConcatenation(int* nums, int numsSize, int* returnSize){
  int newSz = 2 * numsSize;
  int* newArr = (int *)calloc(sizeof(int), newSz);
  *returnSize = newSz;

  for (int i=0,j=0; i<newSz; ++i,++j) {
    if(j == newSz/2)
      j=0;
    newArr[i] = nums[j];
  }
  return newArr;
}

int main (int argc, char **argv) {
  int* ret;
  int nums[] = {1,2,1};
  int size_of_nums = sizeof(nums)/sizeof(nums[0]);
  int size_of_ans;

  ret = getConcatenation(nums, size_of_nums, &size_of_ans);
  for (int i=0; i<size_of_ans; ++i)
    debug("Output = %d", ret[i]);
  return 0;
}

/**
   => ./a.out
   [main] L=85 :Output = 1
   [main] L=85 :Output = 2
   [main] L=85 :Output = 1
   [main] L=85 :Output = 1
   [main] L=85 :Output = 2
   [main] L=85 :Output = 1
**/
