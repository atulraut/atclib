/***
    LeetCode : 229. Majority Element II
    Given an integer array of size n, find all elements that appear
    more than ⌊ n/3 ⌋ times.
    Note: The algorithm should run in linear time and in O(1) space.
    Example 1:
    Input: [3,2,3]
    Output: [3]
    Example 2:
    Input: [1,1,1,3,3,2,2,2]
    Output: [1,2]

    https://leetcode.com/problems/majority-element-ii/
    https://leetcode.com/explore/featured/card/september-leetcoding-challenge/557/week-4-september-22nd-september-28th/3469/
*/
#include "../../at_lib.h"

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* majorityElement(int* nums, int numsSize, int* returnSize){
  *returnSize = 0;
  int *res = (int *)malloc(2 * sizeof(int));
  if(numsSize == 0)
    return NULL;

  int nums1 = 0, nums2 = 0, count1 = 0, count2 = 0;
  for(int i = 0; i < numsSize; i++) {
    if(nums1 == nums[i])
      count1++;
    else if(nums2 == nums[i])
      count2++;
    else if(count1 == 0) {
      nums1 = nums[i];
      count1++;
    } else if(count2 == 0) {
      nums2 = nums[i];
      count2++;
    } else {
      count1--;
      count2--;
    }
  }
  count1 = 0;
  count2 = 0;
  for(int i = 0; i < numsSize; i++) {
    if(nums1 == nums[i])
      count1++;
    else if(nums2 == nums[i])
      count2++;
  }
  if(count1 > numsSize / 3)
    res[(*returnSize)++] = nums1;

  if(count2 > numsSize / 3)
    res[(*returnSize)++] = nums2;

  return res;
}

int main () {
  int nums [] = {1, 1, 1, 3, 3, 2, 2, 2};
  //int nums [] = {3, 2, 3};
  int sz = sizeof(nums) / sizeof(nums[0]);
  int retSz;
  int *ret;

  ret = majorityElement(nums, sz, &retSz);

  for (int i=0; i<retSz; i++)
    printf ("[%s] --> %d \n",__func__,  ret[i]);
}
