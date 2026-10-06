/***
    1480. Running Sum of 1d Array
    Given an array nums. We define a running sum of an array as
    runningSum[i] = sum(nums[0]…nums[i]).

    Return the running sum of nums.

    Input: nums = [1,2,3,4]
    Output: [1,3,6,10]
    Explanation: Running sum is obtained as follows: [1, 1+2, 1+2+3, 1+2+3+4].

    Input: nums = [1,1,1,1,1]
    Output: [1,2,3,4,5]
    Explanation: Running sum is obtained as follows: [1, 1+1, 1+1+1, 1+1+1+1, 1+1+1+1+1].

    Input: nums = [3,1,2,10,1]
    Output: [3,4,6,16,17]

    Constraints:
    1 <= nums.length <= 1000
    -10^6 <= nums[i] <= 10^6

    https://leetcode.com/problems/running-sum-of-1d-array/
    Date: 3 May 2021.
    San Diego, CA.
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

int* runningSum(int* nums, int numsSize, int* returnSize) {
  int j = 0;
  int runningSum = 0;
  int *size;

  size = (int*)malloc(sizeof(int) * numsSize);

  while (j < numsSize) {
    size[j] = nums[j] + runningSum;
    runningSum += nums[j];
    ++j;
  }
  returnSize[0] = numsSize;
  return size;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* runningSum2(int* nums, int numsSize, int* returnSize){
  int *ret = (int *)malloc(sizeof(int) * numsSize);
  if (NULL == ret)
    return NULL;
  int sum = nums[0];
  ret[0] = sum;
  for (int i=1; i<numsSize; ++i) {
    sum += nums[i];
    ret[i] = sum;
  }
  *returnSize = numsSize;
  return ret;
}

int main () {
  int *ret = 0;
  int arr[] = {1, 2, 3, 4};
  int numsSize = sizeof(arr)/sizeof(arr[0]);
  int returnSize;

  debug ("numsSize = %d", numsSize);
  ret = runningSum(arr, numsSize, &returnSize);
  for(int i=0; i<returnSize; i++)
    debug("Output = %d", ret[i]);
  return 0;
}

/**
   => ./a.out
   [main] L=64 :numsSize = 4
   [main] L=67 :Output = 1
   [main] L=67 :Output = 3
   [main] L=67 :Output = 6
   [main] L=67 :Output = 10
**/
