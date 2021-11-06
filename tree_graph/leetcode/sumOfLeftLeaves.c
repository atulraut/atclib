/***
    https://leetcode.com/problems/sum-of-left-leaves/
    Sum of Left Leaves

    Given the root of a binary tree, return the sum of all left leaves.

    Input: root = [3,9,20,null,null,15,7]
    Output: 24
    Explanation: There are two left leaves in the binary tree,
    with values 9 and 15 respectively.

    Input: root = [1]
    Output: 0

    Constraints:

    The number of nodes in the tree is in the range [1, 1000].
    -1000 <= Node.val <= 1000

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address sumOfLeftLeaves.c -lm

    Date: 5 Nov 2021
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

void helper(struct TreeNode* root, int* sum, bool indentifier) {
  if(root == NULL)
    return;
  if (indentifier && !root->left && !root->right)
    *sum += root->val;
  else {
    helper(root->left, sum, true);
    helper(root->right, sum, false);
  }
}

int sumOfLeftLeaves(struct TreeNode* root) {
  int* ans = malloc(sizeof(int));
  *ans = 0;
  helper(root, ans, false);
  return *ans;
}

int main (int argc, char **argv) {
  int ret = 0;
  struct TreeNode rt[5];

  rt[0] = (struct TreeNode){.val=3,  .left=NULL, .right=NULL};
  rt[1] = (struct TreeNode){.val=9,  .left=NULL, .right=NULL};
  rt[2] = (struct TreeNode){.val=20, .left=NULL, .right=NULL};
  rt[3] = (struct TreeNode){.val=15, .left=NULL, .right=NULL};
  rt[4] = (struct TreeNode){.val=7,  .left=NULL, .right=NULL};

  rt[0].left = &rt[1];
  rt[0].right= &rt[2];

  rt[2].left = &rt[3];
  rt[2].right= &rt[4];

  ret =  sumOfLeftLeaves(rt);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=95 :Output = 24
**/
