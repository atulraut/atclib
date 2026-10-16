/***
    https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/description/

    153. Find Minimum in Rotated Sorted Array

    Suppose an array of length n sorted in ascending order is rotated
    between 1 and n times. For example, the array nums = [0,1,2,4,5,6,7] might become:

    [4,5,6,7,0,1,2] if it was rotated 4 times.
    [0,1,2,4,5,6,7] if it was rotated 7 times.
    Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1
    time results in the array [a[n-1], a[0], a[1], a[2], ..., a[n-2]].

    Given the sorted rotated array nums of unique elements,
    return the minimum element of this array.

    You must write an algorithm that runs in O(log n) time.

    Input: nums = [3,4,5,1,2]
    Output: 1
    Explanation: The original array was [1,2,3,4,5] rotated 3 times.

    Input: nums = [4,5,6,7,0,1,2]
    Output: 0
    Explanation: The original array was [0,1,2,4,5,6,7] and it was rotated 4 times.

    Input: nums = [11,13,15,17]
    Output: 11
    Explanation: The original array was [11,13,15,17] and it was rotated 4 times.

    Constraints:
    n == nums.length
    1 <= n <= 5000
    -5000 <= nums[i] <= 5000
    All the integers of nums are unique.
    nums is sorted and rotated between 1 and n times.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Thu Oct 15 17:21:53 PDT 2026
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

int findMin(int* nums, int numsSize) {

  int start = 0;
  int end = numsSize - 1;
  int mid = 0;

  while (start < end) {
    mid = start + (end - start) / 2;

    if(nums[mid] < nums[end])
      end = mid;
    else if (nums[mid] > nums[end])
      start = mid + 1;
  }
  return nums[start];
}

void test() {
  int ret = 0;
  int nums[] = {3,4,5,1,2};
  int numsSize = 5;
  ret = findMin(nums, numsSize);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   L=[81][2_binary_search_modified/03_findMinInRotedSortedArray_LC-153.c]->[test] :| Output = 1
**/
