/***
    https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/
    Hard: Find Minimum in Rotated Sorted Array II

    Suppose an array of length n sorted in ascending order
    is rotated between 1 and n times. For example, the
    array nums = [0,1,4,4,5,6,7] might become:

    [4,5,6,7,0,1,4] if it was rotated 4 times.
    [0,1,4,4,5,6,7] if it was rotated 7 times.
    Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1
    time results in the array [a[n-1], a[0], a[1], a[2], ..., a[n-2]].

    Given the sorted rotated array nums that may contain
    duplicates, return the minimum element of this array.
    You must decrease the overall operation steps as much
    as possible.

    Input: nums = [1,3,5]
    Output: 1

    Input: nums = [2,2,2,0,1]
    Output: 0

    Constraints:
    n == nums.length
    1 <= n <= 5000
    -5000 <= nums[i] <= 5000
    nums is sorted and rotated between 1 and n times.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 10/202021
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
#define atsizeof(object) (char *)(&object+1) - (char*)(&object)
#define nelem(x)  (sizeof(x) / sizeof((x)[0]))
#define max(a,b)		\
  ({ typeof (a) _a = (a);	\
    typeof (b) _b = (b);	\
    _a > _b ? _a : _b; })
#define min(a,b)		\
  ({ typeof (a) _a = (a);	\
    typeof (b) _b = (b);	\
    _a < _b ? _a : _b; })

int findMin(int* nums, int numsSize) {
  int low = 0;
  int high = numsSize - 1;
  while (low < high) {
    int pivot = low + (high - low) / 2;
    if (nums[pivot] < nums[high])
      high = pivot;
    else if (nums[pivot] > nums[high])
      low = pivot + 1;
    else
      high -= 1;
  }
  return nums[low];
}

int main (int argc, char **argv) {
  int ret = 0;
  int nums[] = {0, 1, 4, 4, 5, 6, 7};
  int numsSize = sizeof(nums)/sizeof(nums[0]);
  debug ("sz = %d", numsSize);
  debug ("sz = %ld", nelem(nums));

  ret =  findMin(nums, numsSize);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=77 :sz = 7
   [main] L=79 :Output = 0
**/
