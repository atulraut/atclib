/***
    Given the root of a Binary Search Tree and a target number k,
    return true if there exist two elements in the BST such that
    their sum is equal to the given target.

    Input: root = [5,3,6,2,4,null,7], k = 9
    Output: true

    Input: root = [5,3,6,2,4,null,7], k = 28
    Output: false

    Input: root = [2,1,3], k = 4
    Output: true

    Input: root = [2,1,3], k = 1
    Output: false

    Input: root = [2,1,3], k = 3
    Output: true

    Constraints:
    The number of nodes in the tree is in the range [1, 104].
    -104 <= Node.val <= 104
    root is guaranteed to be a valid binary search tree.
    -105 <= k <= 105

    https://leetcode.com/problems/two-sum-iv-input-is-a-bst/
    Date: 23 August 2021
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

struct tree_node {
  int val;
  struct tree_node *left;
  struct tree_node *right;
};

int k=0;
void tree(struct tree_node *root,int *arr){
  if(root == NULL){
    return ;
  }
  if(root->left == NULL && root->right == NULL){
    arr[k++] = root->val;
    return;
  }
  tree(root->left, arr);
  arr[k++] = root->val;
  tree(root->right, arr);
  return ;
}

int count_(struct tree_node *root) {
  if(root == NULL) {
    return 0;
  }

  if(root->left == NULL && root->right == NULL) {
    return 1;
  }
  return 1 + count_(root->left) + count_(root->right);
}

bool findTarget(struct tree_node* root, int t) {
  int count = count_(root);
  k=0;
  int *arr=malloc(count*sizeof(int));

  debug ("count = %d", count);
  tree(root, arr);
  for (int i=0; i<count; ++i)
    debug ("arr[%d] = %d", i, arr[i]);

  for(int i=0; i<count-1; i++) {
    for(int j=i+1; j<count; j++) {
      if(arr[i] + arr[j] == t){
	return true;
      }
    }
  }
  return false;
}

int main (int argc, char **argv) {
  int ret = 0;
  int t=9;
  struct tree_node rt[7];

  /* Input: root = [5,3,6,2,4,null,7], k = 9 */
  /* Initialize the Tree as per Example 1 above */
  rt[0] = (struct tree_node) {.val=5, .left=NULL, .right=NULL};
  rt[1] = (struct tree_node) {.val=3, .left=NULL, .right=NULL};
  rt[2] = (struct tree_node) {.val=6, .left=NULL, .right=NULL};
  rt[3] = (struct tree_node) {.val=2, .left=NULL, .right=NULL};
  rt[4] = (struct tree_node) {.val=4, .left=NULL, .right=NULL};
  //  rt[5] = NULL;
  rt[6] = (struct tree_node) {.val=7, .left=NULL, .right=NULL};

  rt[0].left  = &rt[1];  // 1 <-- 0 [0's left]
  rt[0].right = &rt[2];  // 0 --> 3 [0's right]

  rt[1].left  = &rt[3];
  rt[1].right = &rt[4];

  rt[2].right = &rt[6];

  ret = findTarget(rt, t);

  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [findTarget] L=82 :count = 6
   [findTarget] L=85 :arr[0] = 2
   [findTarget] L=85 :arr[1] = 3
   [findTarget] L=85 :arr[2] = 4
   [findTarget] L=85 :arr[3] = 5
   [findTarget] L=85 :arr[4] = 6
   [findTarget] L=85 :arr[5] = 7
   [main] L=121 :Output = 1
**/
