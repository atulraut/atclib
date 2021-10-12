/***
    https://leetcode.com/problems/diameter-of-binary-tree/
    Diameter of Binary Tree

     Given the root of a binary tree, return the length of
     the diameter of the tree.

     The diameter of a binary tree is the length of the
     longest path between any two nodes in a tree. This path
     may or may not pass through the root.

     The length of a path between two nodes is represented by
     the number of edges between them.

     Input: root = [1,2,3,4,5]
     Output: 3
     Explanation: 3 is the length of the path [4,2,1,3] or [5,2,1,3].

     Input: root = [1,2]
     Output: 1

     Constraints:
     The number of nodes in the tree is in the range [1, 104].
     -100 <= Node.val <= 100

    Date: 11 Oct 2021
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
struct tree_node {
  int val;
  struct tree_node *left;
  struct tree_node *right;
};

int max;

int preorder(struct tree_node *node) {
  int ld, rd, dia;

  if (!node)
    return 0;
  ld = preorder(node->left);
  rd = preorder(node->right);

  dia = ld + rd + 1;
  if (dia > max)
    max = dia;

  return ((ld>rd) ? ld+1 : rd+1);
}


int diameterOfBinaryTree(struct tree_node* root) {
  int x;

  if (!root)
    return 0;
  max=0;
  x= preorder(root);
  return ((x>max) ? x-1 : max-1);
}

int main (int argc, char **argv) {
  int ret = 0;
struct tree_node rt[5];

  rt[0] = (struct tree_node) {.val=1, .left=NULL, .right=NULL};
  rt[1] = (struct tree_node) {.val=2, .left=NULL, .right=NULL};
  rt[2] = (struct tree_node) {.val=3, .left=NULL, .right=NULL};
  rt[3] = (struct tree_node) {.val=4, .left=NULL, .right=NULL};
  rt[4] = (struct tree_node) {.val=5, .left=NULL, .right=NULL};

  rt[0].left  = &rt[1];  // 1 <-- 0 [0's left]
  rt[0].right = &rt[2];  // 0 --> 3 [0's right]
  rt[1].left  = &rt[3];  // 1 <-- 2 [1's left]
  rt[1].right  = &rt[4];  // 1 <-- 2 [1's right]

  ret =  diameterOfBinaryTree(rt);
  debug("Output = %d", ret);
  return 0;
}

/**
 // Input
 1
 / \
 2  3
 / \
 4   5
**/

/**
   => ./a.out
   [main] L=102 :Output = 3
**/
