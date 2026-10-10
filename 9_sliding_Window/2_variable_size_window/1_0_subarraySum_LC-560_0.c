/***
    https://leetcode.com/problems/subarray-sum-equals-k/

    560. Subarray Sum Equals K

    Given an array of integers nums and an integer k, return the total
    number of subarrays whose sum equals to k.

    A subarray is a contiguous non-empty sequence of elements within an array.

    Input: nums = [1,1,1], k = 2
    Output: 2

    Input: nums = [1,2,3], k = 3
    Output: 2

    Constraints:
    1 <= nums.length <= 2 * 104
    -1000 <= nums[i] <= 1000
    -107 <= k <= 107

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Fri Oct  9 21:26:14 PDT 2026
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

// for -ve numbesr : Prefix Sum + Hash Map is optimized approch
// Variable size window
int subArraySum(int* nums, int numsSize, int k) {
  if (k <= 0 || k > numsSize)
    return 0;
  int left = 0;
  int sum = 0;
  int count = 0;

  for (int right = 0; right < numsSize; right++) {
    sum += nums[right];  // Add Incoming

    while (sum > k && left <= right) {
      sum -= nums[left];  // Remove Outgoing
      left++;
    }
    if (sum == k)
      count++;
  }
  return count;
}

void test() {
  int ret = 0;

  int arr[] = {1, 2, 3};
  ret = subArraySum(arr, 3, 3);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   L=[51][1_0_subarraySum_LC-560_0.c]->[test] :| Output = 2
**/
