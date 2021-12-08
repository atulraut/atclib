/***
    https://leetcode.com/problems/binary-tree-tilt
    Binary Tree Tilt

    Given the root of a binary tree, return the sum of every tree node's tilt.

    The tilt of a tree node is the absolute difference between the
    sum of all left subtree node values and all right subtree node values.
    If a node does not have a left child, then the sum of the left
    subtree node values is treated as 0. The rule is similar if there the
    node does not have a right child.

    Input: root = [1,2,3]
    Output: 1
    Explanation:
    Tilt of node 2 : |0-0| = 0 (no children)
    Tilt of node 3 : |0-0| = 0 (no children)
    Tilt of node 1 : |2-3| = 1 (left subtree is just left child, so sum is 2;
    right subtree is just right child, so sum is 3)
    Sum of every tilt : 0 + 0 + 1 = 1
    Example 2:

    Input: root = [4,2,9,3,5,null,7]
    Output: 15
    Explanation:
    Tilt of node 3 : |0-0| = 0 (no children)
    Tilt of node 5 : |0-0| = 0 (no children)
    Tilt of node 7 : |0-0| = 0 (no children)
    Tilt of node 2 : |3-5| = 2 (left subtree is just left child, so sum is 3;
    right subtree is just right child, so sum is 5)
    Tilt of node 9 : |0-7| = 7 (no left child, so sum is 0;
    right subtree is just right child, so sum is 7)
    Tilt of node 4 : |(3+5+2)-(9+7)| = |10-16| = 6 (left subtree values
    are 3, 5, and 2, which sums to 10; right subtree values are 9 and 7, which sums to 16)
    Sum of every tilt : 0 + 0 + 0 + 2 + 7 + 6 = 15

    Input: root = [21,7,14,1,1,2,2,3,3]
    Output: 9

    Constraints:
    The number of nodes in the tree is in the range [0, 104].
    -1000 <= Node.val <= 1000

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 12/8/2021
    Folsom, CA.
*/

/*----------------------------------- Header --------------------------------------*/
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

/*----------------------------------- Micro --------------------------------------*/
#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)
#define atsizeof(object) (char *)(&object+1) - (char*)(&object)
#define arrsz(x)  (sizeof(x) / sizeof((x)[0]))
#define max(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a > _b ? _a : _b; })
#define min(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
  int val;
  struct TreeNode *left;
  struct TreeNode *right;
};

int aux(struct TreeNode* root);
int count;

int findTilt(struct TreeNode* root) {
  count = 0;
  int var = aux(root);
  return count;
}

int aux(struct TreeNode* root) {
  if(root == NULL) {
    return 0;
  }

  if(root->left == NULL && root->right == NULL) {
    return root->val;
  }

  int left = aux(root->left);
  int right = aux(root->right);

  if(left >= right) {
    count += left-right;
  } else {
    count += right-left;
  }
  return left+right+root->val;
}

static int total_tilt;
static int visit(struct TreeNode *node) {
  int left, right, tilt;
  if (!node)
    return 0;
  left  = visit(node->left);
  right = visit(node->right);
  tilt  = left - right;
  tilt  = tilt < 0 ? -tilt : tilt;
  total_tilt += tilt;
  return left + right + node->val;
}


int findTilt1(struct TreeNode *root) {
  total_tilt = 0;
  visit(root);
  return total_tilt;
}

int tree_tilt = 0;
int node_sum(struct TreeNode *root) {
  int node_tilt,left_sum = 0, right_sum = 0;
  if (root != NULL)
    {
      left_sum = node_sum(root->left);
      right_sum = node_sum(root->right);
      node_tilt = abs(left_sum - right_sum);
      tree_tilt+=node_tilt;
      return(root->val + left_sum + right_sum);
    }
  else
    return(0);
}

int findTilt2(struct TreeNode* root) {
  tree_tilt=0;
  node_sum(root);
  return(tree_tilt);
}

int main (int argc, char **argv) {
  int ret = 0;
 struct TreeNode rt[3];

  rt[0] = (struct TreeNode) {.val=1, .left=NULL, .right=NULL};
  rt[1] = (struct TreeNode) {.val=2, .left=NULL, .right=NULL};
  rt[2] = (struct TreeNode) {.val=3, .left=NULL, .right=NULL};

  rt[0].left  = &rt[1];  // 1 <-- 0 [0's left]
  rt[0].right = &rt[2];  // 0 --> 3 [0's right]

  ret = findTilt(rt);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=167 :Output = 1
**/
