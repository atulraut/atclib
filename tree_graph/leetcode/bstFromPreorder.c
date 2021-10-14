/***
    https://leetcode.com/problems/construct-binary-search-tree-from-preorder-traversal/
    Construct Binary Search Tree from Preorder Traversal

    Given an array of integers preorder, which represents the
    preorder traversal of a BST (i.e., binary search tree),
    construct the tree and return its root.

    It is guaranteed that there is always possible to find
    a binary search tree with the given requirements for
    the given test cases.

    A binary search tree is a binary tree where for every node,
    any descendant of Node.left has a value strictly less
    than Node.val, and any descendant of Node.right has a
    value strictly greater than Node.val.

    A preorder traversal of a binary tree displays the
    value of the node first, then traverses Node.left,
    then traverses Node.right.

    Input: preorder = [8,5,1,7,10,12]
    Output: [8,5,10,1,7,null,12]

    Input: preorder = [1,3]
    Output: [1,null,3]

    Constraints:
    1 <= preorder.length <= 100
    1 <= preorder[i] <= 1000
    All the values of preorder are unique.

    Date: 14 Oct 2021
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

struct TreeNode* bstFromPreorder(int* preorder, int preorderSize) {
  struct TreeNode *new;
  int left_ptr;

  new = malloc(sizeof(struct TreeNode));
  new->val = preorder[0];

  if (preorderSize == 1) {
    new->right = NULL;
    new->left = NULL;
    return new;
  }

  left_ptr=1;
  while ((left_ptr < preorderSize) && (preorder[left_ptr] < preorder[0]))
    left_ptr++;

  if (left_ptr == 1)
    new->left = NULL;
  else
    new->left = bstFromPreorder(preorder+1,left_ptr-1);

  if (left_ptr<preorderSize)
    new->right = bstFromPreorder(preorder+left_ptr,preorderSize-left_ptr);
  else
    new->right = NULL;

  return new;
}

int main (int argc, char **argv) {
  int ret = 0;
  struct TreeNode rt[6];

  rt[0] = (struct TreeNode){.val=8, .left=NULL, .right=NULL};
  rt[1] = (struct TreeNode){.val=5, .left=NULL, .right=NULL};
  rt[2] = (struct TreeNode){.val=10, .left=NULL, .right=NULL};
  rt[3] = (struct TreeNode){.val=7, .left=NULL, .right=NULL};
  rt[4] = (struct TreeNode){.val=10, .left=NULL, .right=NULL};
  rt[5] = (struct TreeNode){.val=12, .left=NULL, .right=NULL};

  rt[0].left = &rt[1];
  rt[0].right= &rt[2];

  rt[1].left = &rt[3];

  rt[2].left = &rt[4];
  rt[2].right= &rt[5];

  rt[3].left = &rt[6];
  rt[3].right= &rt[7];

  rt[5].left = &rt[8];
  rt[5].right= &rt[9];
  //struct TreeNode* bstFromPreorder(int* preorder, int preorderSize)
  debug("Output = %d", ret);
  return 0;
}

/**

 **/
