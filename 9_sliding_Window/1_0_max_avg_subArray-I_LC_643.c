/***

    https://leetcode.com/problems/maximum-average-subarray-i/description/

    643. Maximum Average Subarray I

    You are given an integer array nums consisting of n elements, and an integer k.

    Find a contiguous subarray whose length is equal to k that has the maximum
    average value and return this value. Any answer with a calculation error
    less than 10-5 will be accepted.

    Input: nums = [1,12,-5,-6,50,3], k = 4
    Output: 12.75000
    Explanation: Maximum average is (12 - 5 - 6 + 50) / 4 = 51 / 4 = 12.75

    Input: nums = [5], k = 1
    Output: 5.00000

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Wed Oct  7 16:41:26 PDT 2026
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

#define max(a, b) ({__typeof__(a) _a = (a); __typeof__(b) _b = (b); _a > _b ? _a : _b;})

/**
   T(n) = O(n)
   S(n) = O(1)
 **/

double findMaxAverage(int* nums, int n, int k) {
  if(k <=0 || k>n)
    return INT_MIN;

  double current_sum = 0;
  // Step 1: Calculate first windows
  for (int i=0; i<k; ++i)
    current_sum += nums[i];

  double maxSum = current_sum;
  // Step 2: Slide the window
  for (int i=k; i<n; ++i) {
    current_sum += nums[i];   // Add incoming/current element
    current_sum -= nums[i-k]; // Remove outgoing/first element i.e.when i=4,k=4:  4=4 == 0 i.e. nums[0]
    if(current_sum > maxSum)
      maxSum = current_sum;
  }

  return ((double)maxSum/(double)k);
}

// Brute Force O(n^2)
double findMaxAverage_Bforce(int* nums, int n, int k) {

  if(nums == NULL || k <= 0 || k > n)
    return 0.0;

  long long max_sum = LLONG_MIN;

  for (int i=0; i<=n-k; ++i) {
    long long sum = 0; // Reset for each window

    for (int j=i; j<i+k; j++) {
      sum += nums[j];
      if (sum > max_sum) {
	max_sum = sum;
      }
    }
  }
  return ((double)max_sum/(double)k);
}

void test() {
  int nums[] = {1,12,-5,-6,50,3};
  int numsSize = 6;
  int k = 4;

  double ret1 = findMaxAverage(nums, numsSize, k);
  debug("Output = %f", ret1);
  double ret2 = findMaxAverage_Bforce(nums, numsSize, k);
  debug("Output = %f", ret2);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   L=[81][9_sliding_Window/1_max_avg_subArray-I_LC_643.c]->[test] :| Output = 12.750000
   L=[83][9_sliding_Window/1_max_avg_subArray-I_LC_643.c]->[test] :| Output = 12.750000
**/
