/***
    Given an integer array nums, return the
    third distinct maximum number in this array.
    If the third maximum does not exist, return the maximum number.

    Input: nums = [3,2,1]
    Output: 1
    Explanation:
    The first distinct maximum is 3.
    The second distinct maximum is 2.
    The third distinct maximum is 1.

    Input: nums = [1,2]
    Output: 2
    Explanation:
    The first distinct maximum is 2.
    The second distinct maximum is 1.
    The third distinct maximum does not exist, so the maximum (2) is returned instead.

    Input: nums = [2,2,3,1]
    Output: 1
    Explanation:
    The first distinct maximum is 3.
    The second distinct maximum is 2 (both 2's are counted together since they have the same value).
    The third distinct maximum is 1.

    Constraints:

    1 <= nums.length <= 104
    -231 <= nums[i] <= 231 - 1

    https://leetcode.com/problems/third-maximum-number/

    Date: 10 Sept 2021
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

int thirdMax(int* nums, int numsSize)  {
  long m[3] = { LONG_MIN, LONG_MIN, LONG_MIN };
  int cnt = 0;

  for(int i = 0; i < numsSize; i++) {
    if(nums[i] == m[0] || nums[i] == m[1] || nums[i] == m[2])
      continue;
    if(nums[i] > m[0]) {
      m[2] = m[1];
      m[1] = m[0];
      m[0] = nums[i];
      cnt++;
    }else if(nums[i] > m[1]) {
      m[2] = m[1];
      m[1] = nums[i];
      cnt++;
    }else if(nums[i] > m[2]) {
      m[2] = nums[i];
      cnt++;
    }
  }
  if(cnt < 3) {
    return m[0];
  }else {
    return m[2];
  }
}

int main (int argc, char **argv) {
  int ret = 0;
  int nums[] = {3, 2, 1};
  int numsSize = sizeof(nums)/sizeof(nums[0]);

  ret = thirdMax(nums, numsSize);
  debug("Output = %d", ret);
  return 0;
}

/**

 **/
