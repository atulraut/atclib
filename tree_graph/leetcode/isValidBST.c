/***
    https://leetcode.com/problems/validate-binary-search-tree/solution/

    Validate Binary Search Tree

    Given the root of a binary tree, determine if it is a valid binary search tree (BST).
    A valid BST is defined as follows:
    The left subtree of a node contains only nodes with keys less than the node's key.
    The right subtree of a node contains only nodes with keys greater than the node's key.
    Both the left and right subtrees must also be binary search trees.

    Input: root = [2,1,3]
    Output: true

    Input: root = [5,1,4,null,null,3,6]
    Output: false
    Explanation: The root node's value is 5 but its right child's value is 4.

    Constraints:
    The number of nodes in the tree is in the range [1, 104].
    -2^31 <= Node.val <= 2^31 - 1

    Date : Wed Aug 10 07:29:51 PM PDT 2022

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

/***
    In case File Debug Option needs to Enabled.
*/
//#define debug(str,args...) printf("[%s] [%s()] L=%d :"str"\n",__FILE__, __func__, __LINE__, ##args)

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

struct tree_node {
  int val;
  struct tree_node *left;
  struct tree_node *right;
};

bool validate(struct tree_node* root, struct tree_node* low, struct tree_node* high) {
  //  debug ("root->val = %d", root->val);
  // Empty trees are valid BSTs.
  if (root == NULL) {
    debug ("Enter");
    return true;
  }

  // The current node's value must be between low and high.
  if ((low != NULL && root->val <= low->val) ||
      (high != NULL && root->val >= high->val)) {
    debug ("Enter");
    return false;
  }

  // The left and right subtree must also be valid.
  return validate(root->right, root, high) &&
    validate(root->left, low, root);
}

bool isValidBST(struct tree_node* root){
  return validate(root, NULL, NULL);
}

static struct tree_node rt[3];
int main () {
  //  struct tree_node rt[7];

  /* Initialize the Tree as per Example 1 above */
  rt[0] = (struct tree_node) {.val=2, .left=NULL, .right=NULL};
  rt[1] = (struct tree_node) {.val=1, .left=NULL, .right=NULL};
  rt[2] = (struct tree_node) {.val=3, .left=NULL, .right=NULL};

  //  rt[3] = (struct tree_node) {.val=0, .left=NULL, .right=NULL};
  //  rt[4] = (struct tree_node) {.val=0, .left=NULL, .right=NULL};
  /*
    rt[5] = (struct tree_node) {.val=3, .left=NULL, .right=NULL};
    rt[6] = (struct tree_node) {.val=6, .left=NULL, .right=NULL};
  */

  rt[0].left  = &rt[1];  // 5 <-- 1 [0's left]
  rt[0].right = &rt[2];  // 5 --> 4 [0's right]

  //rt[2].left  = &rt[5];  // 4 <-- 3 [2's left]
  //  rt[2].right = &rt[6];  // 4 <-- 6
  //preorder (rt, 0);
  int ret = isValidBST(rt);

  debug ("Ret --> %d", ret);

  printf ("\n");
  return 0;
}

/***
    Complexity Analysis

    Time complexity : O(N) since we visit each node exactly once.
    Space complexity : O(N) since we keep up to the entire tree.

*/
/**
   > ./a.out
   [validate] L=54 :Enter
   [validate] L=54 :Enter
   [validate] L=54 :Enter
   [validate] L=54 :Enter
   [main] L=98 :Ret --> 1
**/

