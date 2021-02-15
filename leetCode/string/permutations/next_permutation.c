/***
    Next Permutation :
    Implement next permutation, which rearranges numbers into the
    lexicographically next greater permutation of numbers.
    If such an arrangement is not possible, it must rearrange it as the
    lowest possible order (i.e., sorted in ascending order).
    The replacement must be in place and use only constant extra memory.

    Example 1:
    Input: nums = [1,2,3]
    Output: [1,3,2]

    Example 2:
    Input: nums = [3,2,1]
    Output: [1,2,3]

    Example 3:
    Input: nums = [1,1,5]
    Output: [1,5,1]

    Example 4:
    Input: nums = [1]
    Output: [1]

    https://leetcode.com/problems/next-permutation/solution/

    Constraints :
    1 <= nums.length <= 100
    0 <= nums[i] <= 100
*/
#include <stdio.h>
#include <stdlib.h>
#include "../../at_lib.h"

void print_array(int *nums) {
  int numsSize = 4;//sizeof(nums) / sizeof(nums[0]);
  debug (" Enter sz = %d ", numsSize);

  for (int i=0; i<numsSize; i++)
    debug ("i=%d nums[%d]", i, nums[i]);
}

void swap(int *nums, int i, int j) {
  int temp = nums[i];
  nums[i] = nums[j];
  nums[j] = temp;
}

void reverseNum(int *array, int start, int end){
  while(start < end) {
    int temp = array[start];
    array[start] = array[end];
    array[end] = temp;
    start++;
    end--;
  }
  return;
}
void nextPermutation(int* nums, int numsSize){
  int last = numsSize-2;
  int temp;
  while(last >= 0 && (nums[last] >= nums[last+1]))
    last--;

  if(last >= 0) {
    int j = numsSize-1;
    while (j >= 0 && nums[j] <= nums[last]) {
      j--;
    }
    swap(nums, last, j);
    /*
      temp = nums[last];
      nums[last]  = nums[j];
      nums[j] = temp;
    */
  }
  debug (" Enter ");
  print_array(nums);
  reverseNum(nums, last+1, numsSize-1);
  return;
}

int main () {

  int nums1[] = {3, 2, 1};
  int nums[] = {4, 5, 3, 1};
  int numsSize = sizeof(nums) / sizeof(nums[0]);

  nextPermutation(nums, numsSize);
  debug (" Enter sz = %d ", numsSize);
  print_array(nums);

  return 0;
}

/**
   => ./a.out
   [main] L=80 :i=0 nums[1]
   [main] L=80 :i=1 nums[2]
   [main] L=80 :i=2 nums[3]

   => ./a.out - 4,5,3,1
   [nextPermutation] L=77 : Enter
   [print_array] L=37 : Enter sz = 4
   [print_array] L=40 :i=0 nums[5]
   [print_array] L=40 :i=1 nums[4]
   [print_array] L=40 :i=2 nums[3]
   [print_array] L=40 :i=3 nums[1]
   [main] L=90 : Enter sz = 4
   [print_array] L=37 : Enter sz = 4
   [print_array] L=40 :i=0 nums[5]
   [print_array] L=40 :i=1 nums[1]
   [print_array] L=40 :i=2 nums[3]
   [print_array] L=40 :i=3 nums[4]

**/

/**
   Approach 2: Single Pass Approach :
   First, we observe that for any given sequence that is in descending order, no next
   larger permutation is possible. For example, no next permutation is possible for
   the following array: [9, 5, 4, 3, 1]
   We need to find the first pair of two successive numbers a[i] and a[i−1],
   from the right, which satisfy a[i]>a[i−1]a[i] > a[i-1]a[i]>a[i−1]. Now, no rearrangements
   to the right of a[i−1] can create a larger permutation since that
   subarray consists of numbers in descending order. Thus, we need to rearrange the
   numbers to the right of a[i−1] including itself.

   Now, what kind of rearrangement will produce the next larger number? We want to
   create the permutation just larger than the current one. Therefore, we need to
   replace the number a[i−1]a[i-1]a[i−1] with the number which is just larger than
   itself among the numbers lying to its right section, say a[j]a[j]a[j].

   We swap the numbers a[i−1]and a[j]. We now have the correct number at index i−1.
   But still the current permutation isn't the permutation that we are looking for.
   We need the smallest permutation that can be formed by using the numbers only to
   the right of a[i−1]. Therefore, we need to place those numbers in ascending
   order to get their smallest permutation.

   But, recall that while scanning the numbers from the right, we simply kept decrementing
   the index until we found the pair a[i]a[i]a[i] and a[i−1]a[i-1]a[i−1] where,
   a[i] > a[i-1]. Thus, all numbers to the right of a[i−1]a[i-1]a[i−1] were already sorted
   in descending order. Furthermore, swapping a[i−1] and a[j] didn't change that order.
   Therefore, we simply need to reverse the numbers following a[i−1] to get the next
   smallest lexicographic permutation.
**/
