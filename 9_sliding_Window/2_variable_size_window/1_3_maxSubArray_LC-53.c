/***

    https://leetcode.com/problems/maximum-subarray/

    53. Maximum Subarray

    Given an integer array nums, find the subarray with the largest sum, and return its sum.

    Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
    Output: 6
    Explanation: The subarray [4,-1,2,1] has the largest sum 6.

    Input: nums = [1]
    Output: 1
    Explanation: The subarray [1] has the largest sum 1.

    Input: nums = [5,4,-1,7,8]
    Output: 23
    Explanation: The subarray [5,4,-1,7,8] has the largest sum 23.
 
    Constraints:
    1 <= nums.length <= 105
    -104 <= nums[i] <= 104

    Follow up: If you have figured out the O(n) solution, try coding another solution
    using the divide and conquer approach, which is more subtle.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Fri Oct  9 22:06:01 PDT 2026
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

int maxSubArray(int* nums, int numsSize) {
  int current_sum = 0;
  int maxSum = INT_MIN;
  int left = 0;

  for (int right = 0; right < numsSize; right++) {

    // Add incoming
    current_sum += nums[right];

    // Update maximum
    if (current_sum > maxSum)
      maxSum = current_sum;

    // Discard negative window
    if (current_sum < 0) {
      current_sum = 0;
      left = right + 1;
    }
  }

  return maxSum;
}

void test() {
  int ret = 0;
  int arr[] = {5, 4, -1, 7, 8};
  ret = maxSubArray(arr, 5);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   L=[77][1_4_maxSubArray_LC-53.c]->[test] :| Output = 23
**/
