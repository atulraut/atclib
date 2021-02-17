/***
 * LeetCode : Search Insert Position
 * Given a sorted array and a target value, return the index if the target is found.
 * If not, return the index where it would be if it were inserted in order.
 * You may assume no duplicates in the array.
 * Example 1:
 * Input: [1,3,5,6], 5
 * Output: 2
 * Example 2:
 * Input: [1,3,5,6], 2
 * Output: 1
 * Example 3:
 * Input: [1,3,5,6], 7
 * Output: 4
 * Example 4:
 * Input: [1,3,5,6], 0
 * Output: 0
 * Logic : https://www.youtube.com/watch?v=0A40XJH_VvE
 * Date: 06/17/2020 Wednesday, 12:22PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Using Binary Search Insead Linear Search */
int searchInsert(int* nums, int numsSize, int target) {
  int low = 0;
  int high = numsSize-1;
  int mid;

  while (low<=high) {
    mid = (low+high)/2;

    if (nums[mid] == target)
      return mid;
    else if (nums[mid] < target)
      low = mid + 1;
    else
      high = mid - 1;
  }
  return low;
}

int main () {
  int ret;
  int nums [] = {1,3,5,6};
  int target = 7;//2;
  int numsSize = sizeof(nums)/sizeof(nums[0]);

  ret = searchInsert(nums, numsSize, target);
  printf ("[%s] ret=%d L=%d \n", __func__, ret, __LINE__);
}
