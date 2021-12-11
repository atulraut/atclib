/***
    https://leetcode.com/problems/linked-list-in-binary-tree/
    Linked List in Binary Tree

    Given a binary tree root and a linked list with head as the first node.

    Return True if all the elements in the linked list starting from the
    head correspond to some downward path connected in the binary tree otherwise return False.

    In this context downward path means a path that starts at some node and goes downwards.

    Input: head = [4,2,8], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
    Output: true
    Explanation: Nodes in blue form a subpath in the binary Tree.

    Input: head = [1,4,2,6], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
    Output: true

    Input: head = [1,4,2,6,8], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
    Output: false
    Explanation: There is no path in the binary tree that contains all the elements of
    the linked list from head.

    Constraints:
    The number of nodes in the tree will be in the range [1, 2500].
    The number of nodes in the list will be in the range [1, 100].
    1 <= Node.val <= 100 for each node in the linked list and binary tree.
    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 10 Dec 2021 (121021)
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
 * Definition for singly-linked list.
 */
struct ListNode {
  int val;
  struct ListNode *next;
};

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
  int val;
  struct TreeNode *left;
  struct TreeNode *right;
};

bool checkValue (struct ListNode* head, struct TreeNode* root) {
  if (!head) {
    return true;
  } else if (!root) {
    return false;
  }
  if (head->val == root->val) {
    return checkValue(head->next, root->left) || checkValue(head->next, root->right);
  } else {
    return false;
  }
}


bool isSubPath(struct ListNode* head, struct TreeNode* root) {
  if (!root) {
    return false;
  }
  if (checkValue(head, root)) {
    return true;
  }
  return isSubPath(head,root->left) || isSubPath(head,root->right);
}

bool findSubPath(struct ListNode* head,struct TreeNode* root) {
  if (!head)
    return true;
  if (!root)
    return false;
  return head->val == root->val && (findSubPath(head->next, root->left) || findSubPath(head->next, root->right));
}

bool isSubPath2(struct ListNode* head, struct TreeNode* root) {
  if (!root)
    return false;
  return findSubPath(head, root) || isSubPath(head, root->left) || isSubPath(head, root->right);
}

void push(struct ListNode** head_ref, int val) {
  struct ListNode* nn = (struct ListNode*)malloc(sizeof(struct ListNode));
  nn->val = val;
  nn->next = (*head_ref);
  (*head_ref) = nn;
}

void printList(struct ListNode* head) {
  struct ListNode* trav = head;
  while (trav != NULL) {
    debug("%d  ", trav->val);
    trav = trav->next;
  }
}

int main (int argc, char **argv) {
  int ret = 0;
  struct ListNode* head = NULL;

  push(&head, 8);
  push(&head, 2);
  push(&head, 4);

  debug("Given linked list\n");
  printList(head);

  struct TreeNode rt[6];

  rt[0] = (struct TreeNode){.val=5, .left=NULL, .right=NULL};
  rt[1] = (struct TreeNode){.val=7, .left=NULL, .right=NULL};
  rt[2] = (struct TreeNode){.val=4, .left=NULL, .right=NULL};
  rt[3] = (struct TreeNode){.val=11,.left=NULL, .right=NULL};
  rt[4] = (struct TreeNode){.val=2, .left=NULL, .right=NULL};
  rt[5] = (struct TreeNode){.val=8, .left=NULL, .right=NULL};

  rt[0].left = &rt[1];
  rt[0].right= &rt[2];

  rt[1].left = &rt[3];

  rt[2].left = &rt[4];
  rt[4].right= &rt[5];

  ret = isSubPath(head, rt);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=138 :Given linked list

   [printList] L=125 :4
   [printList] L=125 :2
   [printList] L=125 :8
   [main] L=159 :Output = 1
**/
