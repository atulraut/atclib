/***
 * LeetCode : Permutation Sequence
 * The set [1,2,3,...,n] contains a total of n! unique permutations.
 * By listing and labeling all of the permutations in order, we get
 *  the following sequence for n = 3:
    "123"
    "132"
    "213"
    "231"
    "312"
    "321"
 * Given n and k, return the kth permutation sequence.
 * NOte:
 * Given n will be between 1 and 9 inclusive.
 * Given k will be between 1 and n! inclusive.
 * Example 1:
 * Input: n = 3, k = 3
 * Output: "213"
 * Example 2:
 * Input: n = 4, k = 9
 * Output: "2314"
 * Logic : https://www.youtube.com/watch?v=W9SIlE2jhBQ - Pending
 * Date : 06/21/2020 08:05PM SD
 * https://leetcode.com/problems/permutations/submissions/ - this
 * https://leetcode.com/explore/featured/card/june-leetcoding-challenge/541/week-3-june-15th-june-21st/3366/ - Pending
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

/*
returnSize = how many 1-D array you have
returnColumnSizes = how many element each 1-D array has
*/
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

int main() {

  int arr[] = {1, 2, 3};
  int numsSize = sizeof(arr)/sizeof(arr[0]);
  int returnSize;
  int *returnColumnSizes;
  int**res =  permute(arr, numsSize, &returnSize, &returnColumnSizes) ;

  printf ("[%s] Rsz=%d Csz=%d L=%d",__func__, returnSize, *returnColumnSizes, __LINE__);

  for(int i = 0; i < 1; i++)
    for(int j = 0; j < *returnColumnSizes; j++)
      printf ("o/p--> %d \n", res[i][j]);
}
