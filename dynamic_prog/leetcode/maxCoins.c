/***
    https://leetcode.com/problems/burst-balloons
    312. Burst Balloons

    You are given n balloons, indexed from 0 to n - 1. Each balloon is painted
    with a number on it represented by an array nums. You are asked to
    burst all the balloons.

    If you burst the ith balloon, you will get nums[i - 1] * nums[i] * nums[i + 1] coins.
    If i - 1 or i + 1 goes out of bounds of the array, then treat it as if
    there is a balloon with a 1 painted on it.

    Return the maximum coins you can collect by bursting the balloons wisely.

    Input: nums = [3,1,5,8]
    Output: 167
    Explanation:
    nums = [3,1,5,8] --> [3,5,8] --> [3,8] --> [8] --> []
    coins =  3*1*5    +   3*5*8   +  1*3*8  + 1*8*1 = 167
    Example 2:

    Input: nums = [1,5]
    Output: 10


    Constraints:

    n == nums.length
    1 <= n <= 500
    0 <= nums[i] <= 100
    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Jan 1, 2022
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

int maxCoins(int* nums, int numsSize) {
  int *nums1 = (int*)malloc(sizeof(int)*(numsSize+2));
  nums1[0] = nums1[numsSize+1] = 1;

  for(int i = 0; i < numsSize; i++)
    nums1[i+1] = nums[i];

  numsSize += 2;

  int** maxs = (int**)malloc(sizeof(int*)*numsSize); //maxs store the max result between index i and j exclusively;

  for(int i = 0; i < numsSize; i++) {
    maxs[i] = (int*)malloc(sizeof(int)*numsSize);
    memset(maxs[i], 0, sizeof(int)*numsSize);
  }
  for(int i = 2; i < numsSize; i++) //start from length - 2 till length - size-1;
    for(int left = 0; left+i < numsSize; left++) {
      int right = left+i;
      for(int j = left+1; j < right; j++) {
	int t = maxs[left][j]+maxs[j][right]+nums1[left]*nums1[right]*nums1[j];
	if(t > maxs[left][right])
	  maxs[left][right] = t;
      }
    }
  return maxs[0][numsSize-1]; //the max between the first and last - extra 1;
}

int main (int argc, char **argv) {
  int ret = 0;
  int arr[] = {3,1,5,8};
  int sz = arrsz(arr);
  debug ("sz = %d", sz);
  ret = maxCoins(arr, sz);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=94 :sz = 4
   [main] L=96 :Output = 167
**/
