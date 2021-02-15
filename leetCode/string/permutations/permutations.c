/***
    Permutations :
    Given an array nums of distinct integers, return all the possible permutations.
    You can return the answer in any order.

    Example 1:
    Input: nums = [1,2,3]
    Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

    Example 2:
    Input: nums = [0,1]
    Output: [[0,1],[1,0]]

    Example 3:
    Input: nums = [1]
    Output: [[1]]

    Constraints:
    1 <= nums.length <= 6
    -10 <= nums[i] <= 10
    All the integers of nums are unique.

    https://leetcode.com/problems/permutations/
*/
#include <stdio.h>
#include "../../../at_lib.h"


int *nodetable;

void dfs_each_node(int * nums, int numsSize, int *temp, int pos, int **res, int *returnSize) {
  int i;

  if (pos == numsSize) {
    res[*returnSize] = (int *) calloc(sizeof(int), numsSize);
    memcpy(res[*returnSize], temp, sizeof(int) * numsSize);
    *returnSize= *returnSize + 1;

    return;
  }

  for (i = 0; i < numsSize; i++) {
    if (nodetable[i] == 1)
      continue;
    temp[pos] = nums[i];
    nodetable[i] = 1;

    dfs_each_node(nums, numsSize, temp, pos+1, res, returnSize);
    nodetable[i] = 0;
  }
}

int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {

  int i, *temp, **res;
  int expNum;

  expNum = 1;

  for(i = 1; i <= numsSize; i++)
    expNum = expNum * i;

  nodetable = (int *) calloc (sizeof(int), numsSize);
  res = (int **) calloc(sizeof(int *), expNum);
  temp = (int *) calloc(sizeof(int), numsSize);
  *returnColumnSizes = (int *) calloc (sizeof(int), expNum);

  for(i = 0; i < expNum; i++)
    (*returnColumnSizes)[i] = numsSize;

  *returnSize = 0;

  dfs_each_node(nums, numsSize, temp, 0, res, returnSize);

  return res;
}


int main () {
  int nums[] = {1, 2, 3};
  int returnSize;
  int* returnColumnSizes;
  int numsSize = sizeof(nums) / sizeof(nums[0]);

  int**op =  permute(nums, numsSize, &returnSize, &returnColumnSizes);
  for (int i=0,j=0; i<returnSize; i++, j++)
     debug (" op = %d ", op[i][j]);
  return 0;
}


/**

 **/
