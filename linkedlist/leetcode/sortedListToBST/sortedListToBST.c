/***
    Medium: Convert Sorted List to Binary Search Tree
    https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/

    Given the head of a singly linked list where elements are sorted in
    ascending order, convert it to a height balanced BST.

    For this problem, a height-balanced binary tree is defined as a binar
    tree in which the depth of the two subtrees of every node never
    differ by more than 1.

    Input: head = [-10,-3,0,5,9]
    Output: [0,-3,9,-10,null,5]
    Explanation: One possible answer is [0,-3,9,-10,null,5], which represents
    the shown height balanced BST.

    Date:
    San Diego, CA.
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

struct TreeNode* treenode_create(int val) {
    struct TreeNode* p = malloc(sizeof(struct TreeNode));
    p->val = val;
    p->left = NULL;
    p->right = NULL;
    return p;
}

struct TreeNode* sortedListToBST(struct ListNode* head) {
    if (head == NULL) {
        return NULL;
    }
    if (head->next == NULL) {
        return treenode_create(head->val);
    }

    struct ListNode* prev = NULL;
    struct ListNode* slow = head;
    struct ListNode* fast = head;

    while (fast && fast->next) {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    if (prev) {
        prev->next = NULL;
    }

    struct TreeNode* l = sortedListToBST(head);
    struct TreeNode* r = sortedListToBST(slow->next);
    struct TreeNode* root = treenode_create(slow->val);
    root->left = l;
    root->right = r;

    return root;
}

int main () {
  int ret = 0;

  debug("Output = ");
  return 0;
}

/**

 **/
