/***
    https://leetcode.com/problems/build-array-from-permutation/
    Build Array from Permutation

    Given a zero-based permutation nums (0-indexed), build an
    array ans of the same length where ans[i] = nums[nums[i]]
    for each 0 <= i < nums.length and return it.

    A zero-based permutation nums is an array of distinct
    integers from 0 to nums.length - 1 (inclusive).

    Input: nums = [0,2,1,5,3,4]
    Output: [0,1,2,4,5,3]
    Explanation: The array ans is built as follows:
    ans = [nums[nums[0]], nums[nums[1]], nums[nums[2]], nums[nums[3]], nums[nums[4]], nums[nums[5]]]
    = [nums[0], nums[2], nums[1], nums[5], nums[3], nums[4]]
    = [0,1,2,4,5,3]

    Input: nums = [5,0,1,2,3,4]
    Output: [4,5,0,1,2,3]
    Explanation: The array ans is built as follows:
    ans = [nums[nums[0]], nums[nums[1]], nums[nums[2]], nums[nums[3]], nums[nums[4]], nums[nums[5]]]
    = [nums[5], nums[0], nums[1], nums[2], nums[3], nums[4]]
    = [4,5,0,1,2,3]

    Constraints:
    1 <= nums.length <= 1000
    0 <= nums[i] < nums.length
    The elements in nums are distinct.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 27 Nov 2021
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

int* buildArray(int* nums, int numsSize, int* returnSize) {
  int* ans = (int*)malloc(numsSize * 4);
  *returnSize = numsSize;
  numsSize--;
  while(numsSize >= 0) {
    ans[numsSize] = *(nums + *(nums+numsSize));
    numsSize--;
  }
  return ans;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* buildArray2(int* nums, int numsSize, int* returnSize) {
  *returnSize = numsSize;
  int* ret = (int*) malloc(sizeof(int) * numsSize);
  for (int i = 0; i < numsSize; i++) {
    ret[i] = nums[nums[i]];
  }
  return ret;
}

int main (int argc, char **argv) {
  int *ret;
  int nums[] = {0,2,1,5,3,4};
  int numsSize = 6;
  int returnSize;

  ret =  buildArray(nums, numsSize, &returnSize);
  for (int i=0; i<returnSize; ++i)
    debug("Output = %d", ret[i]);

  return 0;
}

/**
   => ./a.out
   [main] L=94 :Output = 0
   [main] L=94 :Output = 1
   [main] L=94 :Output = 2
   [main] L=94 :Output = 4
   [main] L=94 :Output = 5
   [main] L=94 :Output = 3
**/
