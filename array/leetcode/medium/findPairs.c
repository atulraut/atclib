/***
    https://leetcode.com/problems/k-diff-pairs-in-an-array
    K-diff Pairs in an Array

    Given an array of integers nums and an integer k,
    return the number of unique k-diff pairs in the array.

    A k-diff pair is an integer pair (nums[i], nums[j]),
    where the following are true:

    0 <= i < j < nums.length
    |nums[i] - nums[j]| == k
    Notice that |val| denotes the absolute value of val.

    Input: nums = [3,1,4,1,5], k = 2
    Output: 2
    Explanation: There are two 2-diff pairs in the array, (1, 3) and (3, 5).
    Although we have two 1s in the input, we should only
    return the number of unique pairs.

    Input: nums = [1,2,3,4,5], k = 1
    Output: 4
    Explanation: There are four 1-diff pairs in the array,
    (1, 2), (2, 3), (3, 4) and (4, 5).

    Input: nums = [1,3,1,5,4], k = 0
    Output: 1
    Explanation: There is one 0-diff pair in the array, (1, 1).

    Constraints:
    1 <= nums.length <= 104
    -107 <= nums[i] <= 107
    0 <= k <= 107

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address findPairs.c -lm

    Date: 2/9/2022 Feb
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

int cmpfunc (const void * a, const void * b) {
  return ( *(int*)a - *(int*)b );
}

int findPairs(int* nums, int numsSize, int k) {
  qsort(nums, numsSize, sizeof(int), cmpfunc);

  int i,j,total=0;
  for(i=0; i<numsSize-1; i++){
    if(i>0 && nums[i] == nums[i-1])
      continue;
    j=i+1;
    int diff=-1;
    while(diff<=k && j<numsSize){
      diff = nums[j] - nums[i];
      if(diff == k) {
	total++;
	break;
      }
      j++;
    }
  }
  return total;
}


void test() {
  int ret = 0;
  int nums[] = {3,1,4,1,5};
  int numsSize = 5;
  int k = 2;
  ret = findPairs(nums, numsSize, k);

  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [test] L=98 :Output = 2
**/
