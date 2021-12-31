/***
    https://leetcode.com/problems/maximum-difference-between-node-and-ancestor
    1026. Maximum Difference Between Node and Ancestor

    Given the root of a binary tree, find the maximum value v for which
    there exist different nodes a and b where v = |a.val - b.val| and a is
    an ancestor of b.

    A node a is an ancestor of b if either: any child of a is equal to b
    or any child of a is an ancestor of b.

    Input: root = [8,3,10,1,6,null,14,null,null,4,7,13]
    Output: 7
    Explanation: We have various ancestor-node differences, some of which are given below :
    |8 - 3| = 5
    |3 - 7| = 4
    |8 - 1| = 7
    |10 - 13| = 3
    Among all possible differences, the maximum value of 7 is obtained by |8 - 1| = 7.

    Input: root = [1,null,2,null,0,3]
    Output: 3

    Constraints:
    The number of nodes in the tree is in the range [2, 5000].
    0 <= Node.val <= 105

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 12/20/2021
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


int helper(struct TreeNode *node, int curMax, int curMin) {
        // if encounter leaves, return the max-min along the path
        if (node == NULL) {
            return curMax - curMin;
        }
        // else, update max and min
        // and return the max of left and right subtrees
        curMax = max(curMax, node->val);
        curMin = min(curMin, node->val);
        int left = helper(node->left, curMax, curMin);
        int right = helper(node->right, curMax, curMin);
        return max(left, right);
}

int maxAncestorDiff(struct TreeNode* root){
    if (root == NULL) {
            return 0;
        }
        return helper(root, root->val, root->val);
}

int main (int argc, char **argv) {
  int ret = 0;

   struct TreeNode rt[9];

  rt[0] = (struct TreeNode){.val=8, .left=NULL, .right=NULL};
  rt[1] = (struct TreeNode){.val=3, .left=NULL, .right=NULL};
  rt[2] = (struct TreeNode){.val=10, .left=NULL, .right=NULL};

  rt[3] = (struct TreeNode){.val=1, .left=NULL, .right=NULL};
  rt[4] = (struct TreeNode){.val=6, .left=NULL, .right=NULL};

  rt[5] = (struct TreeNode){.val=14, .left=NULL, .right=NULL};

  rt[6] = (struct TreeNode){.val=4, .left=NULL, .right=NULL};
  rt[7] = (struct TreeNode){.val=7, .left=NULL, .right=NULL};

  rt[8] = (struct TreeNode){.val=13, .left=NULL, .right=NULL};

  rt[0].left = &rt[1];
  rt[0].right= &rt[2];
  rt[1].left = &rt[3];
  rt[1].right= &rt[4];
  rt[2].right= &rt[5];

  rt[4].left = &rt[6];
  rt[4].right= &rt[7];

  rt[5].left = &rt[8];

  ret = maxAncestorDiff(rt);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=122 :Output = 7
**/
