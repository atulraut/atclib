/***
    https://leetcode.com/problems/count-complete-tree-nodes/
    Count Complete Tree Nodes
    Given the root of a complete binary tree, return the number
    of the nodes in the tree.

    According to Wikipedia, every level, except possibly the last,
    is completely filled in a complete binary tree, and all nodes
    in the last level are as far left as possible. It can have
    between 1 and 2h nodes inclusive at the last level h.

    Design an algorithm that runs in less than O(n) time complexity.

    Input: root = [1,2,3,4,5,6]
    Output: 6

    Input: root = []
    Output: 0

    Input: root = [1]
    Output: 1

    Constraints:
    The number of nodes in the tree is in the range [0, 5 * 104].
    0 <= Node.val <= 5 * 104
    The tree is guaranteed to be complete.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 24 Oct 2021
    Fair Oaks, CA.
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
  ({ typeof (a) _a = (a);			\
    typeof (b) _b = (b);			\
    _a > _b ? _a : _b; })
#define min(a,b)				\
  ({ typeof (a) _a = (a);			\
    typeof (b) _b = (b);			\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/
struct tree_node {
  int val;
  struct tree_node *left;
  struct tree_node *right;
};

int height(struct tree_node *root) {
  int h;

  h = -1;
  while (root) {
    ++h;
    root = root->left;
  }
  return h;
}

int countNodes(struct tree_node* root) {
  int h1, h2;


  if (!root) return 0;

  h1 = height(root->left);
  h2 = height(root->right);

  if (h1 == h2) {
    return 1 + ((1 << (h1 + 1)) - 1) + countNodes(root->right);
  } else {
    return 1 + ((1 << h1) - 1) + countNodes(root->left);
  }
}

int main (int argc, char **argv) {
  int ret = 0;
  struct tree_node rt[6];

  rt[0] = (struct tree_node) {.val=1, .left=NULL, .right=NULL};
  rt[1] = (struct tree_node) {.val=2, .left=NULL, .right=NULL};
  rt[2] = (struct tree_node) {.val=3, .left=NULL, .right=NULL};
  rt[3] = (struct tree_node) {.val=4, .left=NULL, .right=NULL};
  rt[4] = (struct tree_node) {.val=5, .left=NULL, .right=NULL};
  rt[5] = (struct tree_node) {.val=6, .left=NULL, .right=NULL};

  rt[0].left  = &rt[1];  // 1 <-- 0 [0's left]
  rt[0].right = &rt[2];  // 0 --> 3 [0's right]

  rt[1].left  = &rt[3];  // 1 <-- 2 [2's left]
  rt[1].right = &rt[4];  // 0 --> 3 [0's right]

  rt[2].left  = &rt[5];  // 1 <-- 2 [2's left]

  ret = countNodes(rt);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=112 :Output = 6
**/
