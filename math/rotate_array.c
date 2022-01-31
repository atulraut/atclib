/***
    https://leetcode.com/problems/rotate-array/
    Rotate Array

    Given an array, rotate the array to the right by k steps,
    where k is non-negative.

    Input: nums = [1,2,3,4,5,6,7], k = 3
    Output: [5,6,7,1,2,3,4]
    Explanation:
    rotate 1 steps to the right: [7,1,2,3,4,5,6]
    rotate 2 steps to the right: [6,7,1,2,3,4,5]
    rotate 3 steps to the right: [5,6,7,1,2,3,4]

    Input: nums = [-1,-100,3,99], k = 2
    Output: [3,99,-1,-100]
    Explanation:
    rotate 1 steps to the right: [99,-1,-100,3]
    rotate 2 steps to the right: [3,99,-1,-100]

    Constraints:
    1 <= nums.length <= 105
    -231 <= nums[i] <= 231 - 1
    0 <= k <= 105

    Follow up:
    Try to come up with as many solutions as you can.
    There are at least three different ways to solve this problem.
    Could you do it in-place with O(1) extra space?

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date:
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

void rotate(int* nums, int numsSize, int k) {
  int result[numsSize];
  for(int i = 0; i < numsSize; i++) {
    debug ("Place-> %d", ((i+k)%numsSize));
    result[(i+k)%numsSize]=nums[i];
  }
  for(int j = 0; j < numsSize; j++)
    nums[j]=result[j];
}

void test1DArray() {
  int nums[] = {1,2,3,4,5,6,7};
  int k = 3;
  int numsSize = sizeof(nums)/sizeof(nums[0]);
  printf ("------ Input -------\n");
  for (int i=0; i<numsSize; ++i)
    printf ("nums[%d] = %d\n", i, nums[i]);
  rotate(nums, numsSize, k);
  printf ("------ Output -------\n");
  for (int i=0; i<numsSize; ++i)
    printf ("nums[%d] = %d\n", i, nums[i]);
}

int main() {
  test1DArray();
  return 0;
}

/**
   => ./a.out
   ------ Input -------
   nums[0] = 1
   nums[1] = 2
   nums[2] = 3
   nums[3] = 4
   nums[4] = 5
   nums[5] = 6
   nums[6] = 7
   [rotate] L=66 :Place-> 3
   [rotate] L=66 :Place-> 4
   [rotate] L=66 :Place-> 5
   [rotate] L=66 :Place-> 6
   [rotate] L=66 :Place-> 0
   [rotate] L=66 :Place-> 1
   [rotate] L=66 :Place-> 2
   ------ Output -------
   nums[0] = 5
   nums[1] = 6
   nums[2] = 7
   nums[3] = 1
   nums[4] = 2
   nums[5] = 3
   nums[6] = 4
**/
