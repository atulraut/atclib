/***
    Medium: 114. Flatten Binary Tree to Linked List
    https://leetcode.com/problems/flatten-binary-tree-to-linked-list/

    Given the root of a binary tree, flatten the tree into a "linked list":

    The "linked list" should use the same TreeNode class where the right
    child pointer points to the next node in the list and the left
    child pointer is always null.
    The "linked list" should be in the same order as a pre-order traversal
    of the binary tree.

    Input: root = [1,2,5,3,4,null,6]
    Output: [1,null,2,null,3,null,4,null,5,null,6]

    Input: root = []
    Output: []

    Input: root = [0]
    Output: [0]

    Constraints:
    The number of nodes in the tree is in the range [0, 2000].
    -100 <= Node.val <= 100

    Follow up: Can you flatten the tree in-place (with O(1) extra space)?

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

void flatten(struct TreeNode* root){
  if(root) {
    struct TreeNode* flat_tree = root->right;

    flatten(root->left);
    flatten(root->right);

    root->right = root->left;
    root->left = NULL;
    while(root->right) {
      root = root->right;
    }

    root->right = flat_tree;
  }
}

struct TreeNode* flatten1(struct TreeNode *root) {
  if(root->left && root->right) {
    struct TreeNode *temp,*temp1;
    temp1 = flatten1(root->right);
    temp = flatten1(root->left);
    temp->right = root->right;
    root->right = root->left;
    root->left = NULL;
    return temp1;
  }

  if(!root->left && root->right)
    return flatten1(root->right);

  if(root->left && !root->right) {
    struct TreeNode *temp=flatten1(root->left);
    root->right = root->left;
    root->left = NULL;
    return temp;
  }
  else
    return root;
}

/* 4ms : */
void flatten_Recur(struct TreeNode* root) {
  if(!root)
    return;
  else
    flatten1(root);

}

int main () {
  int ret = 0;

  debug("Output = %d", ret);
  return 0;
}

/**

 **/
