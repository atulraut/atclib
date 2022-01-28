/***
    https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/
    Maximum XOR of Two Numbers in an Array

    Given an integer array nums, return the maximum result
    of nums[i] XOR nums[j], where 0 <= i <= j < n.

    Input: nums = [3,10,5,25,2,8]
    Output: 28
    Explanation: The maximum result is 5 XOR 25 = 28.

    Input: nums = [14,70,53,83,49,91,36,80,92,51,66,70]
    Output: 127

    Constraints:

    1 <= nums.length <= 2 * 105
    0 <= nums[i] <= 231 - 1

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Jan 27, 2022
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
#define max_(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a > _b ? _a : _b; })
#define min(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

struct QuadTree {
  struct QuadTree *zeroPoint;
  struct QuadTree *onePoint;
};

int max(int a, int b) {
  if(a >= b)
    return a;
  return b;
}

struct QuadTree *newNode() {
  struct QuadTree *temp;
  temp = malloc(sizeof(struct QuadTree));
  temp->zeroPoint = NULL;
  temp->onePoint = NULL;
  return temp;
};

void insertQuad(struct QuadTree *head, int num) {
  unsigned int maxValue = (unsigned int)1 << 31;
  struct QuadTree *temp = head;

  while(maxValue) {
    if(num&maxValue) {
      if(!temp->onePoint)
	temp->onePoint = newNode();
      temp = temp->onePoint;
    }
    else {
      if(!temp->zeroPoint)
	temp->zeroPoint = newNode();
      temp = temp->zeroPoint;
    }
    maxValue = (maxValue >> 1);
  }
  return;
}

void insertMax(struct QuadTree *head, int num, int *result) {
  unsigned int maxValue = (unsigned int)1 << 31;
  struct QuadTree *temp = head, *otherBranch = head;
  int tempResult = 0;
  while(maxValue) {
    if(num&maxValue) {
      if(!temp->onePoint)
	temp->onePoint = newNode();
      temp = temp->onePoint;
      if(otherBranch->zeroPoint) {
	tempResult += maxValue;
	otherBranch = otherBranch->zeroPoint;
      } else
	otherBranch = otherBranch->onePoint;
    } else {
      if(!temp->zeroPoint)
	temp->zeroPoint = newNode();
      temp = temp->zeroPoint;
      if(otherBranch->onePoint){
	tempResult += maxValue;
	otherBranch = otherBranch->onePoint;
      }
      else
	otherBranch = otherBranch->zeroPoint;
    }
    maxValue = (maxValue >> 1);
  }
  (*result) = max((*result), tempResult);
  return;
}

int findMaximumXOR(int* nums, int numsSize) {
  struct QuadTree *head = newNode();
  insertQuad(head, nums[0]);
  int result = INT_MIN;
  for(int x = 1; x < numsSize; x++)
    insertMax(head, nums[x], &result);
  if(result == INT_MIN)
    return 0;
  return result;
}

/**
 * 2nd approch :
 */
#define MAX_BIT 30
struct tree {
  struct tree *leaf[2]; /* bit 0 --> leaf 0 ; bit 1 --> leaf 1*/
};


static void buildTree(struct tree *root, int *nums, int numsSize) {
  int i;
  int j;
  int bit_val;
  struct tree *node = NULL;

  for (i = 0; i < numsSize; i++) {
    node = root;
    for (j = MAX_BIT; j >= 0; j--) {
      bit_val = nums[i] >> j & 1;
      if (!node->leaf[bit_val])
	node->leaf[bit_val] = calloc(1, sizeof(*root));
      node = node->leaf[bit_val];
    }
  }
}

void freeTree(struct tree *root) {
  if (!root)
    return;

  if (root->leaf[0]);
  freeTree(root->leaf[0]);
  if (root->leaf[1])
    freeTree(root->leaf[1]);
  free(root);
}

int findMaximumXOR_(int* nums, int numsSize) {
  struct tree root = {0};
  int i;
  int j;
  struct tree *node = NULL;
  int max = 0;
  int cur = 0;
  int bit_val = 0;

  if (1 == numsSize)
    return 0;

  buildTree(&root, nums, numsSize);

  for (i = 0; i < numsSize; i++) {
    cur = 0;
    node = &root;
    for (j = MAX_BIT; j >= 0; j--) {
      bit_val = nums[i] >> j & 1;
      if (node->leaf[!bit_val]) {
	cur += 1 << j;
	node = node->leaf[!bit_val];
      } else {
	node = node->leaf[bit_val];
      }
    }

    if (cur > max)
      max = cur;
  }

  freeTree(root.leaf[0]);
  freeTree(root.leaf[1]);
  return max;
}

void test() {
  int ret = 0;
  int nums[] = {3, 10, 5, 25, 2, 8};
  int numsSize = 6;

  ret = findMaximumXOR(nums, numsSize);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [test] L=212 :Output = 28
**/
