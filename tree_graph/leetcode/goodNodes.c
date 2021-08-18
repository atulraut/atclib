/***
    Medium: Count Good Nodes in Binary Tree
    iven a binary tree root, a node X in the tree is named good if in the path
    from root to X there are no nodes with a value greater than X.

    Return the number of good nodes in the binary tree.

    Input: root = [3,1,4,3,null,1,5]
    Output: 4
    Explanation: Nodes in blue are good.
    Root Node (3) is always a good node.
    Node 4 -> (3,4) is the maximum value in the path starting from the root.
    Node 5 -> (3,4,5) is the maximum value in the path
    Node 3 -> (3,1,3) is the maximum value in the path.

    https://leetcode.com/problems/count-good-nodes-in-binary-tree/

    Input: root = [3,3,null,4,2]
    Output: 3
    Explanation: Node 2 -> (3, 3, 2) is not good, because "3" is higher than it.

    Input: root = [1]
    Output: 1
    Explanation: Root is considered as good.

    Constraints:

    The number of nodes in the binary tree is in the range [1, 10^5].
    Each node's value is between [-10^4, 10^4].

    Date: 17 August 2021
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

int helper(struct TreeNode* currentNode, int currentMax){
  if(currentNode==NULL) return 0;
  int result=0;
  int newMax=currentMax;

  if(currentNode->val >= newMax) {
    ++result;
    newMax=currentNode->val;
  }

  if(currentNode->left == NULL && currentNode->right == NULL)
    return result;

  result+=helper(currentNode->left,newMax);
  result+=helper(currentNode->right,newMax);
  return result;
}

int goodNodes(struct TreeNode* root) {
  return helper(root,root->val);
}

int main (int argc, char **argv) {
  int ret = 0;
  struct TreeNode rt[7];

  rt[0] = (struct TreeNode){.val=3, .left=NULL, .right=NULL};
  rt[1] = (struct TreeNode){.val=1, .left=NULL, .right=NULL};
  rt[2] = (struct TreeNode){.val=4, .left=NULL, .right=NULL};
  rt[3] = (struct TreeNode){.val=3, .left=NULL, .right=NULL};
  //  rt[4] = NULL;//(struct TreeNode){.val=13, .left=NULL, .right=NULL};
  rt[5] = (struct TreeNode){.val=1, .left=NULL, .right=NULL};
  rt[6] = (struct TreeNode){.val=5, .left=NULL, .right=NULL};

  rt[0].left = &rt[1];
  rt[0].right= &rt[2];

  rt[1].left = &rt[3];
  rt[1].right = NULL;

  rt[2].left = &rt[5];
  rt[2].right= &rt[6];

  ret = goodNodes(rt);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=100 :Output = 4
**/
