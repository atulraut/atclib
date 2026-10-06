/***
    https://leetcode.com/problems/maximum-sum-of-3-non-overlapping-subarrays/
    Hard : Maximum Sum of 3 Non-Overlapping Subarrays

    Given an integer array nums and an integer k, find three
    non-overlapping subarrays of length k with maximum sum
    and return them.

    Return the result as a list of indices representing the
    starting position of each interval (0-indexed). If there
    are multiple answers, return the lexicographically smallest one.

    Input: nums = [1,2,1,2,6,7,5,1], k = 2
    Output: [0,3,5]
    Explanation: Subarrays [1, 2], [2, 6], [7, 5] correspond
    to the starting indices [0, 3, 5].
    We could have also taken [2, 1], but an answer of [1, 3, 5]
    would be lexicographically larger.

    Input: nums = [1,2,1,2,1,2,1,2,1], k = 2
    Output: [0,2,4]

    Constraints:
    1 <= nums.length <= 2 * 104
    1 <= nums[i] < 216
    1 <= k <= floor(nums.length / 3)

    Date: 17 Oct 2021
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
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxSumOfThreeSubarrays(int* nums, int numsSize, int k, int* returnSize) {
  int i;
  int oneIdx;
  int *twoIdx;
  int *threeIdx;
  int oneSum=0,oneMax=0,twoSum=0,twoMax=0,threeSum=0,threeMax=0;

  if((nums==NULL) || (numsSize==0)) {
    *returnSize = 0;
    return NULL;
  }

  oneIdx = 0;
  twoIdx = (int*)malloc(2*sizeof(int));
  twoIdx[0] = 0;
  twoIdx[1] = k;
  threeIdx = (int*)malloc(3*sizeof(int));
  threeIdx[0] = 0;
  threeIdx[1] = k;
  threeIdx[2] = k*2;
  for(i=0;i<k;i++) {
    oneSum += nums[i];
    twoSum += nums[i+k];
    threeSum += nums[i+k*2];
  }
  oneMax = oneSum;
  twoMax = oneMax+twoSum;
  threeMax = twoMax+threeSum;

  for(i=0;i<numsSize-k*3;i++) {
    oneSum += nums[i+k] - nums[i];
    if(oneSum > oneMax) {
      oneMax = oneSum;
      oneIdx = i+1;
    }

    twoSum += nums[i+k*2] - nums[i+k];
    if((oneMax+twoSum) > twoMax) {
      twoMax = oneMax+twoSum;
      twoIdx[0] = oneIdx;
      twoIdx[1] = i+k+1;
    }

    threeSum += nums[i+k*3] - nums[i+k*2];
    if((twoMax+threeSum) > threeMax) {
      threeMax = twoMax+threeSum;
      threeIdx[0] = twoIdx[0];
      threeIdx[1] = twoIdx[1];
      threeIdx[2] = i+k*2+1;
    }
  }

  free(twoIdx);

  *returnSize = 3;
  return threeIdx;
}

int main (int argc, char **argv) {
  int *ret;
  int nums[] = {1,2,1,2,6,7,5,1};
  int k = 2;
  int numsSize = sizeof(nums)/sizeof(nums[0]);
  int returnSize;

  ret = maxSumOfThreeSubarrays(nums, numsSize, k, &returnSize);
  for (int i=0; i<returnSize; ++i)
    debug("Output = %d", ret[i]);
  return 0;
}

/**
   => ./a.out
   [main] L=116 :Output = 0
   [main] L=116 :Output = 3
   [main] L=116 :Output = 5
**/
