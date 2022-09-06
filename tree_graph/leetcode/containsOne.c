/***
    https://leetcode.com/problems/binary-tree-pruning/
    Binary Tree Pruning

    Given the root of a binary tree, return the same
    tree where every subtree (of the given tree) not
    containing a 1 has been removed.

    A subtree of a node node is node plus every node
    that is a descendant of node.

    Input: root = [1,null,0,0,1]
    Output: [1,null,0,null,1]
    Explanation:
    Only the red nodes satisfy the property "every subtree
    not containing a 1".
    The diagram on the right represents the answer.

    Input: root = [1,0,1,0,0,0,1]
    Output: [1,null,1,null,1]
    Constraints:

    The number of nodes in the tree is in the range [1, 200].
    Node.val is either 0 or 1.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Mon Sep  5 11:42:16 PM PDT 2022
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

void test() {
  int ret = 0;

  debug("Output = %d", ret);
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

bool containsOne(struct TreeNode* node) {
  if (node == NULL)
    return false;

  // Check if any node in the left subtree contains a 1.
  bool leftContainsOne = containsOne(node->left);

  // Check if any node in the right subtree contains a 1.
  bool rightContainsOne = containsOne(node->right);

  // If the left subtree does not contain a 1, prune the subtree.
  if (!leftContainsOne)
    node->left = NULL;

  // If the right subtree does not contain a 1, prune the subtree.
  if (!rightContainsOne)
    node->right = NULL;

  // Return true if the current node, its left or right subtree contains a 1.
  return node->val == 1 || leftContainsOne || rightContainsOne;
}

struct TreeNode* pruneTree(struct TreeNode* root){
  return containsOne(root) ? root : NULL;
}
int main (int argc, char **argv) {
  test();
  return 0;
}

/*
  Complexity Analysis

  Time Complexity: O(N), where N is the number of nodes
  in the tree. We process each node once.

  Space Complexity: O(N), the recursion call stack can be
  as large as the height H of the tree.
  In the worst case scenario, H=N, when the tree is skewed.
*/

/*
  prune - छाटणी, छाटून टाकणे
*/
