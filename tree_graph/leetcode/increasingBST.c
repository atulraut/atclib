/***
    https://leetcode.com/problems/increasing-order-search-tree
    ncreasing Order Search Tree

    Given the root of a binary search tree, rearrange the tree
    in in-order so that the leftmost node in the tree is now the
    root of the tree, and every node has no left child and only one right child.

    Input: root = [5,3,6,2,4,null,8,1,null,null,null,7,9]
    Output: [1,null,2,null,3,null,4,null,5,null,6,null,7,null,8,null,9]

    Input: root = [5,1,7]
    Output: [1,null,5,null,7]

    Constraints:
    The number of nodes in the given tree will be in the range [1, 100].
    0 <= Node.val <= 1000

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 27 Nov 2021
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

struct TreeNode* increasingBST(struct TreeNode* root) {
  if(root->right)
    root->right=increasingBST(root->right);

  if(root->left) {
    root->left=increasingBST(root->left);
    struct TreeNode*temp=root->left;
    struct TreeNode*next=temp->right;
    while(next) {
      temp=next;
      next=next->right;
    }
    next=root->left;
    temp->right=root;
    root->left=NULL;
    return next;
  }
  return root;
}

int main (int argc, char **argv) {
  struct TreeNode rt[3];

  rt[0] = (struct TreeNode){.val=5, .left=NULL, .right=NULL};
  rt[1] = (struct TreeNode){.val=1, .left=NULL, .right=NULL};
  rt[2] = (struct TreeNode){.val=2, .left=NULL, .right=NULL};

  rt[0].left = &rt[1];
  rt[0].right= &rt[2];

  struct TreeNode* ret = increasingBST(rt);
  //  debug("Output = %d", ret);
  return 0;
}

/**

 **/
