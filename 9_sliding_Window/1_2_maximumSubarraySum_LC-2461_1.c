/***

    https://leetcode.com/problems/maximum-sum-of-distinct-subarrays-with-length-k/

    2461. Maximum Sum of Distinct Subarrays With Length K

    You are given an integer array nums and an integer k.
    Find the maximum subarray sum of all the subarrays of nums that meet the following conditions:

    The length of the subarray is k, and
    All the elements of the subarray are distinct.
    Return the maximum subarray sum of all the subarrays that meet the conditions.
    If no subarray meets the conditions, return 0.

    A subarray is a contiguous non-empty sequence of elements within an array.

    Input: nums = [1,5,4,2,9,9,9], k = 3
    Output: 15
    Explanation: The subarrays of nums with length 3 are:
    - [1,5,4] which meets the requirements and has a sum of 10.
    - [5,4,2] which meets the requirements and has a sum of 11.
    - [4,2,9] which meets the requirements and has a sum of 15.
    - [2,9,9] which does not meet the requirements because the element 9 is repeated.
    - [9,9,9] which does not meet the requirements because the element 9 is repeated.
    We return 15 because it is the maximum subarray sum of all the subarrays that meet the conditions

    Input: nums = [4,4,4], k = 3
    Output: 0
    Explanation: The subarrays of nums with length 3 are:
    - [4,4,4] which does not meet the requirements because the element 4 is repeated.
    We return 0 because no subarrays meet the conditions.

    Constraints:

    1 <= k <= nums.length <= 105
    1 <= nums[i] <= 105

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Thu Oct  8 16:57:29 PDT 2026
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

long long maximumSubarraySum(int* nums, int n, int k) {
  int freq[100001] = {0};
  int distinct = 0;
  long long sum = 0, maxSum = 0;

  // Step 1: Calculate first window of size k
  for (int i = 0; i < k; i++) {
    sum += nums[i];

    if (freq[nums[i]]++ == 0)
      distinct++;
  }

  if (distinct == k)
    maxSum = sum;

  // Step 2: Slide the window
  for (int i = k; i < n; i++) {

    // Add incoming
    sum += nums[i];

    if (freq[nums[i]]++ == 0)
      distinct++;

    // Remove outgoing
    sum -= nums[i - k];

    if (--freq[nums[i - k]] == 0)
      distinct--;

    // Update answer
    if (distinct == k && sum > maxSum)
      maxSum = sum;
  }

  return maxSum;
}

/**
   Time complexity: O(n)
   Space complexity: O(1) with LeetCode's bounded integer values.
**/

void test() {
  int nums[] = {1, 5, 4, 2, 9, 9, 9};
  int numsSize = 7;
  int k = 3;
  long long ret = maximumSubarraySum(nums, numsSize, k);
  debug("Output = %lld", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   L=[108][1_maximumSubarraySum_LC-2461.c]->[test] :| Output = 15
**/

/**
   When i = 0:
   nums[i] = 1;

   if (freq[1]++ == 0)
   distinct++;

   C performs these operations:
   1. Read the old value of freq[1], which is 0.
   2. Compare 0 == 0 → true.
   3. Increment freq[1] from 0 to 1.
   4. Execute distinct++.
**/
