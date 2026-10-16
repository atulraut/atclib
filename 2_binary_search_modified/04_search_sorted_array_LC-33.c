/***
    https://leetcode.com/problems/search-in-rotated-sorted-array/description/

    33. Search in Rotated Sorted Array

    There is an integer array nums sorted in ascending order (with distinct values).

    Prior to being passed to your function, nums is possibly left
    rotated at an unknown index k (1 <= k < nums.length) such that
    the resulting array is
    [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed).
    For example, [0,1,2,4,5,6,7] might be left rotated by 3 indices and become [4,5,6,7,0,1,2].

    Given the array nums after the possible rotation and an integer target,
    return the index of target if it is in nums, or -1 if it is not in nums.

    You must write an algorithm with O(log n) runtime complexity.

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
    nums is an ascending array that is possibly rotated.
    -104 <= target <= 104

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Thu Oct 15 07:52:59 PDT 2026
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

int search(int* nums, int numsSize, int target) {
  int start = 0;
  int end   = numsSize - 1;
  while (start < end) {
    int mid = start + (end - start) / 2;
    /* if I am (nums[mid]) in the wrong zone, move towards boundary */
    if (target <= nums[end] && nums[mid] > nums[end]) {
      start = mid + 1; /* I am in the green zone, target in brown zone */
    } else if (target > nums[end] && nums[mid] <= nums[end]) {
      end = mid - 1; /* Target is in green zone, I am in brown zone */
    } else if (nums[mid] < target) { /* Now I am correct Zone move towards the target */
      start = mid + 1;  /* Regular binary search */ // coorected from '-' to '+'
    } else
      end = mid - 1;
  }
  if (nums[start] == target)
    return start;
  else
    return -1;
}

void test() {

  int ret = 0;
  int nums[] = {4, 5, 6, 7, 0, 1, 2};
  int numsSize = sizeof(nums)/sizeof(nums[0]);
  int target = 0;
  ret =  search(nums, numsSize, target);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   L=[84][04_search_sorted_array_LC-33.c]->[test] :| Output = 4
**/
