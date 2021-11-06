/***
    https://leetcode.com/problems/single-number-iii/submissions/
    Single Number III

    Given an integer array nums, in which exactly two elements
    appear only once and all the other elements appear exactly
    twice. Find the two elements that appear only once. You can
    return the answer in any order.

    You must write an algorithm that runs in linear runtime complexity
    and uses only constant extra space.

    Input: nums = [1,2,1,3,2,5]
    Output: [3,5]
    Explanation:  [5, 3] is also a valid answer.

    Input: nums = [-1,0]
    Output: [-1,0]

    Input: nums = [0,1]
    Output: [1,0]

    Constraints:

    2 <= nums.length <= 3 * 104
    -231 <= nums[i] <= 231 - 1
    Each integer in nums will appear twice, only two integers will appear once.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address singleNumber.c -lm

    Date: 5 Nov 2021
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
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* singleNumber(int* nums, int numsSize, int* returnSize) {
  if (!nums || (numsSize < 2))
    return NULL;

  unsigned int* ret = (unsigned int*)malloc(sizeof(int) * 2);
  if (ret) {
    unsigned int i, x = 0, y = 0, flag, tmp;
    for (i = 0; i < numsSize; i++)
      x ^= nums[i];
    flag = x & -x; //Get last bit of x https://leetcode.com/discuss/52377/3-lines-ruby-4-lines-c
    for (i = 0; i < numsSize; i++)
      if ((tmp = nums[i]) & flag) y ^= tmp;

    ret[0] = x ^ y;
    ret[1] = y;

    if (returnSize)
      *returnSize = 2;
  }
  return ret;
}

int main (int argc, char **argv) {
  int *ret;
  int nums[] = {1,2,1,3,2,5};
  int numsSize = sizeof(nums)/sizeof(nums[0]);
  int returnSize;

  ret = singleNumber(nums, numsSize, &returnSize);
  for (int i=0; i<returnSize; ++i)
    debug("Output = %d", ret[i]);

  free(ret);
  return 0;
}

/**
   => ./a.out
   [main] L=93 :Output = 5
   [main] L=93 :Output = 3
**/
