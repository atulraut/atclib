/***
 * https://leetcode.com/problems/product-of-array-except-self/
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
 * Jun 22 2020
 * San Diego, CA
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/**
   For every given index, ii, we will make use of the product of all the numbers
   to the left of it and multiply it by the product of all the numbers to the right.
   This will give us the product of all the numbers except the one at the given
   index ii. Let's look at a formal algorithm describing this idea more concretely.

   Algorithm :
   Initialize two empty arrays, L and R where for a given index i, L[i] would
   contain the product of all the numbers to the left of i and R[i] would
   contain the product of all the numbers to the right of i.
   We would need two different loops to fill in values for the two arrays.
   For the array L, L[0]L[0] would be 1 since there are no elements to the
   left of the first element. For the rest of the elements, we simply
   use L[i] = L[i - 1] * nums[i - 1]L[i]=L[i−1]∗nums[i−1]. Remember that L[i]
   represents product of all the elements to the left of element at index i.
   For the other array, we do the same thing but in reverse i.e. we start
   with the initial value of 1 in R[length - 1]R[length−1] where lengthlength
   is the number of elements in the array, and keep updating R[i] in reverse.
   Essentially, R[i] = R[i + 1] * nums[i + 1]R[i]=R[i+1]∗nums[i+1]. Remember
   that R[i] represents product of all the elements to the right of element at index i.
   Once we have the two arrays set up properly, we simply iterate over
   the input array one element at a time, and for each element at index i,
   we find the product except self as L[i] * R[i]L[i]∗R[i].

   Complexity analysis
   Time complexity : O(N) where NN represents the number of elements
   in the input array. We use one iteration to construct the array LL,
   one to update the array answeranswer.
   Space complexity : O(1) since don't use any additional array for our
   computations. The problem statement mentions that using the
   answeranswer array doesn't add to the space complexity.

*/
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
