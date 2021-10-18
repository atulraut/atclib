/***
    https://leetcode.com/problems/cousins-in-binary-tree/
    Cousins in Binary Tree

    Given the root of a binary tree with unique values and
    the values of two different nodes of the tree x and y,
    return true if the nodes corresponding to the values x
    and y in the tree are cousins, or false otherwise.

    Two nodes of a binary tree are cousins if they have the
    same depth with different parents.

    Note that in a binary tree, the root node is at the depth
    0, and children of each depth k node are at the depth k + 1.

    Input: root = [1,2,3,4], x = 4, y = 3
    Output: false

    Input: root = [1,2,3,null,4,null,5], x = 5, y = 4
    Output: true
    Example 3:

    Input: root = [1,2,3,null,4], x = 2, y = 3
    Output: false

    Constraints:
    The number of nodes in the tree is in the range [2, 100].
    1 <= Node.val <= 100
    Each node has a unique value.
    x != y
    x and y are exist in the tree.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings isCousins.c -lm

    Date: 18 Oct 2021
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

void dfs(struct TreeNode* node, int Parent, int Depth, int x, int *xDepth, int *xParent, int y, int *yDepth, int *yParent) {
  if(!node)
    return;

  if(x==node->val) {
    *xDepth = Depth;
    *xParent = Parent;
  } else if(y==node->val) {
    *yDepth = Depth;
    *yParent = Parent;
  }

  if(*xDepth!=-1 && *yDepth!=-1)
    return;

  dfs(node->left, node->val, Depth+1, x, xDepth, xParent, y, yDepth, yParent);
  dfs(node->right, node->val, Depth+1, x, xDepth, xParent, y, yDepth, yParent);
}

bool isCousins(struct TreeNode* root, int x, int y) {
  int xDepth=-1, xParent=0, yDepth=-1, yParent=0;

  dfs(root, 0, 0, x, &xDepth, &xParent, y, &yDepth, &yParent);

  return xDepth==yDepth && xParent!=yParent;
}

int main (int argc, char **argv) {
  int ret = 0;
  int x = 5;
  int y = 4;
  struct TreeNode rt[5];

  rt[0] = (struct TreeNode){.val=1, .left=NULL, .right=NULL};
  rt[1] = (struct TreeNode){.val=2, .left=NULL, .right=NULL};
  rt[2] = (struct TreeNode){.val=3, .left=NULL, .right=NULL};
  rt[3] = (struct TreeNode){.val=4, .left=NULL, .right=NULL};
  rt[4] = (struct TreeNode){.val=5, .left=NULL, .right=NULL};

  rt[0].left = &rt[1];
  rt[0].right= &rt[2];

  rt[1].right = &rt[3];
  rt[2].right= &rt[4];

  ret = isCousins(rt, x, y);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=109 :Output = 1
**/
