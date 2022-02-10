/***
 * Name - Atul Raut
 * Date - January, 18, 2021 San Diego, CA-92126
 * Ref  - https://leetcode.com/problems/remove-duplicates-from-sorted-array/
 * LeetCode : Remove Duplicates from Sorted Array
 * Given a sorted array nums, remove the duplicates in-place such that
 * each element appears only once and returns the new length.
 * Do not allocate extra space for another array, you must do this by
 * modifying the input array in-place with O(1) extra memory.
 * Clarification:
 * Confused why the returned value is an integer but your answer is an array?
 * Note that the input array is passed in by reference, which means a
 * modification to the input array will be known to the caller as well.
 * Internally you can think of this:
 * // nums is passed in by reference. (i.e., without making a copy)
 * int len = removeDuplicates(nums);
 *
 * // any modification to nums in your function would be known by the caller.
 * // using the length returned by your function, it prints the first len elements.
 * for (int i = 0; i < len; i++) {
 *   print(nums[i]);
 * }
 * Example 1:
 *
 * Input: nums = [1,1,2]
 * Output: 2, nums = [1,2]
 * Explanation: Your function should return length = 2, with the first two elements
 * of nums being 1 and 2 respectively. It doesn't matter what you leave beyond
 * the returned length.
 *
 * Example 2:
 *
 * Input: nums = [0,0,1,1,1,2,2,3,3,4]
 * Output: 5, nums = [0,1,2,3,4]
 * Explanation: Your function should return length = 5, with the first five elements
 * of nums being modified to 0, 1, 2, 3, and 4 respectively. It doesn't matter what
 * values are set beyond the returned length.
 */
#include<stdio.h>
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

int removeDuplicates(int* nums, int numsSize){
  if (numsSize == 0)
    return 0;
  int c1 = 0;
  int c2 = 0;
  int size = numsSize;

  for (c2 = 0; c2 < size; c2++) {
    debug ("B: c1 = %d nums[c1] = %d c2 = %d nums[c2] = %d ", c1, nums[c1], c2, nums[c2]);
    printf ("\n");
    if (nums[c1] != nums[c2]) {
      c1++;
      nums[c1] = nums[c2];
    }
  }
  return c1 + 1;
}

void test1() {
  int arr[6] = {1,2, 2,3,4}; /* Must be non-decreasing */
  int i, j, k, size=5;

  size = sizeof(arr) / sizeof(arr[0]);
  printf("\n [%s] Array with Unique list  : %d \n", __func__, size);
  size = removeDuplicates (arr, size);
  printf("\n [%s] Array with Unique list  : %d \n", __func__, size);
  for (i = 0; i < size; i++) {
    printf("[%s] %d \n", __func__, arr[i]);
  }

}

/**
   https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii
   Remove Duplicates from Sorted Array II
   Input: nums = [1,1,1,2,2,3]
   Output: 5, nums = [1,1,2,2,3,_]
   Explanation: Your function should return k = 5, with the first five
   elements of nums being 1, 1, 2, 2 and 3 respectively.
   It does not matter what you leave beyond the returned k (hence they
   are underscores).

   Date: Feb 5 2022
**/
int removeDuplicates_II(int* nums, int numsSize) {
  int i=0,j;
  for (j=0;j<numsSize;j++) {
    debug ("i = %d i-2=%d j = %d", i, i-2, j);
    if (i<2 || nums[j]>nums[i-2]) {
      debug ("i = %d i-2=%d j = %d nums[%d]=%d nums[%d]=%d", i, i-2, j, i,nums[i], j,nums[j]);
      nums[i++]=nums[j];
    }
  }
  return i;
}

void test2() {
  int ret = 0;
  int arr[] = {1,1,1,2,2,3};
  debug("Remove II");
  int sz = sizeof(arr)/sizeof(arr[0]);
  ret = removeDuplicates_II(arr, sz);
  debug ("Ret = %d", ret);
  for (int i=0; i<sz; ++i)
    debug ("Out --> arr[%d]=%d", i, arr[i]);
}

int main() {
  test1();
  test2();
  return (0);
}

/***
    => ./a.out

    [main] Array with Unique list  : 6

    [main] Array with Unique list  : 5
    [main] 1
    [main] 2
    [main] 3
    [main] 4
    [main] 0
*/

/***
    [test2] L=124 :Remove II
    [removeDuplicates_II] L=112 :i = 0 i-2=-2 j = 0
    [removeDuplicates_II] L=114 :i = 0 i-2=-2 j = 0 nums[0]=1 nums[0]=1
    [removeDuplicates_II] L=112 :i = 1 i-2=-1 j = 1
    [removeDuplicates_II] L=114 :i = 1 i-2=-1 j = 1 nums[1]=1 nums[1]=1
    [removeDuplicates_II] L=112 :i = 2 i-2=0 j = 2
    [removeDuplicates_II] L=112 :i = 2 i-2=0 j = 3
    [removeDuplicates_II] L=114 :i = 2 i-2=0 j = 3 nums[2]=1 nums[3]=2
    [removeDuplicates_II] L=112 :i = 3 i-2=1 j = 4
    [removeDuplicates_II] L=114 :i = 3 i-2=1 j = 4 nums[3]=2 nums[4]=2
    [removeDuplicates_II] L=112 :i = 4 i-2=2 j = 5
    [removeDuplicates_II] L=114 :i = 4 i-2=2 j = 5 nums[4]=2 nums[5]=3
    [test2] L=127 :Ret = 5
    [test2] L=129 :Out --> arr[0]=1
    [test2] L=129 :Out --> arr[1]=1
    [test2] L=129 :Out --> arr[2]=2
    [test2] L=129 :Out --> arr[3]=2
    [test2] L=129 :Out --> arr[4]=3
    [test2] L=129 :Out --> arr[5]=3
*/
