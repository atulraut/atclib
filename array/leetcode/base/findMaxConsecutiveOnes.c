/***
    Max Consecutive Ones

    Given a binary array nums, return the maximum number of consecutive 1's in the array.

    Input: nums = [1,1,0,1,1,1]
    Output: 3
    Explanation: The first two digits or the last three digits are consecutive 1s.
    The maximum number of consecutive 1s is 3.

    Input: nums = [1,0,1,1,0,1]
    Output: 2

    Constraints:
    1 <= nums.length <= 105
    nums[i] is either 0 or 1.


    https://leetcode.com/problems/max-consecutive-ones/

    Date: 29 August 2021
    Fair Oaks, CA.
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

int findMaxConsecutiveOnes(int* nums, int numsSize) {
  int count = 0;
  int max = 0;
  for(int i = 0; i < numsSize; i++) {
    if(nums[i] == 0)
      count = 0;
    else
      count ++;
    max = count > max ? count : max;
  }
  return max;
}

/*
  Max Consecutive Ones II
  Given a binary array nums, return the maximum number of consecutive 1's
  in the array if you can flip at most one 0.

  Input: nums = [1,0,1,1,0]
  Output: 4
  Explanation: Flip the first zero will get the maximum number of consecutive 1s.
  After flipping, the maximum number of consecutive 1s is 4.

  Input: nums = [1,0,1,1,0,1]
  Output: 4

  Constraints:
  1 <= nums.length <= 105
  nums[i] is either 0 or 1.

  Follow up: What if the input numbers come in one by one as an infinite stream?
  In other words, you can't store all numbers coming from the stream as it's too
  large to hold in memory. Could you solve it efficiently?

  Ref : https://leetcode.com/problems/max-consecutive-ones-ii/
*/
int findMaxConsecutiveOnesII(int* nums, int numsSize) {
  int i, count, flip, max;

  max = count = 0;
  flip = -1;
  for (i = 0 ; i < numsSize ; ++i) {
    if (nums[i]) {
      ++count;
    } else {
      if (count > max)
	max = count;
      count = i - flip;
      flip = i;
    }
  }

  return max > count ? max : count;
}

int main (int argc, char **argv) {
  int ret = 0;
  int arr[] = {1, 1, 0, 1, 1, 1};
  int nums[] = {1, 0,1, 1, 0};

  int  numsSize = sizeof(arr)/sizeof(arr[0]);
  int  numsSize2 = sizeof(nums)/sizeof(nums[0]);

  ret = findMaxConsecutiveOnes(arr, numsSize);
  debug("Output = %d", ret);

  ret = findMaxConsecutiveOnesII(nums, numsSize2);
  debug("Output = %d", ret);

  return 0;
}

/**
   => ./a.out
   [main] L=57 :Output = 3
**/
