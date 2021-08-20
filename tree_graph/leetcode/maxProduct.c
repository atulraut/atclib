/***
    Medium: Maximum Product of Splitted Binary Tree

    Given the root of a binary tree, split the binary tree
    into two subtrees by removing one edge such that the
    product of the sums of the subtrees is maximized.

    Return the maximum product of the sums of the two subtrees.
    Since the answer may be too large, return it modulo 109 + 7.

    Note that you need to maximize the answer before taking the
    mod and not after taking it.

    Input: root = [1,2,3,4,5,6]
    Output: 110
    Explanation: Remove the red edge and get 2 binary trees with sum 11 and 10.
    Their product is 110 (11*10)

    https://leetcode.com/problems/maximum-product-of-splitted-binary-tree/

    Date: 19 August 2021
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

long long int traversal(struct TreeNode * root, long long * max_val, long long total_sum) {
  if(root == NULL)
    return 0;

  long long int left  = traversal(root->left, max_val, total_sum);
  long long int right = traversal(root->right, max_val, total_sum);


  long long int product1 = ((left + root->val + (total_sum - left - right - root->val))) * right;
  long long int product2 = (right + root->val + (total_sum - right - left - root->val) ) * left;

  long long max_product = product1 >= product2 ? product1 : product2;

  if(max_product >= *max_val) {
    *max_val = max_product;
  }

  return (left + right + root->val);
}

long long find_sum(struct TreeNode * root) {
  if(root == NULL)
    return 0;

  long long left = find_sum(root->left);
  long long right = find_sum(root->right);

  return (left + right + root->val);
}

int maxProduct(struct TreeNode* root) {
  long long max_val = INT_MIN;
  long long total_sum = find_sum(root);
  traversal(root, &max_val, total_sum);
  return max_val % ((int)pow(10, 9) + 7);
}

int main (int argc, char **argv) {
  int ret = 0;

  debug("Output = %d", ret);
  return 0;
}

/**

 **/
