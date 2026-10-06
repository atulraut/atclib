/***
    Hard: 315. Count of Smaller Numbers After Self
    https://leetcode.com/problems/count-of-smaller-numbers-after-self/

    You are given an integer array nums and you have to return a new counts array.
    The counts array has the property where counts[i] is the number of
     smaller elements to the right of nums[i].

    Input: nums = [5,2,6,1]
    Output: [2,1,1,0]
    Explanation:
    To the right of 5 there are 2 smaller elements (2 and 1).
    To the right of 2 there is only 1 smaller element (1).
    To the right of 6 there is 1 smaller element (1).
    To the right of 1 there is 0 smaller element.

    Input: nums = [-1]
    Output: [0]

    Input: nums = [-1,-1]
    Output: [0,0]

    Constraints:
    1 <= nums.length <= 105
    -104 <= nums[i] <= 104

    Date: June 29, 2021
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
 * Note: The returned array must be malloced, assume caller calls free().
 */
#define LSB(x)  ((x) & -(x))    // zeroes all the bits except the least significant one

int max(int x, int y) { return x > y ? x : y; }
int min(int x, int y) { return x < y ? x : y; }

int get_sum(int *tree, int size, int i) {
  int sum = 0;

  while (i > 0) {
    sum += tree[i];
    i -= LSB(i);
  }

  return sum;
}

void update(int *tree, int size, int i) {
  while (i < size) {
    tree[i]++;
    i += LSB(i);
  }
}

int *countSmaller(int *nums, int size, int *returnSize) {
  int *res = NULL;
  int min_elem = INT_MAX;
  int max_elem = INT_MIN;

  *returnSize = size;
  if (!size)
    return NULL;

  res = malloc(size * sizeof(int));

  for (int i = 0; i < size; ++i)
    min_elem = min(min_elem, nums[i]);

  for (int i = 0; i < size; ++i) {
    nums[i] = nums[i] - min_elem + 1;
    max_elem = max(max_elem, nums[i]);
  }

  int tree[max_elem + 1];
  memset(tree, 0x0, sizeof(tree));

  for (int i = size - 1; i >= 0; --i) {
    res[i] = get_sum(tree, max_elem + 1, nums[i] - 1);
    update(tree, max_elem + 1, nums[i]);
  }

  return res;
}

int main () {
  int *ret;

  int nums[] = {5,2,6,1};
  int returnSize;
  int size = sizeof(nums)/sizeof(nums[0]);

  ret = countSmaller(nums, size, &returnSize);

  for (int i=0; i<returnSize; ++i)
    debug("Output = %d", ret[i]);
  return 0;
}

/**
   => ./a.out
   [main] L=111 :Output = 2
   [main] L=111 :Output = 1
   [main] L=111 :Output = 1
   [main] L=111 :Output = 0
**/
