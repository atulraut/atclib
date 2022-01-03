/***
    https://leetcode.com/problems/sign-of-the-product-of-an-array/
    1822. Sign of the Product of an Array

    There is a function signFunc(x) that returns:

    1 if x is positive.
    -1 if x is negative.
    0 if x is equal to 0.
    You are given an integer array nums. Let product be the
    product of all values in the array nums.

    Return signFunc(product).

    Input: nums = [-1,-2,-3,-4,3,2,1]
    Output: 1
    Explanation: The product of all values in the array is 144, and signFunc(144) = 1

    Input: nums = [1,5,0,2,-3]
    Output: 0
    Explanation: The product of all values in the array is 0, and signFunc(0) = 0

    Input: nums = [-1,1,-1,1,-1]
    Output: -1
    Explanation: The product of all values in the array is -1, and signFunc(-1) = -1

    Constraints:
    1 <= nums.length <= 1000

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Jan, 2, 2022
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

/* Using BitWise */
int arraySign2(int* nums, int numsSize) {
  char negatives = 0;
  char zeroes = 0;
  for (int idx = 0; idx < numsSize; ++idx) {
    negatives ^= (nums[idx] < 0);
    zeroes = zeroes || (nums[idx] == 0);
  }
  return zeroes ? 0 : (negatives == 1 ) ? -1 : 1;
}

/* AR version */
int arraySign1(int* nums, int numsSize) {
  int nvcnt = 0;
  for (int i=0; i<numsSize; ++i) {
    if (nums[i] == 0)
      return 0;
    if (nums[i] < 0)
      nvcnt++;
  }
  if (nvcnt % 2 == 0)
    return 1;
  else
    return -1;
}

int signFunc(int x) {
  if(x>0)
    return 1;
  if(x==0)
    return 0;
  else
    return -1;
}

/* 2ms */
int arraySign(int* nums, int numsSize) {
  int product=1;
  for(int i=0; i<numsSize; i++) {
    product = product*nums[i];
    product = signFunc(product);
  }
  return product;
}


int main (int argc, char **argv) {
  int ret = 0;
  int nums[] = {-1,1,-1,1,-1};
  int numsSize = arrsz(nums);

  ret = arraySign(nums, numsSize);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=87 :Output = -1
**/
