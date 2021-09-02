/***
    Hard: Patching Array
    Given a sorted integer array nums and an integer n, add/patch elements
    to the array such that any number in the range [1, n] inclusive can be
    formed by the sum of some elements in the array.

    Return the minimum number of patches required.

    Input: nums = [1,3], n = 6
    Output: 1
    Explanation:
    Combinations of nums are [1], [3], [1,3], which form possible sums of: 1, 3, 4.
    Now if we add/patch 2 to nums, the combinations are: [1], [2], [3], [1,3], [2,3], [1,2,3].
    Possible sums are 1, 2, 3, 4, 5, 6, which now covers the range [1, 6].
    So we only need 1 patch.

    Input: nums = [1,5,10], n = 20
    Output: 2
    Explanation: The two patches can be [2, 4].

    Input: nums = [1,2,2], n = 5
    Output: 0

    Constraints:
    1 <= nums.length <= 1000
    1 <= nums[i] <= 104
    nums is sorted in ascending order.
    1 <= n <= 231 - 1

    https://leetcode.com/problems/patching-array

    Date: 29 August 2021.
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

/***
  Here is the recipe of this greedy algorithm:
  Initialize the range [1, miss) = [1, 1) = empty
  While n is not covered yet
     if the current element nums[i] is less than or equal to miss
        extends the range to [1, miss + nums[i])
        increase i by 1
  otherwise
        patch the array with miss, extends the range to [1, miss + miss)
        increase the number of patches
  Return the number of patches
*/
int minPatches(int* nums, int numsSize, int n) {
  int ret = 0,ptr = 0;
  unsigned int range = 0,limit = n;
  while(range < limit) {
    if(ptr == numsSize || range + 1 < nums[ptr]) {
      ret ++;
      debug("(range<<1) =%u", (range << 1));
      range = (range << 1) | 1;
      debug("ret = %d range=%u", ret, range);
    } else {
      range += nums[ptr++];
      debug("ret = %d range=%u", ret, range);
    }
  }
  return ret;
}

int main (int argc, char **argv) {
  int ret = 0;
  int nums[] = {1,3};
  int n = 6;

  int numsSize = sizeof(nums) / sizeof(nums[0]);

  ret = minPatches(nums, numsSize, n);
  debug("Output = %d", ret);
  return 0;
}

/*
  Complexity Analysis :
  Time complexity : O(m+log⁡n)O(m + \log n)O(m+logn). In each iteration, we eithe
  increase the index i or we double the variable miss. The total number of increment
  for index i is mmm and the total number of doubling miss is log⁡n\log nlogn

  Space complexity : O(1)O(1)O(1). We only need three variables, patches, i and miss.
*/

/**
   [minPatches] L=71 :ret = 0 range=1
   [minPatches] L=68 :ret = 1 range=3
   [minPatches] L=71 :ret = 1 range=6
   [main] L=85 :Output = 1
**/
