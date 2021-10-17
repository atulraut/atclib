/***
    https://leetcode.com/problems/path-sum-iii/
    Path Sum III

    Given the root of a binary tree and an integer
    targetSum, return the number of paths where the
    sum of the values along the path equals targetSum.

    The path does not need to start or end at the root
    or a leaf, but it must go downwards (i.e., traveling
    only from parent nodes to child nodes).

    Input: root = [10,5,-3,3,2,null,11,3,-2,null,1], targetSum = 8
    Output: 3
    Explanation: The paths that sum to 8 are shown.

    Input: root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
    Output: 3

    Constraints:
    The number of nodes in the tree is in the range [0, 1000].
    -109 <= Node.val <= 109
    -1000 <= targetSum <= 1000

    Date: 17 Oct 2021
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

struct TreeNode {
  int val;
  struct TreeNode *left;
  struct TreeNode *right;
};

void helper(struct TreeNode* root, int sum, int* table, int level, int* ans) {
    if (!root) return;
    int* newTable = malloc(sizeof(int)*level);
    int i;

    for(i = 0; i < level-1; i++) {
        newTable[i] = table[i] + root -> val;
    }

    newTable[i] = root -> val;
    for(i = 0; i < level; i++) {
        if(newTable[i] == sum) *ans += 1;
    }

    helper(root->left, sum, newTable, level+1, ans);
    helper(root->right, sum, newTable, level+1, ans);
    free(newTable);
}

int pathSum(struct TreeNode* root, int sum) {
    int *ans = malloc(sizeof(int));
    *ans = 0;
    helper(root, sum, NULL, 1, ans);
    return *ans;
}

int main (int argc, char **argv) {
  int ret = 0;
  int sum = 8;
   struct TreeNode rt[10];

  rt[0] = (struct TreeNode){.val=5, .left=NULL, .right=NULL};
  rt[1] = (struct TreeNode){.val=4, .left=NULL, .right=NULL};
  rt[2] = (struct TreeNode){.val=8, .left=NULL, .right=NULL};
  rt[3] = (struct TreeNode){.val=11, .left=NULL, .right=NULL};
  rt[4] = (struct TreeNode){.val=13, .left=NULL, .right=NULL};
  rt[5] = (struct TreeNode){.val=4, .left=NULL, .right=NULL};
  rt[6] = (struct TreeNode){.val=7, .left=NULL, .right=NULL};
  rt[7] = (struct TreeNode){.val=2, .left=NULL, .right=NULL};
  rt[8] = (struct TreeNode){.val=5, .left=NULL, .right=NULL};
  rt[9] = (struct TreeNode){.val=1, .left=NULL, .right=NULL};

  rt[0].left = &rt[1];
  rt[0].right= &rt[2];

  rt[1].left = &rt[3];

  rt[2].left = &rt[4];
  rt[2].right= &rt[5];

  rt[3].left = &rt[6];
  rt[3].right= &rt[7];

  rt[5].left = &rt[8];
  rt[5].right= &rt[9];

  ret = pathSum(rt, sum);
  debug("Output = %d", ret);
  return 0;
}

/**

 **/
