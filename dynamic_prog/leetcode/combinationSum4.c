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

int combinationSum4(int* nums, int numsSize, int target) {
  if(target == 0) {
    return 1;
  }

  unsigned long long* dp = (unsigned long long*)calloc(target+1,sizeof(unsigned long long));
  dp[0] = 1;

  for(int i=1;i<=target;i++) {
    for(int j=0;j<numsSize;j++) {
      if(nums[j]<=i) {
	dp[i] += dp[i-nums[j]];
      }
    }
  }
  return (int)dp[target];
}

int main () {
  int ret = 0;
  int nums[] = {1, 2, 3};
  int numsSize = sizeof(nums)/sizeof(nums[0]);
  int target = 4;

  ret = combinationSum4(nums, numsSize, target);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=78 :Output = 7
**/
