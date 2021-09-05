/***
    Unique Binary Search Trees II

    Given an integer n, return all the structurally unique BST's
    (binary search trees), which has exactly n nodes of unique
    values from 1 to n. Return the answer in any order.

    Input: n = 3
    Output: [[1,null,2,null,3],[1,null,3,2],[2,1,3],[3,1,null,null,2],[3,2,null,1]]

    Input: n = 1
    Output: [[1]]

    https://leetcode.com/problems/unique-binary-search-trees-ii/
    Date: 2 Sept 2021
    Fair Oaks, CA.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode **partition(int l, int r, int *size) {
  if (l > r) {
    *size = 1;
    struct TreeNode **arr = calloc(1, sizeof(struct TreeNode *));
    arr[0] = NULL;
    return arr;
  }

  *size = 0;
  struct TreeNode **arr = NULL;
  int index = 0;
  for (int i = l; i <= r; i++) {
    // get the left & right subtree array
    int lsize = 0, rsize = 0;
    struct TreeNode **left = partition(l, i-1, &lsize);
    struct TreeNode **right = partition(i+1, r, &rsize);

    // calculate the increased size (numbers of combinations)
    *size += rsize * lsize;
    arr = realloc(arr, *size * sizeof(struct TreeNode *));

    // merge root/left/right and store to array
    for (int j = 0; j < lsize; j++) {
      for (int k = 0; k < rsize; k++) {
	struct TreeNode **root = &(arr[index++]);
	*root = calloc(1, sizeof(struct TreeNode));
	(*root)->val = i;
	(*root)->left = left[j];
	(*root)->right = right[k];
      }
    }
  }

  return arr;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
struct TreeNode** generateTrees(int n, int* returnSize){
  return partition(1, n, returnSize);
}

int main (int argc, char **argv) {
  int ret = 0;

  debug("Output = %d", ret);
  return 0;
}

/**

 **/
