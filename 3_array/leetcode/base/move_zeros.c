/***
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

/***
    https://leetcode.com/explore/featured/card/fun-with-arrays/525/inserting-items-into-an-array/3245/
    https://leetcode.com/problems/duplicate-zeros/solution/
    s = 0
    d = 0
    # Copy is performed until the destination array is full.
    for s in range(N):
    if source[s] == 0:
    # Copy zero twice.
    destination[d] = 0
    d += 1
    destination[d] = 0
    else:
    destination[d] = source[s]

    d += 1
*/
void duplicateZeros(int* arr, int arrSize){
  int temp = 0;
  int i = 0;
  while(i < arrSize) {
    if(arr[i] == 0) {
      for(int j = arrSize - 2; j > i; j--) {
	arr[j + 1] = arr[j];
      }
      if(i == arrSize - 1) {
	break;
      }
      arr[i + 1] = 0;
      i += 2;
      continue;
    }
    i++;
  }
}

/***
    Move all zeros towards Ends.
 */
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
  int arrZ[] = {1, 0, 2, 3, 5};

  sz = sizeof(arr) / sizeof(arr[1]);

  for(i=0; i<sz; i++)
    printf ("[%s] num[%d]=%d L=%d\n", __func__, i, arr[i], __LINE__);
  moveZeroes(arr, sz);
  printf ("\n");
  for(i=0; i<sz; i++)
    printf ("[%s] arr[%d]=%d L=%d \n", __func__, i, arr[i], __LINE__);
  printf ("\n");

  printf ("Start Duplicate Zeros !\n");
  sz = sizeof(arrZ) / sizeof(arrZ[1]);
  duplicateZeros(arrZ, sz);
  for(i=0; i<sz; i++)
    printf ("[%s] -->i=%d num=%d L=%d\t", __func__, i, arrZ[i], __LINE__);
  printf ("\n");

  return 0;
}
