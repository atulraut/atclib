/***
    Find Minimum in Rotated Sorted Array
    Suppose an array of length n sorted in ascending order
    is rotated between 1 and n times. For example, the
    array nums = [0,1,2,4,5,6,7] might become:

    [4,5,6,7,0,1,2] if it was rotated 4 times.
    [0,1,2,4,5,6,7] if it was rotated 7 times.
    Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]]
    1 time results in the array [a[n-1], a[0], a[1], a[2], ..., a[n-2]].

    Given the sorted rotated array nums of unique elements,
    return the minimum element of this array.

    You must write an algorithm that runs in O(log n) time.

    Input: nums = [3,4,5,1,2]
    Output: 1
    Explanation: The original array was [1,2,3,4,5] rotated 3 times.

    Input: nums = [4,5,6,7,0,1,2]
    Output: 0
    Explanation: The original array was [0,1,2,4,5,6,7] and
    it was rotated 4 times.

    Input: nums = [11,13,15,17]
    Output: 11
    Explanation: The original array was [11,13,15,17] and it
    was rotated 4 times.

    Constraints:
    n == nums.length
    1 <= n <= 5000
    -5000 <= nums[i] <= 5000
    All the integers of nums are unique.
    nums is sorted and rotated between 1 and n times.

    https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/

    Date: 3 Sept 2021
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

int findMin(int* nums, int numsSize) {
  int low = 0;
  int high = numsSize - 1;

  while (low < high) {
    int mid = (low + high) / 2;
    if (nums[mid] < nums[high]) {
      high = mid;
    } else if (nums[mid] > nums[high]) {
      low = mid + 1;
    }
  }
  return nums[low];
}

int main (int argc, char **argv) {
  int ret = 0;

  int nums[] = {3, 4, 5, 1, 2};
  int numsSize = sizeof(nums)/sizeof(nums[0]);

  ret = findMin(nums, numsSize);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=79 :Output = 1
**/
