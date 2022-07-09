/***
    https://leetcode.com/problems/wiggle-subsequence/
    Wiggle Subsequence

    A wiggle sequence is a sequence where the differences
    between successive numbers strictly alternate between
    positive and negative. The first difference (if one exists)
    may be either positive or negative. A sequence with one
    element and a sequence with two non-equal elements are
    trivially wiggle sequences.

    For example, [1, 7, 4, 9, 2, 5] is a wiggle sequence because
    the differences (6, -3, 5, -7, 3) alternate between positive
    and negative.
    In contrast, [1, 4, 7, 2, 5] and [1, 7, 4, 5, 5] are not
    wiggle sequences. The first is not because its first two
    differences are positive, and the second is not because its
    last difference is zero.
    A subsequence is obtained by deleting some elements (possibly
    zero) from the original sequence, leaving the remaining
    elements in their original order.

    Given an integer array nums, return the length of the longest
    wiggle subsequence of nums.

    Input: nums = [1,7,4,9,2,5]
    Output: 6
    Explanation: The entire sequence is a wiggle sequence with
    differences (6, -3, 5, -7, 3).

    Input: nums = [1,17,5,10,13,15,10,5,16,8]
    Output: 7
    Explanation: There are several subsequences that achieve this length.
    One is [1, 17, 10, 13, 10, 16, 8] with differences (16, -7, 3, -3, 6, -8).

    Input: nums = [1,2,3,4,5,6,7,8,9]
    Output: 2

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Fri Jul  8 10:45:49 PM PDT 2022
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

#define max(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a > _b ? _a : _b; })

int wiggleMaxLength(int* nums, int numsSize) {
  if (numsSize < 2)
    return numsSize;
  int* up   = malloc(sizeof(int) * numsSize);
  int* down = malloc(sizeof(int) * numsSize);
  up[0] = down[0] = 1;

  for (int i = 1; i < numsSize; i++) {
    if (nums[i] > nums[i - 1]) {
      up[i] = down[i - 1] + 1;
      down[i] = down[i - 1];
    } else if (nums[i] < nums[i - 1]) {
      down[i] = up[i - 1] + 1;
      up[i] = up[i - 1];
    } else {
      down[i] = down[i - 1];
      up[i] = up[i - 1];
    }
  }
  return max(down[numsSize - 1], up[numsSize - 1]);
}

void test() {
  int ret = 0;
  int arr[] = {1, 7, 4, 9, 2, 5};
  int numsSize = sizeof(arr) / sizeof(arr[0]);
  ret =  wiggleMaxLength(arr, numsSize);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [test] L=103 :Output = 6
**/
