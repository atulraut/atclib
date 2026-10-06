/***
    565. Array Nesting

    You are given an integer array nums of length n where nums is
    permutation of the numbers in the range [0, n - 1].

    You should build a set s[k] = {nums[k], nums[nums[k]],
    nums[nums[nums[k]]], ... } subjected to the following rule:

    The first element in s[k] starts with the selection of the element
    nums[k] of index = k.
    The next element in s[k] should be nums[nums[k]], and then
    nums[nums[nums[k]]], and so on.
    We stop adding right before a duplicate element occurs in s[k].
    Return the longest length of a set s[k].

    Input: nums = [5,4,0,3,1,6,2]
    Output: 4
    Explanation:
    nums[0] = 5, nums[1] = 4, nums[2] = 0, nums[3] = 3, nums[4] = 1, nums[5] = 6, nums[6] = 2.
    One of the longest sets s[k]:
    s[0] = {nums[0], nums[5], nums[6], nums[2]} = {5, 6, 2, 0}

    Input: nums = [0,1,2]
    Output: 1

    Constraints:
    1 <= nums.length <= 105
    0 <= nums[i] < nums.length
    All the values of nums are unique.

    https://leetcode.com/problems/array-nesting/
    Date: Sept 1, 2021
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

#define max(x, y) (((x) > (y)) ? (x) : (y))

int arrayNesting__(int* nums, int numsSize) {
  int i, res = 0;
  int count, start;
  for (i = 0; i < numsSize; i++) {
    start = nums[i];
    count = 0;
    do {
      start = nums[start];
      count++;
    } while (start != nums[i]);
    res = max(res, count);
  }
  return res;
}

int arrayNesting(int* nums, int numsSize) {
  int start, count;
  int* visited = (int *)calloc(sizeof(int), numsSize);
  int res = 0;
  for (int i = 0; i < numsSize; i++) {
    debug("Entre i = %d", i);
    if (!visited[i]) {
      start = nums[i];
      count = 0;
      do {
	//	debug("start=%d count = %d num[%d]=%d", start, count, start, nums[start]);
	start = nums[start];
	count++;
	visited[start] = true;
	debug("start=%d count = %d num[%d]=%d", start, count, i, nums[i]);
      } while (start != nums[i]);
      res = max(res, count);
    }
  }
  free(visited);
  visited = NULL;
  return res;
}

int main (int argc, char **argv) {
  int ret = 0;
  int nums[] = {5,4,0,3,1,6,2};
  int numsSize = sizeof(nums) / sizeof(nums[0]);

  ret = arrayNesting(nums, numsSize);

  debug("Output = %d", ret);
  return 0;
}

/**
=> ./a.out
[arrayNesting] L=72 :Entre i = 0
[arrayNesting] L=81 :start=6 count = 1 num[0]=5
[arrayNesting] L=81 :start=2 count = 2 num[0]=5
[arrayNesting] L=81 :start=0 count = 3 num[0]=5
[arrayNesting] L=81 :start=5 count = 4 num[0]=5
[arrayNesting] L=72 :Entre i = 1
[arrayNesting] L=81 :start=1 count = 1 num[1]=4
[arrayNesting] L=81 :start=4 count = 2 num[1]=4
[arrayNesting] L=72 :Entre i = 2
[arrayNesting] L=72 :Entre i = 3
[arrayNesting] L=81 :start=3 count = 1 num[3]=3
[arrayNesting] L=72 :Entre i = 4
[arrayNesting] L=72 :Entre i = 5
[arrayNesting] L=72 :Entre i = 6
[main] L=98 :Output = 4
**/

/**
   Complexity Analysis
   Time complexity : O(n^2)O(n2).
   In worst case, for example- [1,2,3,4,5,0], loop body will be executed n^2 times.
   Space complexity : O(1). Constant space is used.
**/
