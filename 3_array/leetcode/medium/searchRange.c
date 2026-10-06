/***
    Find First and Last Position of Element in Sorted Array
    Given an array of integers nums sorted in ascending order,
    find the starting and ending position of a given target value.
    If target is not found in the array, return [-1, -1].
    Follow up: Could you write an algorithm with O(log n) runtime complexity?

    Input: nums = [5,7,7,8,8,10], target = 8
    Output: [3,4]

    Input: nums = [5,7,7,8,8,10], target = 6
    Output: [-1,-1]

    Input: nums = [], target = 0
    Output: [-1,-1]

    Constraints:
    0 <= nums.length <= 105
    -109 <= nums[i] <= 109
    nums is a non-decreasing array.
    -109 <= target <= 109


    https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/

    Date: 2 May 2021.
    San Diego, CA.
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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* searchRange(int* nums, int numsSize, int target, int* returnSize) {
  int *arr;

  arr=(int*)malloc(sizeof(int)*2);
  arr[0]=arr[1]=-1;
  int i,flag=1;
  *returnSize=2;

  for(i=0; i<numsSize; i++) {
    if(flag&&nums[i] == target) {
      flag=0;
      arr[0]=i;
      arr[1]=i;
    } else if(nums[i] == target) {
      arr[1]=i;
    }
  }
  return arr;
}

int main () {
  int nums[] = {5,7,7,8,8,10};
  int target = 8;
  int returnSize;
  int numsSize = sizeof(nums) / sizeof(nums[0]);

  int* ret = searchRange(nums, numsSize, target, &returnSize);

  for (int i=0; i<returnSize; i++)
    debug("Output = %d", ret[i]);

  return 0;
}

/**
   => ./a.out
   [main] L=74 :Output = 3
   [main] L=74 :Output = 4
**/

/**
   Complexity Analysis:
   Time Complexity: O(logN) considering there are N elements in the
   array. This is because binary search takes logarithmic
   time to scan an array of NNN elements. Why? Because at each step we
   discard half of the array we are scanning and hence, we're done after
   a logarithmic number of steps. We simply perform binary search twice
   in this case.

   Space Complexity: O(1) since we only use space for a few variables
   and our result array, all of which require constant space.
**/
