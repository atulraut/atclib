/***
    https://leetcode.com/problems/delete-node-in-a-bst/
    Delete Node in a BST

    Given a root node reference of a BST and a key, delete the
    node with the given key in the BST. Return the root node
    reference (possibly updated) of the BST.

    Basically, the deletion can be divided into two stages:

    Search for a node to remove.
    If the node is found, delete the node.

    Input: root = [5,3,6,2,4,null,7], key = 3
    Output: [5,4,6,2,null,null,7]
    Explanation: Given key to delete is 3. So we find the node with value 3 and delete it.
    One valid answer is [5,4,6,2,null,null,7], shown in the above BST.
    Please notice that another valid answer is [5,2,6,null,4,null,7] and it's also accepted.

    Input: root = [5,3,6,2,4,null,7], key = 0
    Output: [5,3,6,2,4,null,7]
    Explanation: The tree does not contain a node with value = 0.
    Example 3:

    Input: root = [], key = 0
    Output: []

    Constraints:
    The number of nodes in the tree is in the range [0, 104].
    -105 <= Node.val <= 105
    Each node has a unique value.
    root is a valid binary search tree.
    -105 <= key <= 105

    Date: 22 Nov 2021
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

void add_right_most_leaf(struct TreeNode *node, struct TreeNode *new) {
  while (node->right)
    node = node->right;
  node->right = new;
}

void del_node(struct TreeNode **root, struct TreeNode *node, struct TreeNode *parent) {
  struct TreeNode **_parent;
  if (parent)
    _parent = node->val < parent->val ? &parent->left : &parent->right;
  else
    _parent = root;

  if (!node->left) {
    *_parent = node->right;
  } else if (!node->right) {
    *_parent = node->left;
  } else {
    struct TreeNode *tmp = node->right->left;
    node->right->left = node->left;
    add_right_most_leaf(node->right->left, tmp);
    *_parent = node->right;
    free(node);
  }
}

struct TreeNode* deleteNode(struct TreeNode* root, int key) {
  struct TreeNode *node = root;
  struct TreeNode *parent = NULL;

  while (node) {
    if (node->val > key) {
      parent = node;
      node = node->left;
    } else if (node->val < key) {
      parent = node;
      node = node->right;
    } else {
      del_node(&root, node, parent);
      break;
    }
  }

  return root;
}

int main (int argc, char **argv) {
  struct TreeNode *ret;
  struct TreeNode rt[7];

  rt[0] = (struct TreeNode){.val=5, .left=NULL, .right=NULL};
  rt[1] = (struct TreeNode){.val=3, .left=NULL, .right=NULL};
  rt[2] = (struct TreeNode){.val=6, .left=NULL, .right=NULL};
  rt[3] = (struct TreeNode){.val=2, .left=NULL, .right=NULL};
  rt[4] = (struct TreeNode){.val=4, .left=NULL, .right=NULL};
  rt[5] = (struct TreeNode){.left=NULL, .right=NULL};
  rt[6] = (struct TreeNode){.val=7, .left=NULL, .right=NULL};

  rt[0].left = &rt[1];
  rt[0].right= &rt[2];

  rt[1].left = &rt[3];
  rt[1].right = &rt[4];

  rt[2].right= &rt[6];

  ret = deleteNode(rt, 3);
  // debug("Output = %d", ret);
  return 0;
}

/**

**/
