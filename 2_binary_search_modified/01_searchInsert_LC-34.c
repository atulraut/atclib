/***
    https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/

    34. Find First and Last Position of Element in Sorted Array

    Given an array of integers nums sorted in non-decreasing order,
    find the starting and ending position of a given target value.

    If target is not found in the array, return [-1, -1].

    You must write an algorithm with O(log n) runtime complexity.

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
    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Wed Oct 14 22:19:39 PDT 2026
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

/**
   its divice and conquer : Divide into two halvs
   first half find first part
   then next part find next element.

       (end) |  | (start)
   [left Zone | right zone]
   [<= target | >= target]

   Algo :
    start = 0, end = n-1
    while start <= end :
      mid = start + (end -start) / 2
      if(nums[mid) // is in left zone - we always search on RHS
         start = mid + 1
      else : // nums[mide] is in right zone
         end = mid - 1
     // use the boundary to return the asnwer to the given problem.
**/
int* searchRange(int* nums, int numsSize, int target, int* returnSize) {
  int start = 0, end = numsSize-1, mid = end/2;
  *returnSize = 2;
  int* res = malloc(sizeof(int)*2);
  res[0] = -1; res[1] = -1;

  while (start <= end) {
    mid = start + (end - start) / 2;
    if (target == nums[mid]) { // might be in both sides
      int mid2 = mid;
      while (start < mid) {
	int start_mid = (mid + start)/2;
	if (nums[start_mid] < target)
	  start = start_mid + 1;
	else
	  mid = start_mid;
      }
      while (mid2 < end) {
	int end_mid = (mid2 + end +1)/2;
	if (nums[end_mid] >  target)
	  end = end_mid-1;
	else
	  mid2 = end_mid;
      }
      res[0] = start; res[1] = end;
      return res;
    } else if (target < nums[mid]) // not in right side
      end  = mid-1;
    else if (target > nums[mid]) // not in left side
      start = mid+1;
  }
  return res;
}

void test() {

  int nums[] = {5,7,7,8,8,10};
  int target = 8;
  int numsSize = 6;
  int returnSize = 0;
  int* ret = searchRange(nums,numsSize, target, &returnSize);
  for (int i=0; i<returnSize; ++i)
    debug("Output = %d", ret[i]);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   L=[109][2_binary_search_modified/01_searchInsert_LC-34.c]->[test] :| Output = 3
   L=[109][2_binary_search_modified/01_searchInsert_LC-34.c]->[test] :| Output = 4
**/
