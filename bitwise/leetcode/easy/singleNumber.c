/***
    LeetCode :  Single Number
    Given a non-empty array of integers nums, every element appears twice
    except for one. Find that single one.
    Follow up: Could you implement a solution with a linear runtime
    complexity and without using extra memory?

    Example 1:
    Input: nums = [2,2,1]
    Output: 1

    Example 2:
    Input: nums = [4,1,2,1,2]
    Output: 4

    Example 3:
    Input: nums = [1]
    Output: 1

    Constraints:
    1 <= nums.length <= 3 * 104
    -3 * 104 <= nums[i] <= 3 * 104
    Each element in the array appears twice except for one element which appears only once.
    Tue Feb 23 13:49:11 2021 -0800

    https://leetcode.com/problems/single-number/
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

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)


// 4 ms
int singleNumber(int* nums, int numsSize) {
   debug("*nums=%d", *nums);
  while (--numsSize) {
    debug("*nums=%d nums[numsSize]=%d", *nums, nums[numsSize]);
    *nums ^= nums[numsSize];
    debug("*nums=%d", *nums);
  }
  return *nums;
}

// 24ms
int singleNumber2(int* nums, int numsSize){
  int a = 0;
  for(int i=0; i<numsSize; i++) {
    a ^= nums[i];
  }
  return a;
}

int main () {
  int nums2[] = {4, 1, 2, 1, 2};
  int nums[] = {2, 1,1};
  int numsSize = sizeof(nums) / sizeof(nums[0]);

  int op =  singleNumber(nums, numsSize);
  debug ("op = %d ", op);

  return 0;
}
/**
   => ./a.out
   [main] L=62 :op = 4
**/

/**
   Using Bit Manipulation :
   Concept
   If we take XOR of zero and some bit, it will return that bit
   a ⊕ 0 = a
   If we take XOR of two same bits, it will return 0
   a ⊕ a = 0
   a ⊕ b ⊕ a = (a ⊕ a) ⊕ b = 0 ⊕ b = b
   So we can XOR all bits together to find the unique number
**/

/**
  Complexity Analysis
  Time complexity : O(n). We only iterate throughnums,
  so the time complexity is the number of elements in \text{nums}nums.
  Space complexity : O(1).
*/
