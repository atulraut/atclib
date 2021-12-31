/***
    https://leetcode.com/problems/populating-next-right-pointers-in-each-node
    Populating Next Right Pointers in Each Node

    You are given a perfect binary tree where all leaves are on the same level, and
    every parent has two children. The binary tree has the following definition:

    struct Node {
      int val;
      Node *left;
      Node *right;
      Node *next;
    }
    Populate each next pointer to point to its next right node. If there
    is no next right node, the next pointer should be set to NULL.

    Initially, all next pointers are set to NULL.

    Input: root = [1,2,3,4,5,6,7]
    Output: [1,#,2,3,#,4,5,6,7,#]
    Explanation: Given the above perfect binary tree (Figure A), your function
    should populate each next pointer to point to its next right node, just like
    in Figure B. The serialized output is in level order as connected by the next
    pointers, with '#' signifying the end of each level.

    Input: root = []
    Output: []

    Constraints:
    The number of nodes in the tree is in the range [0, 212 - 1].
    -1000 <= Node.val <= 1000

    Follow-up:
    You may only use constant extra space.
    The recursive approach is fine. You may assume implicit stack space
    does not count as extra space for this problem.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address connect.c -lm

    Date: 12/29/2021
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
 * Definition for a Node.
 */
struct Node {
  int val;
  struct Node *left;
  struct Node *right;
  struct Node *next;
};

void connect_left_to_right(struct Node* left, struct Node* right) {
    if (left && right) {
        left->next = right;
        connect_left_to_right(left->right, right->left);
    }
}

struct Node* connect(struct Node* root) {
    if (root) {
        connect_left_to_right(root->left, root->right);
        connect(root->left);
        connect(root->right);
    }
    return root;
}

int main (int argc, char **argv) {
  int ret = 0;
  struct Node rt[7];

  rt[0] = (struct Node){.val=1, .left=NULL, .right=NULL};
  rt[1] = (struct Node){.val=2, .left=NULL, .right=NULL};
  rt[2] = (struct Node){.val=3, .left=NULL, .right=NULL};
  rt[3] = (struct Node){.val=4, .left=NULL, .right=NULL};
  rt[4] = (struct Node){.val=5, .left=NULL, .right=NULL};
  rt[5] = (struct Node){.val=6, .left=NULL, .right=NULL};
  rt[6] = (struct Node){.val=7, .left=NULL, .right=NULL};

  rt[0].left = &rt[1];
  rt[0].right= &rt[2];

  rt[1].left = &rt[3];
  rt[1].right= &rt[4];

  rt[2].left = &rt[5];
  rt[2].right= &rt[6];

  struct Node* root = connect(rt);

  debug("Output = %d", root->left->next->val);
  return 0;
}

/**
   => ./a.out
   [main] L=119 :Output = 3
**/
