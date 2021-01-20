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

int removeDuplicates(int* nums, int numsSize){
  if (numsSize == 0)
    return 0;
  int c1 = 0;
  int c2 = 0;
  int size = numsSize;
  for (c2 = 0; c2 < size; c2++) {
    if (nums[c1] != nums[c2]) {
      c1++;
      nums[c1] = nums[c2];
    }
  }
  return c1 + 1;
}

int main() {
  int arr[6] = {1,2, 2,3,4}; /* Must be non-decreasing */
  int i, j, k, size=5;

  size = sizeof(arr) / sizeof(arr[0]);
  printf("\n [%s] Array with Unique list  : %d \n", __func__, size);
  size = removeDuplicates (arr, size);
  printf("\n [%s] Array with Unique list  : %d \n", __func__, size);
  for (i = 0; i < size; i++) {
    printf("[%s] %d \n", __func__, arr[i]);
  }
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
