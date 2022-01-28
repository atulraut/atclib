/***
    https://leetcode.com/problems/all-elements-in-two-binary-search-trees/
    Given two binary search trees root1 and root2, return a
    list containing all the integers from both trees sorted in ascending order.

    Input: root1 = [2,1,4], root2 = [1,0,3]
    Output: [0,1,1,2,3,4]

    Input: root1 = [1,null,8], root2 = [8,1]
    Output: [1,1,8,8]

    Constraints:
    The number of nodes in each tree is in the range [0, 5000].
    -105 <= Node.val <= 105

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 25 Jan 2022
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

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
  int val;
  struct TreeNode *left;
  struct TreeNode *right;
};

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#define MAXSIZE 5000
typedef struct sta {
  struct TreeNode *stack[MAXSIZE];
  int top;
} stack_t;

int isempty(stack_t *s) {
  if(s->top == -1)
    return 1;
  else
    return 0;
}

int isfull(stack_t *s) {
  if(s->top == MAXSIZE)
    return 1;
  else
    return 0;
}

struct TreeNode * peek(stack_t *s) {
  return s->stack[s->top];
}

struct TreeNode * pop(stack_t *s) {
  struct TreeNode * data;
  if(!isempty(s)) {
    data = s->stack[s->top];
    s->top = s->top - 1;
    return data;
  } else {
    printf("Could not retrieve data, Stack is empty.\n");
  }
  return NULL;
}

void push(struct TreeNode *data, stack_t *s) {

  if(!isfull(s)) {
    s->top = s->top + 1;
    s->stack[s->top] = data;
  } else {
    printf("Could not insert data, Stack is full.\n");
  }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getAllElements(struct TreeNode* root1, struct TreeNode* root2, int* returnSize) {
  static int init = 0;
  static stack_t *s1,*s2;
  static int* result;
  int result_size = 0;

  if(init == 0) {
    s1 = (stack_t *)malloc(sizeof(stack_t));
    s2 = (stack_t *)malloc(sizeof(stack_t));
    s1->top = -1;
    s2->top = -1;
    result = (int *)malloc(sizeof(int)*10000);
  }
  init++;

  while(root1 != NULL || root2 != NULL || !isempty(s1) || !isempty(s2)) {
    /* push all the root and left nodes of both the trees */
    while(root1 != NULL) {
      push(root1, s1);
      root1 = root1->left;
    }

    while(root2 != NULL) {
      push(root2, s2);
      root2 = root2->left;
    }

    if(isempty(s1) || (!isempty(s2) && peek(s1)->val > peek(s2)->val)) {
      root2 = pop(s2);
      result[result_size++] = root2->val;
      root2 = root2->right;
    } else {
      root1 = pop(s1);
      result[result_size++] = root1->val;
      root1 = root1->right;
    }
  }

  init--;

  if(init == 0) {
    free(s1);
    free(s2);
  }
  *returnSize = result_size;
  return result;
}

#define MAX    5000

void traverse(struct TreeNode* root, int *arr, int *idx) {
  if(!root)
    return;
  traverse(root->left, arr, idx);
  arr[(*idx)++] = root->val;
  traverse(root->right, arr, idx);
}

int* getAllElements__(struct TreeNode* root1, struct TreeNode* root2, int* returnSize) {
  int arr1[MAX];
  int arr2[MAX];
  int idx1 = 0, idx2 = 0, idx = 0, i = 0, j = 0;
  memset(arr1, 0, sizeof(arr1));
  memset(arr2, 0, sizeof(arr2));

  traverse(root1, arr1, &idx1);
  traverse(root2, arr2, &idx2);
  *returnSize = idx1 + idx2;

  int *ret = malloc(sizeof(int) * (*returnSize));
  while(i < idx1 && j < idx2)
    ret[idx++] = arr1[i] < arr2[j] ? arr1[i++] : arr2[j++];

  while(i < idx1)
    ret[idx++] = arr1[i++];

  while(j < idx2)
    ret[idx++] = arr2[j++];

  return ret;
}

void test() {
  int *ret;
  struct TreeNode rt1[3];
  int returnSize;
  rt1[0] = (struct TreeNode) {.val=2, .left=NULL, .right=NULL};
  rt1[1] = (struct TreeNode) {.val=1, .left=NULL, .right=NULL};
  rt1[2] = (struct TreeNode) {.val=4, .left=NULL, .right=NULL};
  rt1[0].left  = &rt1[1];  // 1 <-- 0 [0's left]
  rt1[0].right = &rt1[2];  // 0 --> 3 [0's right]

  struct TreeNode rt2[3];
  rt2[0] = (struct TreeNode) {.val=1, .left=NULL, .right=NULL};
  rt2[1] = (struct TreeNode) {.val=0, .left=NULL, .right=NULL};
  rt2[2] = (struct TreeNode) {.val=3, .left=NULL, .right=NULL};
  rt2[0].left  = &rt2[1];  // 1 <-- 0 [0's left]
  rt2[0].right = &rt2[2];  // 0 --> 3 [0's right]

  ret = getAllElements(rt1, rt2, &returnSize);
  for (int i=0; i<returnSize; ++i)
    debug("Output = %d", ret[i]);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [test] L=197 :Output = 0
   [test] L=197 :Output = 1
   [test] L=197 :Output = 1
   [test] L=197 :Output = 2
   [test] L=197 :Output = 3
   [test] L=197 :Output = 4
**/
