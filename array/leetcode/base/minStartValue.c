/***
    https://leetcode.com/problems/minimum-value-to-get-positive-step-by-step-sum/
    Minimum Value to Get Positive Step by Step Sum

    Given an array of integers nums, you start with an initial
    positive value startValue.
    In each iteration, you calculate the step by step sum of
    startValue plus elements in nums (from left to right).

    Return the minimum positive value of startValue such that the
    step by step sum is never less than 1.

    Input: nums = [-3,2,-3,4,2]
    Output: 5
    Explanation: If you choose startValue = 4, in the third iteration
    your step by step sum is less than 1.
    step by step sum
    startValue = 4 | startValue = 5 | nums
    (4 -3 ) = 1  | (5 -3 ) = 2    |  -3
    (1 +2 ) = 3  | (2 +2 ) = 4    |   2
    (3 -3 ) = 0  | (4 -3 ) = 1    |  -3
    (0 +4 ) = 4  | (1 +4 ) = 5    |   4
    (4 +2 ) = 6  | (5 +2 ) = 7    |   2

    Input: nums = [1,2]
    Output: 1
    Explanation: Minimum start value should be positive.

    Input: nums = [1,-2,-3]
    Output: 5

    Constraints:
    1 <= nums.length <= 100
    -100 <= nums[i] <= 100

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 11/11/2021
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

int minStartValue(int* nums, int numsSize) {
  // Start with startValue = 1.
  int startValue = 1;

  // While we haven't found the first valid startValue
  while (true) {
    // The step-by-step total equals startValue at the beginning.
    // Use boolean parameter "isValid" to record whether the total
    // is larger than or equal to 1.
    int total = startValue;
    bool isValid = true;

    // Iterate over the array "nums".
    for (int i=0; i<numsSize; ++i) {
      // In each iteration, calculate "total"
      // plus the element "num" in the array.
      total += nums[i];

      // If "total" is less than 1, we shall try a larger startValue,
      // we mark "isValid" as "false" and break the current iteration.
      if (total < 1) {
	isValid = false;
	break;
      }
    }

    // If "isVaild" is true, meaning "total" is never less than 1 in the
    // iteration, therefore we return this "startValue". Otherwise, we
    // go ahead and try "startValue" + 1 as the new "startValue".
    if (isValid) {
      return startValue;
    } else {
      startValue += 1;
    }
  }
  return -1;
}

int main (int argc, char **argv) {
  int ret = 0;
  int arr[] = {-3,2,-3,4,2};
  int sz = sizeof(arr)/sizeof(arr[0]);

  ret = minStartValue(arr, sz);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=112 :Output = 5
**/
