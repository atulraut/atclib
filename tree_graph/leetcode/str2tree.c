/***
    536. Construct Binary Tree from String
    You need to construct a binary tree from a string consisting of
    parenthesis and integers.

    The whole input represents a binary tree. It contains an integer
    followed by zero, one or two pairs of parenthesis. The integer represents
    the root's value and a pair of parenthesis contains a child binary tree
    with the same structure.

    You always start to construct the left child node of the parent first
    if it exists.

    Input: s = "4(2(3)(1))(6(5))"
    Output: [4,2,6,3,1,5]

    Input: s = "4(2(3)(1))(6(5)(7))"
    Output: [4,2,6,3,1,5,7]

    Input: s = "-4(2(3)(1))(6(5)(7))"
    Output: [-4,2,6,3,1,5,7]

    Date : 25 March 2021
    San Diego, CA
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

/***
    In case File Debug Option needs to Enabled.
*/
#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)


struct TreeNode {
  int val;
  struct TreeNode *left;
  struct TreeNode *right;
};

struct TreeNode *create(int val) {
  struct TreeNode *new = (struct TreeNode *)malloc(sizeof(struct TreeNode));
  new->val = val;
  new->left = NULL;
  new->right = NULL;
  return new;
}

struct TreeNode* str2tree(char * s){
  int len = strlen(s);
  struct TreeNode *stack[100] = {0};
  int top = -1;

  for (int i = 0; i < len; i++) {

    if (s[i] == ')') {
      //stack[top--] = NULL;
      top--;
    } else if (s[i] >= '0' && s[i] <= '9' || s[i] == '-') {
      int sign = 1;
      if (s[i] == '-') {
	sign = -1;
	i++;
      }

      int num = 0;
      while (s[i] >= '0' && s[i] <= '9') {
	num = 10 * num + s[i++] - '0';
      }
      i--;
      num = num * sign;
      struct TreeNode* new = create(num);
      if (top != -1) {
	struct TreeNode* parent = stack[top];
	if (parent->left)
	  parent->right = new;
	else
	  parent->left = new;
      }
      stack[++top] = new;
    }
  }
  return (top == -1) ? NULL : stack[0];
}

int main () {
  char inputStr[] = "4(2(3)(1))(6(5))";

  struct TreeNode *output = str2tree(inputStr);

  for (int i=0; i<strlen(inputStr); i++) {
    printf ("%d ", output[i].val);
  }
  printf ("\n");
  return 0;
}
