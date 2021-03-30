/***
    971. Flip Binary Tree To Match Preorder Traversal
    https://leetcode.com/problems/flip-binary-tree-to-match-preorder-traversal/
    You are given the root of a binary tree with n nodes, where
    each node is uniquely assigned a value from 1 to n. You are
    also given a sequence of n values voyage, which is the desired
    pre-order traversal of the binary tree.

    Any node in the binary tree can be flipped by swapping its left
    and right subtrees. For example, flipping node 1 will have the
    following effect:

    Input: root = [1,2,3], voyage = [1,3,2]
    Output: [1]
    Explanation: Flipping node 1 swaps nodes 2 and 3, so the pre-order
    traversal matches voyage.

    Date : 29 March 2021
    San Diego, CA
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

/***
    In case File Debug Option needs to Enabled.
*/
//#define debug(str,args...) printf("[%s] [%s()] L=%d :"str"\n",__FILE__, __func__, __LINE__, ##args)

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

/* Definition for a binary tree node. */
struct TreeNode {
  int val;
  struct TreeNode *left;
  struct TreeNode *right;
};

#define ARRAY_SIZE 100UL
static int flippedArray[ARRAY_SIZE] = {0};
static int fIndex = 0;

int preorderTraverse(struct TreeNode *node, int *voyage, int voyageSize, int *index) {
  int ret = 0;
  struct TreeNode *tmp = NULL;
  int index_bak = *index;
  bool flipped = false;

  if (*index >= voyageSize || NULL == node)
    return 0;

  if (node->val != voyage[*index])
    return -1;

 flip: // swap
  if (flipped) {
    tmp = node->left;
    node->left = node->right;
    node->right = tmp;
  }

  *index = index_bak + 1;
  ret = preorderTraverse(node->left, voyage, voyageSize, index);
  if (-1 == ret) {
    if (!flipped) {
      flipped = true;
      goto flip;
    }
    else {
      return -1;
    }
  }

  ret = preorderTraverse(node->right, voyage, voyageSize, index);
  if (-1 == ret) {
    if (!flipped) {
      flipped = true;
      goto flip;
    }
    else {
      return -1;
    }
  }

  if (flipped) {
    flippedArray[fIndex++] = node->val;
  }

  return 0;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* flipMatchVoyage(struct TreeNode* root, int* voyage, int voyageSize, int* returnSize) {
  int index = 0;
  int ret = 0;

  fIndex = 0;
  *returnSize = 1;

  ret = preorderTraverse(root, voyage, voyageSize, &index);
  if (-1 != ret)
    *returnSize = fIndex;
  else
    flippedArray[0] = -1;

  return flippedArray;
}

int main () {
  int voyage[] = {1, 3, 2};
  int voyageSize = 3;
  int returnSize;
  struct TreeNode rt[4];

  /* Initialize the Tree as per Example 1 above */
  rt[0] = (struct TreeNode) {.val=1, .left=NULL, .right=NULL};
  rt[1] = (struct TreeNode) {.val=2, .left=NULL, .right=NULL};
  rt[2] = (struct TreeNode) {.val=3, .left=NULL, .right=NULL};
  // rt[3] = (struct TreeNode) {.val=4, .left=NULL, .right=NULL};

  rt[0].left  = &rt[1];  // 1 <-- 0 [0's left]
  rt[0].right = &rt[2];  // 0 --> 3 [0's right]
  //  rt[1].left  = &rt[3];  // 1 <-- 2 [2's left]

  //preorder (rt, 0);
  int*op =  flipMatchVoyage(rt, voyage, voyageSize, &returnSize);

  debug ("retSize = %d", returnSize);
  for (int i=0; i<returnSize; i++) {
    printf ("--> %d", op[i]);
    //debug ("--> %c", ret[i]);
  }
  printf ("\n");
  return 0;
}

/**
   => ./a.out
   [main] L=137 :retSize = 1
   --> 1
**/
