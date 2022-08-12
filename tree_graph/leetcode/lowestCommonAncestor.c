/***
    https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
    Lowest Common Ancestor of a Binary Search Tree

    Given a binary search tree (BST), find the lowest common
    ancestor (LCA) node of two given nodes in the BST.

    According to the definition of LCA on Wikipedia: “The lowest common
    ancestor is defined between two nodes p and q as the lowest node in T
    that has both p and q as descendants (where we allow a node to be a
    descendant of itself).”

    Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
    Output: 6
    Explanation: The LCA of nodes 2 and 8 is 6.

    Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
    Output: 2
    Explanation: The LCA of nodes 2 and 4 is 2, since a node can be
    a descendant of itself according to the LCA definition.

    Input: root = [2,1], p = 2, q = 1
    Output: 2

    Constraints:

    The number of nodes in the tree is in the range [2, 105].
    -109 <= Node.val <= 109
    All Node.val are unique.
    p != q
    p and q will exist in the BST.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Thu Aug 11 10:03:00 PM PDT 2022
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
#define max(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a > _b ? _a : _b; })
#define min(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

struct tree_node {
  int val;
  struct tree_node *left;
  struct tree_node *right;
};

struct tree_node* lowestCommonAncestor(struct tree_node* root, struct tree_node* p, struct tree_node* q) {
  debug ("root->val = %d p->val=%d q->val=%d", root->val, p->val, q->val);
  if (root->val < p->val && root->val < q->val) {
    // go right
    return lowestCommonAncestor(root->right, p, q);
  } else if (p->val < root->val && q->val < root->val) {
    // go left
    return lowestCommonAncestor(root->left, p, q);
  } else {
    return root;
  }
}

void test() {
  struct tree_node rt[7];
  struct tree_node* p;
  struct tree_node* q;

  /* Initialize the Tree as per Example 1 above */
  rt[0] = (struct tree_node) {.val=6, .left=NULL, .right=NULL};
  rt[1] = (struct tree_node) {.val=2, .left=NULL, .right=NULL};
  rt[2] = (struct tree_node) {.val=8, .left=NULL, .right=NULL};

  rt[0].left  = &rt[1];  // 5 <-- 1 [0's left]
  rt[0].right = &rt[2];  // 5 --> 4 [0's right]

  p = &rt[1];
  q = &rt[2];
  struct tree_node* ret = lowestCommonAncestor(rt, p, q);

  debug("Output = %d", ret->val);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   [lowestCommonAncestor] L=72 :root->val = 6 p->val=2 q->val=8
   [test] L=70 :Output = 6
**/
