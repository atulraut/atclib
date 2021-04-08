/***
    https://leetcode.com/problems/inorder-successor-in-bst/
    285. Inorder Successor in BST
    Medium
    Given the root of a binary search tree and a node p in it, return
    the in-order successor of that node in the BST. If the given
    node has no in-order successor in the tree, return null.

    The successor of a node p is the node with the smallest key
    greater than p.val.
    Input: root = [2,1,3], p = 1
    Output: 2
    Explanation: 1's in-order successor node is 2. Note that both p
    and the return value is of TreeNode type

    Input: root = [5,3,6,2,4,null,null,1], p = 6
    Output: null
    Explanation: There is no in-order successor of the current node,
    so the answer is null.

    Constraints:
    The number of nodes in the tree is in the range [1, 104].
    -105 <= Node.val <= 105
    All Nodes will have unique values.

    Date: 4/8/2021 April
    San Diego, CA
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

struct treeNode {
  int val;
  struct treeNode *left;
  struct treeNode *right;
};

struct treeNode* succ;
void inOrderSuccessorNode(struct treeNode* root, struct treeNode* p) {
  if(root == NULL || succ != NULL)
    return;
  inOrderSuccessorNode(root->left, p);
  if(root->val > p->val && succ == NULL) {
    succ = root;
    return;
  }
  inOrderSuccessorNode(root->right, p);
}

struct treeNode* inorderSuccessor(struct treeNode* root, struct treeNode* p) {
  /*
    succ=NULL;
    inOrderSuccessorNode(root,p);
    return succ;
  */
  succ = NULL;
  while(root) {
    debug ("Reached");
    debug ("Trying =%d", root->val);
    debug ("Sucess!");
    if(root->val > p->val) {
      succ = root;
      root = root->left;
    } else {
      root = root->right;
    }
  }
  return succ;
}

/***
    Fix coredump : Pending
 */
int main () {
  // Input: root = [5,3,6,2,4,null,null,1], p = 6
  struct treeNode rt[6];

  /* Initialize the Tree as per Example 1 above */
  rt[0] = (struct treeNode) {.val=5, .left=NULL, .right=NULL};
  rt[1] = (struct treeNode) {.val=3, .left=NULL, .right=NULL};
  rt[2] = (struct treeNode) {.val=6, .left=NULL, .right=NULL};
  rt[3] = (struct treeNode) {.val=2, .left=NULL, .right=NULL};
  rt[4] = (struct treeNode) {.val=4, .left=NULL, .right=NULL};
  rt[5] = (struct treeNode) {.val=1, .left=NULL, .right=NULL};


  rt[0].left  = &rt[1];  // 1 <-- 0 [0's left]
  rt[0].right = &rt[2];  // 0 --> 3 [0's right]

  rt[1].left  = &rt[3];  // 1 <-- 2 [2's left]
  rt[1].right = &rt[4];

  rt[3].left = &rt[5];

  struct treeNode *output = inorderSuccessor(&rt[0], &rt[2]);
  debug ("output--> %d", output->val);

  printf ("\n");
  return 0;
}

/**
   => ./a.out
   1 ( 2 ( 4 ) ) ( 3 ) - Default
**/
