/***
    https://leetcode.com/problems/sum-of-root-to-leaf-binary-numbers/
    1022. Sum of Root To Leaf Binary Numbers

    You are given the root of a binary tree where each node has a
    value 0 or 1. Each root-to-leaf path represents a binary number
    starting with the most significant bit.

    For example, if the path is 0 -> 1 -> 1 -> 0 -> 1, then this
    could represent 01101 in binary, which is 13.
    For all leaves in the tree, consider the numbers represented
    by the path from the root to that leaf. Return the sum of these numbers.

    The test cases are generated so that the answer fits in a 32-bits integer.

    Input: root = [1,0,1,0,1,0,1]
    Output: 22
    Explanation: (100) + (101) + (110) + (111) = 4 + 5 + 6 + 7 = 22

    Input: root = [0]
    Output: 0

    Constraints:

    The number of nodes in the tree is in the range [1, 1000].
    Node.val is 0 or 1.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Jan 10, 2022
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
#define max(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a > _b ? _a : _b; })
#define min(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
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

int dfs(struct TreeNode* root, int val) {
  if (root == NULL)
    return 0;

  val = (val << 1) + root->val;

  if (root->left == NULL && root->right == NULL)
    return val;

  return dfs(root->left,  val) +
    dfs(root->right, val);
}

int sumRootToLeaf(struct TreeNode* root){
  return dfs(root, 0);
}

void test() {
  int ret = 0;
  // 1,0,1,0,1,0,1
  struct TreeNode rt[7];

  rt[0] = (struct TreeNode){.val=1, .left=NULL, .right=NULL};
  rt[1] = (struct TreeNode){.val=0, .left=NULL, .right=NULL};
  rt[2] = (struct TreeNode){.val=1, .left=NULL, .right=NULL};
  rt[3] = (struct TreeNode){.val=0, .left=NULL, .right=NULL};
  rt[4] = (struct TreeNode){.val=1, .left=NULL, .right=NULL};
  rt[5] = (struct TreeNode){.val=0, .left=NULL, .right=NULL};
  rt[6] = (struct TreeNode){.val=1, .left=NULL, .right=NULL};

  rt[0].left = &rt[1];
  rt[0].right= &rt[2];

  rt[1].left = &rt[3];
  rt[1].right= &rt[4];

  rt[2].left = &rt[5];
  rt[2].right= &rt[6];

  ret = sumRootToLeaf(rt);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [test] L=109 :Output = 22
**/
