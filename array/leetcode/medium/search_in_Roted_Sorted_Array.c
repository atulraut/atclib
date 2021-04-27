/***
    33. Search in Rotated Sorted Array
    https://leetcode.com/problems/search-in-rotated-sorted-array/
    There is an integer array nums sorted in ascending order
    (with distinct values).

    Prior to being passed to your function, nums is rotated
    at an unknown pivot index k (0 <= k < nums.length) such
    that the resulting array is [nums[k], nums[k+1], ..., nums[n-1],
    nums[0], nums[1], ..., nums[k-1]] (0-indexed).
    For example, [0,1,2,4,5,6,7] might be rotated at pivot
    index 3 and become [4,5,6,7,0,1,2].

    Given the array nums after the rotation and an integer
    target, return the index of target if it is in nums,
    or -1 if it is not in nums.

    Input: nums = [4,5,6,7,0,1,2], target = 0
    Output: 4

    Input: nums = [4,5,6,7,0,1,2], target = 3
    Output: -1

    Input: nums = [1], target = 0
    Output: -1

    Constraints:
    1 <= nums.length <= 5000
    -104 <= nums[i] <= 104
    All values of nums are unique.
    nums is guaranteed to be rotated at some pivot.
    -104 <= target <= 104

    Date: 27 April 2021
    San Diego, CA
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
    Optimize Binary Search.
    -----------------------
    | | | | | | | | | | | |
  Start       Mid         End
 */
int search(int* nums, int numsSize, int target) {
  int start = 0, end = numsSize - 1;

  while (start <= end) {
    int mid = start + (end - start) / 2;

    if (nums[mid] == target)
      return mid;
    else if (nums[mid] >= nums[start]) {
      if (target >= nums[start] && target < nums[mid])
	end = mid - 1;
      else
	start = mid + 1;
    }
    else {
      if (target <= nums[end] && target > nums[mid])
	start = mid + 1;
      else
	end = mid - 1;
    }
  }
  return -1;
}

int main() {
  int nums[] = {4,5,6,7,0,1,2};
  int target = 0;

  int numsSize = sizeof(nums) / sizeof(nums[0]);

  int ret = search(nums, numsSize, target);

  debug("Output = %d", ret);

  return 0;
}

/***
    => ./a.out
    [main] L=82 :Output = 4
*/

/***
    Complexity Analysis

    Time complexity: O(log⁡N)
    Space complexity: O(1)
*/
