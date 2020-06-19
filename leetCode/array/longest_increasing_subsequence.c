/***
 * LeetCode :  Largest Divisible Subset
 * Given a set of distinct positive integers, find the largest subset
 * such that every pair (Si, Sj) of elements in this subset satisfies:
 * Si % Sj = 0 or Sj % Si = 0.
 * If there are multiple solutions, return any subset is fine.
 * Example 1:
 * Input: [1,2,3]
 * Output: [1,2] (of course, [1,3] will also be ok)
 * Example 2:
 * Input: [1,2,4,8]
 * Output: [1,2,4,8]
 * Logic : https://www.youtube.com/watch?v=mouCn3CFpgg
 */

/* Dynamic Programming C++ implementation of LIS problem */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* lis() returns the length of the longest increasing
   subsequence in arr[] of size n */
int lis( int *nums, int numsSize)  {
  int i, j, max;
  int lis[numsSize];

  lis[0] = 1;
  /* Compute optimized LIS values in bottom up manner */
  for (i=1; i<numsSize; i++) {
    lis[i] = 1;
    for (j=0; j <i; j++ )
      if (nums[i] > nums[j] && lis[i] < lis[j] + 1)
	lis[i] = lis[j] + 1;
  }

  max = lis[0];
  // Return maximum value in lis[]
  for (i=1; i<numsSize; i++) {
    printf("[%s] i=%d L=%d\n",__func__, nums[i], __LINE__);
    if (lis[i] > max)
      max = lis[i];
  }
  return max;
}

/* Driver program to test above function */
int main() {
  int arr[] = {10,9,2,5,3,7,101,18};
  int n = sizeof(arr)/sizeof(arr[0]);

  printf("Length of lis is %d\n", lis(arr, n));
  return 0;
}
