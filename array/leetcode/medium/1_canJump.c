/***
    Jump Game:
    Given an array of non-negative integers nums, you are
    initially positioned at the first index of the array.
    Each element in the array represents your maximum jump
    length at that position.
    Determine if you are able to reach the last index.

    Input: nums = [2,3,1,1,4]
    Output: true
    Explanation: Jump 1 step from index 0 to 1, then 3 steps
    to the last index.

    Input: nums = [3,2,1,0,4]
    Output: false
    Explanation: You will always arrive at index 3 no matter what.
    Its maximum jump length is 0, which makes it impossible to
    reach the last index.

    Constraints:
    1 <= nums.length <= 3 * 104
    0 <= nums[i] <= 105

    https://leetcode.com/problems/jump-game/

    Date: 5/5/2021
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
#define min(x, y) (((x) < (y)) ? x : y)
/**
   Approach : Dynamic Programming Bottom-up
 **/

enum Index {
    GOOD, BAD, UNKNOWN
};

bool canJump(int* nums, int numsSize) {
  int *memo = (int *)malloc(sizeof(int) * numsSize);

  for (int i = 0; i < numsSize; i++) {
    memo[i] = UNKNOWN;
  }
  memo[numsSize - 1] = GOOD;

  for (int i = numsSize - 2; i >= 0; i--) {
    int furthestJump = min(i + nums[i], numsSize - 1);
    for (int j = i + 1; j <= furthestJump; j++) {
      if (memo[j] == GOOD) {
	memo[i] = GOOD;
	break;
      }
    }
  }

  return memo[0] == GOOD;
}

/**
   Approach : Greedy
 **/
bool canJump1(int* nums, int numsSize) {
  int max = 0;

  for(int i =0; i<numsSize-1 && max < numsSize; i++)   {
    max = ((i+nums[i]) > max) ? i+nums[i] : max;
    if(max < i+1)
      return false;
  }
  return true;
}

int main () {
  int ret = 0;

  int arr[] = {2,3,1,1,4};
  int sz = 5;

  ret = canJump(arr, sz);
  debug("Output = %d", ret);

  return 0;
}

/**
   => ./a.out
   [main] L=61 :Output = 1
**/
