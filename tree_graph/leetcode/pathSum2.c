/***
    Medium - Path Sum II :
    Given the root of a binary tree and an integer targetSum, return all
    root-to-leaf paths where each path's sum equals targetSum.

    A leaf is a node with no children.

    Input: root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
    Output: [[5,4,11,2],[5,8,4,5]]

    https://leetcode.com/problems/path-sum-ii/

    Date: 4 August 2021
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
 */

struct TreeNode {
  int val;
  struct TreeNode *left;
  struct TreeNode *right;
};

void help(struct TreeNode *root, int sum, int ***res, int *buff, int i, int *rSize, int **cSizes) {
  if (root == NULL)
    return;

  if (sum - root->val == 0 && !root->left && !root->right) {
    *cSizes = realloc(*cSizes, sizeof(int) * (*rSize + 1));
    (*cSizes)[*rSize] = i + 1;
    *res = realloc(*res, sizeof(int *) * (*rSize + 1));
    (*res)[*rSize] = malloc(sizeof(int) * (i + 1));
    memcpy((*res)[*rSize], buff, sizeof(int) * (i + 1));
    (*res)[*rSize][i] = root->val;
    (*rSize)++;
    return;
  }

  buff[i] = root->val;
  help(root->left, sum - root->val, res, buff, i + 1, rSize, cSizes);
  help(root->right, sum - root->val, res, buff, i + 1, rSize, cSizes);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** pathSum(struct TreeNode* root, int targetSum, int* returnSize, int** returnColumnSizes) {
  *returnSize = 0;
  int **res = NULL;
  *returnColumnSizes = NULL;
  int *buff = calloc(1001, sizeof(int));

  help(root, targetSum, &res, buff, 0, returnSize, returnColumnSizes);

  return res;
}

int main () {
  int ret = 0;
  int targetSum = 22;
  int returnSize;
  int* returnColumnSizes;
  struct TreeNode rt[10];

  rt[0] = (struct TreeNode){.val=5, .left=NULL, .right=NULL};
  rt[1] = (struct TreeNode){.val=4, .left=NULL, .right=NULL};
  rt[2] = (struct TreeNode){.val=8, .left=NULL, .right=NULL};
  rt[3] = (struct TreeNode){.val=11, .left=NULL, .right=NULL};
  rt[4] = (struct TreeNode){.val=13, .left=NULL, .right=NULL};
  rt[5] = (struct TreeNode){.val=4, .left=NULL, .right=NULL};
  rt[6] = (struct TreeNode){.val=7, .left=NULL, .right=NULL};
  rt[7] = (struct TreeNode){.val=2, .left=NULL, .right=NULL};
  rt[8] = (struct TreeNode){.val=5, .left=NULL, .right=NULL};
  rt[9] = (struct TreeNode){.val=1, .left=NULL, .right=NULL};

  rt[0].left = &rt[1];
  rt[0].right= &rt[2];

  rt[1].left = &rt[3];

  rt[2].left = &rt[4];
  rt[2].right= &rt[5];

  rt[3].left = &rt[6];
  rt[3].right= &rt[7];

  rt[5].left = &rt[8];
  rt[5].right= &rt[9];

  int **op = pathSum(rt, targetSum, &returnSize, &returnColumnSizes);

  for(int i=0; i<returnSize; ++i) {
    for(int j=0; j<*returnColumnSizes; ++j) {
      debug("Output = %d", op[i][j]);
    }
    debug("____ End ____");
  }
  return 0;
}

/**
   => ./a.out
   [main] L=112 :Output = 5
   [main] L=112 :Output = 4
   [main] L=112 :Output = 11
   [main] L=112 :Output = 2
   [main] L=114 :____ End ____
   [main] L=112 :Output = 5
   [main] L=112 :Output = 8
   [main] L=112 :Output = 4
   [main] L=112 :Output = 5
   [main] L=114 :____ End ____
**/
