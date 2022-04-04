/***
    https://leetcode.com/problems/split-array-largest-sum/
    Split Array Largest Sum

    Given an array nums which consists of non-negative integers
    and an integer m, you can split the array into m non-empty continuous subarrays.

    Write an algorithm to minimize the largest sum among these m subarrays.

    Input: nums = [7,2,5,10,8], m = 2
    Output: 18
    Explanation:
    There are four ways to split nums into two subarrays.
    The best way is to split it into [7,2,5] and [10,8],
    where the largest sum among the two subarrays is only 18.

    Input: nums = [1,2,3,4,5], m = 2
    Output: 9

    Input: nums = [1,4,4], m = 3
    Output: 4

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
#define max(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a > _b ? _a : _b; })
#define min(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

int get_howmany_subarray(int *nums, int numsSize, int max_val, int *max_sum) {
  int temp = 0;
  int count = 0;
  for(int i=0;i<numsSize;i++) {
    if(temp + nums[i] > max_val) {
      temp = nums[i];
      count++;
    }
    else {
      temp += nums[i];
    }
    if(*max_sum < temp) *max_sum = temp;
  }

  return count + 1;
}

int search_help(int *nums, int numsSize, int sum_l, int sum_h, int m) {
  int mid_sum = (sum_l + sum_h) / 2;
  int result = -1;

  int max_sum_in_array = 0;
  int split_n = get_howmany_subarray(nums, numsSize, mid_sum, &max_sum_in_array);
  // printf("%3d, %2d, %2d\n", mid_sum, split_n, max_sum_in_array);

  if(split_n <= m) {
    result = max_sum_in_array;
    // Go left
    if(sum_l < mid_sum) {
      int temp = search_help(nums, numsSize, sum_l, mid_sum-1, m);
      if(temp != -1) result = temp;
    }
  }
  else if(split_n > m) {
    // Go right
    if(sum_h > mid_sum) {
      int temp = search_help(nums, numsSize, mid_sum+1, sum_h, m);
      if(temp != -1) result = temp;
    }
  }


  return result;
}

int splitArray(int *nums, int numsSize, int m) {
  int sum_val = 0;
  int min_val = nums[0];
  int max_val = nums[0];
  for(int i=0;i<numsSize;i++) {
    sum_val += nums[i];
    if(min_val > nums[i]) min_val = nums[i];
    if(max_val < nums[i]) max_val = nums[i];
  }

  if(numsSize == m) {
    return max_val;
  }
  return search_help(nums, numsSize, min_val, sum_val, m);
}
void test() {
  int ret = 0;
  int nums[] = {7,2,5,10,8};
  int numsSize = 5;
  int m = 2;
  ret = splitArray(nums, numsSize, m);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [test] L=121 :Output = 18
**/
