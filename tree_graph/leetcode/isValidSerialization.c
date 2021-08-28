/***
    Verify Preorder Serialization of a Binary Tree

    One way to serialize a binary tree is to use preorder traversal.
    When we encounter a non-null node, we record the node's value.
    If it is a null node, we record using a sentinel value such as '#'.

    For example, the above binary tree can be serialized to the
    string "9,3,4,#,#,1,#,#,2,#,6,#,#", where '#' represents a null node.

    Given a string of comma-separated values preorder, return true
    if it is a correct preorder traversal serialization of a binary tree.

    It is guaranteed that each comma-separated value in the string
    must be either an integer or a character '#' representing null pointer.

    You may assume that the input format is always valid.

    For example, it could never contain two consecutive commas, such as "1,,3".
    Note: You are not allowed to reconstruct the tree.

    Input: preorder = "9,3,4,#,#,1,#,#,2,#,6,#,#"
    Output: true

    Input: preorder = "1,#"
    Output: false

    Input: preorder = "9,#,#,1"
    Output: false

    Constraints:
    1 <= preorder.length <= 104
    preorder consist of integers in the range [0, 100] and '#' separated by commas ','.
    https://leetcode.com/problems/verify-preorder-serialization-of-a-binary-tree/

    Date: 28 August 2021.
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

bool isValidSerialization(char * preorder){
  char *p;
  int diff = 1;

  p = strtok(preorder, ",");
  while (p) {
    if (--diff < 0)
      return false;
    if (strcmp(p, "#"))
      diff += 2;
    p = strtok(NULL, ",");
  }

  return diff == 0;
}

bool isValidSerialization2(char* preorder) {
  int n = strlen(preorder);
  int stk[n], top = 0;
  int i = 0;
  stk[top++] = 1;
  while (i < n) {
    if (!top) {
      return false;
    }
    if (preorder[i] == ',') {
      i++;
    } else if (preorder[i] == '#') {
      stk[top - 1] -= 1;
      if (stk[top - 1] == 0) {
	top--;
      }
      i++;
    } else {
      /* Read a number */
      while (i < n && preorder[i] != ',') {
	i++;
      }
      stk[top - 1] -= 1;
      if (stk[top - 1] == 0) {
	top--;
      }
      stk[top++] = 2;
    }
  }
  return !top;
}

int main (int argc, char **argv) {
  int ret = 0;

  char* preorder = "9,3,4,#,#,1,#,#,2,#,6,#,#";
  ret = isValidSerialization2(preorder);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=106 :Output = 1
**/
