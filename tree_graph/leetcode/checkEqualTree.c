/***
    Equal Tree Partition

    Given the root of a binary tree, return true if you can partition the tree
    into two trees with equal sums of values after removing exactly one edge
    on the original tree.

    Input: root = [5,10,10,null,null,2,3]
    Output: true

    Input: root = [1,2,10,null,null,2,20]
    Output: false
    Explanation: You cannot split the tree into two trees with equal sums after
    removing exactly one edge on the tree.

    Constraints:
    The number of nodes in the tree is in the range [1, 104].
    -105 <= Node.val <= 105

    https://leetcode.com/problems/equal-tree-partition/

    Status : Pending

    Date: 29 August 2021.
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

bool checkEqualTree(struct TreeNode* root) {

}

int main (int argc, char **argv) {
  int ret = 0;

  debug("Output = %d", ret);
  return 0;
}

/**

 **/
