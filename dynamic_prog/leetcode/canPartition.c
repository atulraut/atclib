/***
    https://leetcode.com/problems/partition-equal-subset-sum
    Partition Equal Subset Sum

    Given a non-empty array nums containing only positive integers,
    find if the array can be partitioned into two subsets such that
    the sum of elements in both subsets is equal.

    Input: nums = [1,5,11,5]
    Output: true
    Explanation: The array can be partitioned as [1, 5, 5] and [11].

    Input: nums = [1,2,3,5]
    Output: false
    Explanation: The array cannot be partitioned into equal sum subsets.

    Constraints:

    1 <= nums.length <= 200
    1 <= nums[i] <= 100

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address canPartition.c -lm

    Date: 12/12/2021
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

bool canPartition4(int* nums, int numsSize) {
  int sum = 0;
  for(int i = 0; i < numsSize; i++)
    sum += nums[i];

  if(sum % 2 == 1)
    return false;
  sum = sum >> 1;

  bool dp[sum + 1];
  memset(dp, 0, (sum + 1) * sizeof(bool));
  dp[0] = true;

  for(int i= 1; i <= numsSize; i++)
    for(int j = sum; j >= nums[i-1]; j--)
      dp[j] = dp[j] || dp[j - nums[i - 1]];

  return dp[sum];
}

bool canPartition(int* nums, int numsSize) {
  int sum = 0;
  for(int i = 0; i < numsSize; i++)
    sum += nums[i];
  if(sum % 2 == 1)
    return false;

  sum = sum / 2;
  int arr[sum+1];
  for(int i= 0; i<= sum; i++)
    arr[i] = 0;

  arr[0] = 1;

  for(int i= 0; i< numsSize; i++)
    for(int j= sum; j>= nums[i]; j--)
      if(arr[j-nums[i]]) arr[j] = 1;

  return arr[sum];
}
/*
  bool dfs(int *nums, int n, int subSetSum, int* memo) {
  // Base Cases
  if (subSetSum == 0)
  return true;
  if (n == 0 || subSetSum < 0)
  return false;
  // check if subSetSum for given n is already computed and stored in memo
  if (memo[n][subSetSum] != nullopt) {
  return (memo[n][subSetSum] == true);
  }
  bool result = dfs(nums, n - 1, subSetSum - nums[n - 1], memo) ||
  dfs(nums, n - 1, subSetSum, memo);
  memo[n][subSetSum] = result;
  return result;
  }

  // Approach 2: Top Down Dynamic Programming - Memoization
  bool canPartition(int *nums, int numsSize) {
  int totalSum = 0;
  // find sum of all array elements
  for (int i=0; i<numsSize; ++i) {
  totalSum += nums[i];
  }
  // if totalSum is odd, it cannot be partitioned into equal sum subset
  if (totalSum % 2 != 0)
  return false;
  int subSetSum = totalSum / 2;
  int n = numsSize;

  int* memo = (int *)malloc(sizeof (int) * (subSetSum + 1,));
  //    vector<vector<optional<bool>>> memo(n + 1, vector<optional<bool>>(subSetSum + 1, nullopt));

  return dfs(nums, n - 1, subSetSum, memo);
  }
*/


/* Approach 1: Brute Force: Limit Exceeded Error */
bool dfs1(int *nums, int n, int subSetSum) {
  // Base Cases
  if (subSetSum == 0)
    return true;
  if (n == 0 || subSetSum < 0)
    return false;

  bool result = dfs1(nums, n - 1, subSetSum - nums[n - 1]) || dfs1(nums, n - 1, subSetSum);

  return result;
}

bool canPartition1(int* nums, int numsSize) {
  int totalSum = 0;
  // find sum of all array elements
  for (int i=0; i<numsSize; ++i)
    totalSum += nums[i];

  // if totalSum is odd,it cannot be partitioned into equal sum subset
  if (totalSum % 2 != 0)
    return false;

  int subSetSum = totalSum / 2;
  int n = numsSize;

  return dfs1(nums, n - 1, subSetSum);
}

int main (int argc, char **argv) {
  int ret = 0;
  int nums[] = {1, 5, 11, 5};
  int numsSize = arrsz(nums);

  ret =  canPartition4(nums, numsSize);

  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=168 :Output = 1
**/
