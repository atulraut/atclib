/***
    Medium: 377. Combination Sum IV
    https://leetcode.com/problems/combination-sum-iv/

    Given an array of distinct integers nums and a target
    integer target, return the number of possible combinations
    that add up to target.

    The answer is guaranteed to fit in a 32-bit integer.

    Input: nums = [1,2,3], target = 4
    Output: 7
    Explanation:
    The possible combination ways are:
    (1, 1, 1, 1)
    (1, 1, 2)
    (1, 2, 1)
    (1, 3)
    (2, 1, 1)
    (2, 2)
    (3, 1)
    Note that different sequences are counted as different combinations.

    Input: nums = [9], target = 3
    Output: 0

    Constraints:
    1 <= nums.length <= 200
    1 <= nums[i] <= 1000
    All the elements of nums are unique.
    1 <= target <= 1000

    Follow up: What if negative numbers are allowed in the given array?
    How does it change the problem? What limitation we need to add
    to the question to allow negative numbers?

    Status - Pending
    https://www.youtube.com/watch?v=oBt53YbR9Kk&list=LL&index=35&t=7s
    1:15:00
    Date: 5 June 2021, 6AM.
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

bool __canSum(int* nums, int numsSize, int targetSum, int *dp) {
  debug ("target = %d dp=%d", targetSum ,dp[targetSum]);
  if (dp[targetSum] == targetSum)
    return !dp[targetSum]; // NOT requied '!' Needs fix here
  if (targetSum == 0)
    return true;
  if (targetSum < 0)
    return false;

  for(int i=1; i<numsSize; i++) {
    int remainder = targetSum - nums[i];
    debug ("i = %d, nums[%d]=%d remainder=%d", i, i, nums[i], remainder);
    if (__canSum(nums, numsSize, remainder, dp) == true) {
      debug("Awesome!");
      dp[remainder] = true;
      return true;
    }
  }
  debug ("Reached!");
  dp[targetSum] = false;
  return false;
}

bool canSum(int* nums, int numsSize, int target) {
  int *memo = (int *)calloc(target+numsSize, sizeof(int));
  bool ret = __canSum(nums, numsSize, target, memo);
  return ret;
}

int combinationSum4(int* nums, int numsSize, int target) {
    unsigned int *dp = malloc(sizeof(int) * (target+1));
    memset(dp, 0, sizeof(int) * (target+1));
    int i;
    dp[0] = 1;
    for(i = 1; i <= target; i++){
        int j;
        for(j = 0; j < numsSize; j++){
            if(i >= nums[j]){
                dp[i] = dp[i] + dp[i-nums[j]];
            }
        }
    }
    return dp[target];
}

void test() {
  bool ret = 0;
  int nums[] = {5, 3, 4, 7};  // true
  int nums2[] = {2, 3, 15};    // true
  int nums3[] = {7, 14};        // false
  int numsSize = sizeof(nums)/sizeof(nums[0]);
  int target = 700;  // true
  int target2 = 8;    // true
  int target3  = 300;  // false
  debug("Sz = %d", numsSize);
  ret = canSum(nums, numsSize, target);
  debug("Output = %d", ret);
}

void test_leetCode() {
    bool ret = 0;
  int nums[] = {5, 3, 4, 7};  // true
  int nums2[] = {2, 3, 15};    // true
  int nums3[] = {7, 14};        // false
  int numsSize = sizeof(nums)/sizeof(nums[0]);
  int target = 700;  // true
  int target2 = 8;    // true
  int target3  = 300;  // false
  debug("Sz = %d", numsSize);
  ret = combinationSum4(nums, numsSize, target);
  debug("Output = %d", ret);
}

int main () {
  //  test();
  test_leetCode();
  return 0;
}

/**
   [main] L=78 :Output = 7
**/

/**
   [test_leetCode] L=124 :Sz = 4
   [test_leetCode] L=126 :Output = 1
**/
