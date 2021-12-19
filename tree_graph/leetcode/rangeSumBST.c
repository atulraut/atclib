/***
    https://leetcode.com/problems/range-sum-of-bst/
    Range Sum of BST

    Given the root node of a binary search tree and two
    integers low and high, return the sum of values of
    all nodes with a value in the inclusive range [low, high].

    Input: root = [10,5,15,3,7,null,18], low = 7, high = 15
    Output: 32
    Explanation: Nodes 7, 10, and 15 are in the range [7, 15]. 7 + 10 + 15 = 32.

    Input: root = [10,5,15,3,7,13,18,1,null,6], low = 6, high = 10
    Output: 23
    Explanation: Nodes 6, 7, and 10 are in the range [6, 10]. 6 + 7 + 10 = 23.


    Constraints:
    The number of nodes in the tree is in the range [1, 2 * 104].
    1 <= Node.val <= 105
    1 <= low <= high <= 105
    All Node.val are unique.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 12/18/2021 - Day 1 Ridvi
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

int rangeSumBST(struct TreeNode* root, int low, int high) {
  if (!root) {
    return 0;
  }

  if(root->val<low) {
    return rangeSumBST(root->right, low, high);
  }

  if(root->val>high) {
    return rangeSumBST(root->left, low, high);
  }
  return root->val + rangeSumBST(root->left,  low, high) + rangeSumBST(root->right, low, high);
}

int main (int argc, char **argv) {
  int ret = 0;
  int low = 7;
  int high = 15;
  struct TreeNode rt[6];

  rt[0] = (struct TreeNode){.val=10, .left=NULL, .right=NULL};
  rt[1] = (struct TreeNode){.val=5, .left=NULL, .right=NULL};
  rt[2] = (struct TreeNode){.val=15, .left=NULL, .right=NULL};
  rt[3] = (struct TreeNode){.val=3, .left=NULL, .right=NULL};
  rt[4] = (struct TreeNode){.val=7, .left=NULL, .right=NULL};
  rt[5] = (struct TreeNode){.val=18, .left=NULL, .right=NULL};

  rt[0].left = &rt[1];
  rt[0].right= &rt[2];
  rt[1].left = &rt[3];
  rt[1].right= &rt[4];
  rt[2].right= &rt[5];

  ret = rangeSumBST(rt, low, high);
  debug("Output = %d", ret);

  return 0;
}

/**
   => ./a.out
   [main] L=100 :Output = 32
**/
