/*
  Given an array nums, write a function to move all 0's to the end
  of it while maintaining the relative order of the non-zero elements.
  Example:
  Input: [0,1,0,3,12]
  Output: [1,3,12,0,0]
  Note:
    You must do this in-place without making a copy of the array.
    Minimize the total number of operations.
*/
#include <stdio.h>
#include <stdlib.h>

void moveZeroes(int* nums, int numsSize){
  if (numsSize == 0 || numsSize == 1)
    return;

  int left=0, right=0, temp;
  while (right < numsSize) {
    if (nums[right] == 0) {
      ++right;
    } else {
      /* swap */
      temp = nums[left];
      nums[left] = nums[right];
      nums[right] = temp;
      ++left;
      ++right;
    }
  }
}

int main() {
  int i, sz;
  int arr[] = {0,1,0,3,12};

  sz = sizeof(arr) / sizeof(arr[1]);

  for(i=0; i<sz; i++)
    printf ("[%s] -->i=%d num=%d \t", __func__, i, arr[i]);
  moveZeroes(arr, sz);
  printf ("\n");
  for(i=0; i<sz; i++)
    printf ("[%s] -->i=%d num=%d \t", __func__, i, arr[i]);
  printf ("\n");
}
