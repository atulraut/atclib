/***
    665. Non-decreasing Array

    Given an array nums with n integers, your task is to check if it
    could become non-decreasing by modifying at most one element.

    We define an array is non-decreasing if nums[i] <= nums[i + 1]
    holds for every i (0-based) such that (0 <= i <= n - 2).

    Input: nums = [4,2,3]
    Output: true
    Explanation: You could modify the first 4 to 1 to get a non-decreasing array.

    Input: nums = [4,2,1]
    Output: false
    Explanation: You can't get a non-decreasing array by modify at most one element.

    Constraints:
    n == nums.length
    1 <= n <= 104
    -105 <= nums[i] <= 105

    https://leetcode.com/problems/non-decreasing-array/

    Date: 4 May 2021.
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

bool checkPossibility(int* nums, int numsSize) {
  int numViolations = 0;

  for (int i = 1; i < numsSize; i++) {
    if (nums[i - 1] > nums[i]) {
      if (numViolations == 1) {
	return false;
      }
      numViolations++;
      if (i < 2 || nums[i - 2] <= nums[i]) {
	nums[i - 1] = nums[i];
      } else {
	nums[i] = nums[i - 1];
      }
    }
  }
  return true;
}

int main () {
  int nums[] = {4, 2, 3};
  int numsSize = 3;
  bool ret = checkPossibility(nums, numsSize);

  debug("Output = %d ", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=65 :Output = 1
**/
/**
   Complexity Analysis
    Time Complexity: O(n) considering there are nnn elements in the array
    and we process each element at most once.
    Space Complexity: O(1) since we don't use any additional space apart
    from a couple of variables for executing this algorithm.
 **/
