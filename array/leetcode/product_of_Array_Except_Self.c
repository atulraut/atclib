/***
 * LeetCode : Product of Array Except Self
 * Given an array nums of n integers where n > 1,  return an
 * array output such that output[i] is equal to the product of
 * all the elements of nums except nums[i].
 * Example:
 * Input:  [1,2,3,4]
 * Output: [24,12,8,6]
 * Constraint: It's guaranteed that the product of the elements of
 * any prefix or suffix of the array (including the whole array) fits in a 32 bit integer.
 * Note: Please solve it without division and in O(n).
 * Follow up:
 * Could you solve it with constant space complexity? (The output
 * array does not count as extra space for the purpose of space complexity analysis.)
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* productExceptSelf(int* nums, int numsSize, int* returnSize) {
  if(0==numsSize)
    return 0;

  int *ret = malloc(numsSize*sizeof(int));
  *returnSize = numsSize;

  int i=0;
  while(i < numsSize) {
    ret[i] = 1;
    ++i;
  }

  i=1;
  int right = 1;
  int left = 1;
  while(i < numsSize) {
    left *= nums[i-1];
    ret[i] *= left;

    right *= nums[numsSize-i];
    ret[numsSize-i-1] *= right;
    ++i;
  }

  return ret;
}

int main () {
  int arr[] = {1, 2, 3, 4};
  int numsSize = sizeof(arr) / sizeof (arr[0]);
  int returnSize;

  int *ret = productExceptSelf(arr, numsSize, &returnSize);

  for(int i=0; i<returnSize; i++)
    printf ("[%s] arr[%d]=%d  \n", __func__, i, ret[i]);
}

/***
    => ./a.out
    [main] arr[0]=24
    [main] arr[1]=12
    [main] arr[2]=8
    [main] arr[3]=6
*/
