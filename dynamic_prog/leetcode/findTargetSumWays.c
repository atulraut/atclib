/***
    494. Target Sum Medium
    https://leetcode.com/problems/target-sum/

    You are given an integer array nums and an integer target.
    You want to build an expression out of nums by adding one of
    the symbols '+' and '-' before each integer in nums and then
    concatenate all the integers.

    For example, if nums = [2, 1], you can add a '+' before 2 and
    a '-' before 1 and concatenate them to build the expression "+2-1".

    Return the number of different expressions that you can build,
    which evaluates to target.

    Input: nums = [1,1,1,1,1], target = 3
    Output: 5
    Explanation: There are 5 ways to assign symbols to make the sum of nums be target 3.
    -1 + 1 + 1 + 1 + 1 = 3
    +1 - 1 + 1 + 1 + 1 = 3
    +1 + 1 - 1 + 1 + 1 = 3
    +1 + 1 + 1 - 1 + 1 = 3
    +1 + 1 + 1 + 1 - 1 = 3

    Input: nums = [1], target = 1
    Output: 1

    Constraints:
    1 <= nums.length <= 20
    0 <= nums[i] <= 1000
    0 <= sum(nums[i]) <= 1000
    -1000 <= target <= 1000

    Date: 9 June 2021.
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

int findTargetSumWays(int* nums, int numsSize, int target) {
    int i, sum, ret;
    int **dp = (int **)malloc(sizeof(int *) * numsSize);

    for (i = 0; i < numsSize; i++) {
        dp[i] = (int *)malloc(sizeof(int) * 2001);
        memset(dp[i], 0, sizeof(int) * 2001);
    }

    dp[0][nums[0] + 1000] = 1;
    dp[0][-nums[0] + 1000] += 1;

    for (i = 1; i < numsSize; i++) {
        for (sum = -1000; sum <= 1000; sum++) {
            if (dp[i - 1][sum + 1000] > 0) {
                dp[i][sum + nums[i] + 1000] += dp[i - 1][sum + 1000];
                dp[i][sum - nums[i] + 1000] += dp[i - 1][sum + 1000];
            }
        }
    }

    ret = dp[numsSize - 1][target + 1000];

    for (i = 0; i < numsSize; i++) {
        free(dp[i]);
    }
    free(dp);

    return ret;
}

int main () {
  int ret = 0;

  int num[] = {1, 1, 1, 1, 1};
  int numsSize = sizeof(num)/sizeof(num[0]);
  int target = 3;

  ret = findTargetSumWays(num, numsSize, target);

  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=91 :Output = 5
**/
