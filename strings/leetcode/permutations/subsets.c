/***
    Subsets :
    Given an integer array nums of unique elements, return all possible
    subsets (the power set).
    The solution set must not contain duplicate subsets. Return
    the solution in any order.

    Example 1:
    Input: nums = [1,2,3]
    Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

    Example 2:
    Input: nums = [0]
    Output: [[],[0]]

    Constraints:
    1 <= nums.length <= 10
    -10 <= nums[i] <= 10
    All the numbers of nums are unique.
    https://leetcode.com/problems/subsets/
    Date : 18-Feb-2021
    San Diego, CA
*/
#include <stdio.h>
#include "../../../at_lib.h"

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
  int len = (1<<numsSize);
  int** result = (int**)malloc(len*sizeof(int*));
  int i,pos,idx,temp;

  (*returnColumnSizes) = (int*)calloc(len,sizeof(int));

  for(i=0;i<len;i++) {
    result[i] = (int*)malloc(numsSize*sizeof(int));
  }

  for(i=0;i<len;i++) {
    temp = i;
    pos = numsSize-1;
    idx = 0;
    while(temp) {
      if(temp&1)
	result[i][idx++] = nums[pos];
      temp>>=1;
      pos--;
    }
    (*returnColumnSizes)[i] = idx;
  }

  *returnSize = len;
  return result;
}

int main () {
  int i,j;
  int nums[] = {1, 2, 3};
  int returnSize;
  int* returnColumnSizes;
  int numsSize = sizeof(nums) / sizeof(nums[0]);

  int**op =  subsets(nums, numsSize, &returnSize, &returnColumnSizes);

  for (i=0,j=0; i<returnSize; i++, j++)
      debug (" op = %c ", op[i][j]);
  return 0;
}

/**
 **/
