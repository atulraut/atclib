/***
    https://leetcode.com/problems/sum-root-to-leaf-numbers/
    Sum Root to Leaf Numbers

    You are given the root of a binary tree containing
    digits from 0 to 9 only.

    Each root-to-leaf path in the tree represents a number.

    For example, the root-to-leaf path 1 -> 2 -> 3 represents
    the number 123.
    Return the total sum of all root-to-leaf numbers.
    Test cases are generated so that the answer will fit in a 32-bit integer.
    A leaf node is a node with no children.

    Input: root = [1,2,3]
    Output: 25
    Explanation:
    The root-to-leaf path 1->2 represents the number 12.
    The root-to-leaf path 1->3 represents the number 13.
    Therefore, sum = 12 + 13 = 25.

    Input: root = [4,9,0,5,1]
    Output: 1026
    Explanation:
    The root-to-leaf path 4->9->5 represents the number 495.
    The root-to-leaf path 4->9->1 represents the number 491.
    The root-to-leaf path 4->0 represents the number 40.
    Therefore, sum = 495 + 491 + 40 = 1026.

    Constraints:
    The number of nodes in the tree is in the range [1, 1000].
    0 <= Node.val <= 9
    The depth of the tree will not exceed 10.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address sumNumbers.c -lm

    Date: 5 Nov 2021
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

struct TreeNode {
  int val;
  struct TreeNode *left;
  struct TreeNode *right;
};

void travel(struct TreeNode* root,int num,int* res) {
    printf("%d\n",root->val);
    num +=root->val;

    if (root->left == NULL && root->right == NULL) {
        *res+=num;
        printf("%d\n",*res);
    }

    if(root->left != NULL) {
      travel(root->left,num*10,res);
    }

    if(root->right != NULL) {
      travel(root->right,num*10,res);
    }
}

int sumNumbers(struct TreeNode* root) {
  int res = 0;
  travel(root,0,&res);
  return res;
}

int RootToLeafSum(struct TreeNode* node, int sum) {
  if (node == NULL)
    return 0;
  else {
    int new_sum = sum + node -> val;
    if (node->left == NULL && node->right == NULL)
      return new_sum;
    else
      return RootToLeafSum(node->left, new_sum * 10) + RootToLeafSum(node->right, new_sum * 10);
  }
}

int sumNumbers2(struct TreeNode* root){
    int sum = 0;
    return RootToLeafSum(root, sum);
}

int main (int argc, char **argv) {
  int ret = 0;
  struct TreeNode rt[3];

  rt[0] = (struct TreeNode){.val=1,  .left=NULL, .right=NULL};
  rt[1] = (struct TreeNode){.val=2,  .left=NULL, .right=NULL};
  rt[2] = (struct TreeNode){.val=3, .left=NULL, .right=NULL};

  rt[0].left = &rt[1];
  rt[0].right= &rt[2];

  ret = sumNumbers(rt);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   1
   2
   12
   3
   25
   [main] L=127 :Output = 25
**/
