/***
    https://leetcode.com/problems/insert-into-a-binary-search-tree
    701. Insert into a Binary Search Tree

    You are given the root node of a binary search tree (BST)
    and a value to insert into the tree. Return the root node of
    the BST after the insertion. It is guaranteed that the new
    value does not exist in the original BST.

    Notice that there may exist multiple valid ways for the insertion,
    as long as the tree remains a BST after insertion. You can return any of them.

    Input: root = [4,2,7,1,3], val = 5
    Output: [4,2,7,1,3,5]
    Explanation: Another accepted tree is:

    Example 2:

    Input: root = [40,20,60,10,30,50,70], val = 25
    Output: [40,20,60,10,30,50,70,null,null,25]
    Example 3:

    Input: root = [4,2,7,1,3,null,null,null,null,null,null], val = 5
    Output: [4,2,7,1,3,5]


    Constraints:

    The number of nodes in the tree will be in the range [0, 104].
    -108 <= Node.val <= 108
    All the values Node.val are unique.
    -108 <= val <= 108
    It's guaranteed that val does not exist in the original BST.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 12 Jan, 2022
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

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
  int val;
  struct TreeNode *left;
  struct TreeNode *right;
};

struct TreeNode* insertIntoBST(struct TreeNode* root, int val) {
  if(root == NULL) {
    struct TreeNode* temp=root;
    temp = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    temp->val = val;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
  } else if(val <= root->val) {
    root->left = insertIntoBST(root->left,val);
  } else  {
    root->right = insertIntoBST(root->right,val);
  }
  return root;
}

struct TreeNode* insertIntoBST_(struct TreeNode* root, int val) {
  struct TreeNode *p = root, *parent=NULL;
  struct TreeNode* node = malloc(sizeof(struct TreeNode));
  node->left = NULL;
  node->right = NULL;
  node->val = val;
  if(!root){
    return node;
  }
  while (p) {
    parent = p;
    p = (val>p->val)?p->right:p->left;
  }
  if(val>parent->val){
    parent->right = node;
  }else{
    parent->left = node;
  }
  return root;
}

void m_preorder(struct TreeNode *_root) {
	struct TreeNode *nn = (struct TreeNode *)_root;
	printf ("\n m_preorder-> ");
	printf ("->[%d]", nn->val);
	if(nn == NULL)
		return;
	if(NULL != nn->left)
		m_preorder(nn->left);
	if(NULL != nn->right)
		m_preorder(nn->right);
}

void test() {
   struct TreeNode rt[5];

  rt[0] = (struct TreeNode){.val=4, .left=NULL, .right=NULL};
  rt[1] = (struct TreeNode){.val=2, .left=NULL, .right=NULL};
  rt[2] = (struct TreeNode){.val=7, .left=NULL, .right=NULL};
  rt[3] = (struct TreeNode){.val=1, .left=NULL, .right=NULL};
  rt[4] = (struct TreeNode){.val=3, .left=NULL, .right=NULL};

  rt[0].left = &rt[1];
  rt[0].right= &rt[2];

  rt[1].left = &rt[3];
  rt[1].right= &rt[4];

  debug("Iutput");
  m_preorder(rt);
  struct TreeNode *op = insertIntoBST(rt, 5);
  debug("\nOutput");
  m_preorder(op);
  printf("\n");
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [test] L=140 :Iutput

   m_preorder-> ->[4]
   m_preorder-> ->[2]
   m_preorder-> ->[1]
   m_preorder-> ->[3]
   m_preorder-> ->[7][test] L=143 :
   Output

   m_preorder-> ->[4]
   m_preorder-> ->[2]
   m_preorder-> ->[1]
   m_preorder-> ->[3]
   m_preorder-> ->[7]
   m_preorder-> ->[5]
**/
