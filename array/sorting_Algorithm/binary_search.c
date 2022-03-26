/***
    https://leetcode.com/problems/binary-search
    Binary Search

    Given an array of integers nums which is sorted in
    ascending order, and an integer target, write a
    function to search target in nums. If target exists,
    then return its index. Otherwise, return -1.

    You must write an algorithm with O(log n) runtime complexity.

    Input: nums = [-1,0,3,5,9,12], target = 9
    Output: 4
    Explanation: 9 exists in nums and its index is 4

    Input: nums = [-1,0,3,5,9,12], target = 2
    Output: -1
    Explanation: 2 does not exist in nums so return -1

    Constraints:

    1 <= nums.length <= 104
    -104 < nums[i], target < 104
    All the integers in nums are unique.
    nums is sorted in ascending order.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Sat Mar 26 09:27:32 PDT 2022
    Folsom, CA.
*/

/*----------------------------------- Header --------------------------------------*/
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

/*----------------------------------- Micro --------------------------------------*/
#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)
#define atsizeof(object) (char *)(&object+1) - (char*)(&object)
#define arrsz(x)  (sizeof(x) / sizeof((x)[0]))
#define max(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a > _b ? _a : _b; })
#define min(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

/***
    Algorithm:
    Initialise left and right pointers : left = 0, right = n - 1.
    While left <= right :
    Compare middle element of the array nums[pivot] to the target value target.
    If the middle element is the target target = nums[pivot] : return pivot.
    If the target is not yet found :
    If target < nums[pivot], continue the search on the left right = pivot - 1.
    Else continue the search on the right left = pivot + 1.
*/
int search(int* nums, int numsSize, int target) {
  int pivot, left = 0, right = numsSize - 1;

  while (left <= right) {
    pivot = left + (right - left) / 2;
    if (nums[pivot] == target)
      return pivot;
    if (target < nums[pivot])
      right = pivot - 1;
    else
      left = pivot + 1;
  }
  return -1;
}

void test() {
  int ret = 0;
  int nums[] = {-1,0,3,5,9,12};
  int numsSize = arrsz(nums);
  int target = 9;

  ret = search(nums, numsSize, target);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [test] L=81 :Output = 4
**/
