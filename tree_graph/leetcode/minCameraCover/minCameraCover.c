/***
    Hard: 968. Binary Tree Cameras
    https://leetcode.com/problems/binary-tree-cameras/

    Given a binary tree, we install cameras on the nodes of the tree.
    Each camera at a node can monitor its parent, itself, and its immediate children.
    Calculate the minimum number of cameras needed to monitor all nodes of the tree.

    Input: [0,0,null,0,0]
    Output: 1
    Explanation: One camera is enough to monitor all nodes if placed as shown.

    Input: [0,0,null,0,null,0,null,null,0]
    Output: 2
    Explanation: At least two cameras are needed to monitor all nodes of the tree.
    The above image shows one of the valid configurations of camera placement.


    Note:
    The number of nodes in the given tree will be in the range [1, 1000].
    Every node has value 0.

    Date: 17 May 2021.
    San Diego, CA.
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
#define minx(((x) < (y)) ? x : y)

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
  int val;
  struct TreeNode *left;
  struct TreeNode *right;
};

// 0: Strict ST; All nodes below this are covered, but not this one
// 1: Normal ST; All nodes below and incl this are covered - no camera
// 2: Placed camera; All nodes below this are covered, plus camera here
int* solve(TreeNode node) {
  if (node == null)
    return TreeNode node = (TreeNode node)(sizeof(TreeNode) * 99999); //new int[]{0, 0, 99999};

  int[] L = solve(node.left);
  int[] R = solve(node.right);
  int mL12 = min(L[1], L[2]);
  int mR12 = min(R[1], R[2]);

  int d0 = L[1] + R[1];
  int d1 = min(L[2] + mR12, R[2] + mL12);
  int d2 = 1 + min(L[0], mL12) + Math.min(R[0], mR12);
  return new int[]{d0, d1, d2};
}

public int minCameraCover(TreeNode root) {
  int* ans = solve(root);
  return Math.min(ans[1], ans[2]);
}

int minCameraCover(struct TreeNode* root){

}

int main () {
  int ret = 0;
  struct tree_node rt[4];

  rt[0] = (struct tree_node) {.val=0, .left=NULL, .right=NULL};
  rt[1] = (struct tree_node) {.val=0, .left=NULL, .right=NULL};
  rt[2] = (struct tree_node) {.val=0, .left=NULL, .right=NULL};
  rt[3] = (struct tree_node) {.val=0, .left=NULL, .right=NULL};

  rt[0].left  = &rt[1];
  rt[1].left  = &rt[2];
  rt[1].right = &rt[3];

  debug("Output = %d", ret);
  return 0;
}

/**

 **/
