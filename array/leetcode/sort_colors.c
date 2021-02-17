/***
 * LeetCode : Sort Colors
 * Given an array with n objects colored red, white or blue, sort them
 * in-place so that objects of the same color are adjacent, with the colors
 * in the order red, white and blue.
 * Here, we will use the integers 0, 1, and 2 to represent the color red, white,
 * and blue respectively.
 * Note: You are not suppose to use the library's sort function for this problem.
 * Example:
 * Input:  [2,0,2,1,1,0]
 * Output: [0,0,1,1,2,2]
 * Follow up:
 * A rather straight forward solution is a two-pass algorithm using counting sort.
 * First, iterate the array counting number of 0's, 1's, and 2's, then overwrite
 * array with total number of 0's, then 1's and followed by 2's.
 * Could you come up with a one-pass algorithm using only constant space?
 * Logic :
 * Date: 06/17/2020 Wednesday, 02:00PM
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int *nums, int i, int j) {
  int temp;

  printf ("[%s] i = %d j=%d L=%d\n", __func__, i, j, __LINE__);
  temp = nums[i];
  nums[i] = nums[j];
  nums[j] = temp;
}

void sortColors(int* nums, int numsSize){
 int zero = 0;
  int two = numsSize - 1;
  for(int i = 0; i < numsSize; i++) {
    if(nums[i] == 0) {
        printf ("[%s] i = %d zero=%d L=%d\n", __func__, i, zero, __LINE__);
        swap(nums, i, zero++);
    }
    else if(nums[i] == 2 && i < two) {
        printf ("[%s] i = %d two=%d L=%d\n", __func__, i, two, __LINE__);
        swap(nums, i--, two--);
    }
  }
}

int main () {
  int i;
  int nums [] = {2,0,2,1,1,0};
  int numsSize = sizeof(nums)/sizeof(nums[0]);

  sortColors(nums, numsSize);
  for (i=0; i<numsSize; i++)
    printf ("[%s] ret=%d L=%d \n", __func__, nums[i], __LINE__);
}
