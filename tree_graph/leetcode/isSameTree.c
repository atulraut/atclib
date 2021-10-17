/***
    https://leetcode.com/problems/same-tree/
    https://leetcode.com/problems/symmetric-tree/
    1] Same Tree
    2] Symmetric Tree

    Given the roots of two binary trees p and q,
    write a function to check if they are the
    same or not.

    Two binary trees are considered the same if
    they are structurally identical, and the nodes
    have the same value.

    Input: p = [1,2,3], q = [1,2,3]
    Output: true

    Input: p = [1,2], q = [1,null,2]
    Output: false

    Input: p = [1,2,1], q = [1,1,2]
    Output: false

    Constraints:
    The number of nodes in both trees is in the range [0, 100].
    -104 <= Node.val <= 104

    status: Pending
    Date: Oct 17, 2021
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
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

bool isSameTree(struct TreeNode* p, struct TreeNode* q){
  if (p == NULL && q == NULL) {
    return true;
  } else if (p == NULL || q == NULL) {
    return false;
  }

  if (p->val == q->val) {
    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
  } else {
    return false;
  }
}

bool parallel_traverse(struct TreeNode* a, struct TreeNode* b) {
    if (a == NULL && b == NULL)
        return true;

    if (a == NULL || b == NULL)
        return false;

    if (a->val != b->val)
        return false;

    return parallel_traverse(a->left, b->right) && parallel_traverse(a->right, b->left);
}

bool isSymmetric(struct TreeNode* root) {
    if (root == NULL)
        return true;
    return parallel_traverse(root->left, root->right);
}

int main (int argc, char **argv) {
  int ret = 0;

  debug("Output = %d", ret);
  return 0;
}


/**
   Complexity Analysis

   Time complexity : \mathcal{O}(N)O(N), where N is a number of nodes in the tree, since one visits each node exactly once.

   Space complexity : \mathcal{O}(\log(N))O(log(N)) in the best case of completely balanced tree and \mathcal{O}(N)O(N) in the worst case of completely unbalanced tree, to keep a recursion stack.
**/

/**

 **/
