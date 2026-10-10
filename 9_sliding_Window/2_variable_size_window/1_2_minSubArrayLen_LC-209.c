/***
    https://leetcode.com/problems/minimum-size-subarray-sum/

    LeetCode 209 — Minimum Size Subarray Sum (C)
    Pattern: Variable-size Sliding Window

    Given an array of positive integers nums and a positive
    integer target, return the minimal length of a subarray whose
    sum is greater than or equal to target.
    If there is no such subarray, return 0 instead.

    Input: target = 7, nums = [2,3,1,2,4,3]
    Output: 2
    Explanation: The subarray [4,3] has the minimal length under
    the problem constraint.

    Input: target = 4, nums = [1,4,4]
    Output: 1

    Input: target = 11, nums = [1,1,1,1,1,1,1,1]
    Output: 0

    Constraints:
    1 <= target <= 109
    1 <= nums.length <= 105
    1 <= nums[i] <= 104

    Follow up: If you have figured out the O(n) solution, try coding
    another solution of which the time complexity is O(n log(n)).

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Sat Oct 10 10:05:59 PDT 2026
    Folsom, CA.
 */

/*----------------------------------- Header --------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h> // va_arg
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */

#define debug(str,args...) printf("L=[%d][%s]->[%s] :| "str"\n",__LINE__,__FILE__, __func__, ##args)

/**
   Sliding-window approach
   Use two pointers, left and right, and a running sum.
   1. Expand the window by adding nums[right].
   2. Shrink the window while sum >= target, updating the minimum length before removing nums[left].
   3. Continue expanding until the end.
   The key difference from longest-subarray problems is that we update the answer inside the while loop.
**/
int minSubArrayLen(int target, int* nums, int numsSize) {
  int left = 0;
  int sum = 0;
  int minLen = INT_MAX;

  for (int right = 0; right < numsSize; right++) {

    // Incoming element
    sum += nums[right];

    // Shrink while window is valid
    while (sum >= target) {

      int len = right - left + 1;

      if (len < minLen)
	minLen = len;

      // Outgoing element
      sum -= nums[left];
      left++;
    }
  }

  return (minLen == INT_MAX) ? 0 : minLen;
}

/**
   Explanation:
   [4, 3] → sum = 7, length = 2
**/
void test() {
  int ret = 0;
  int target = 7;
  int nums[] = {2, 3, 1, 2, 4, 3};
  int numsSize = sizeof(nums)/sizeof(nums[0]);
  ret = minSubArrayLen(target, nums, numsSize);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   L=[69][1_2_minSubArrayLen_LC-209.c]->[test] :| Output = 2
**/
