/***
    https://leetcode.com/problems/house-robber-iii/
    House Robber III

    The thief has found himself a new place for his thievery again.
    There is only one entrance to this area, called root.

    Besides the root, each house has one and only one parent house.
    After a tour, the smart thief realized that all houses in this place
    form a binary tree. It will automatically contact the police if
    two directly-linked houses were broken into on the same night.

    Given the root of the binary tree, return the maximum amount of m
    oney the thief can rob without alerting the police.

    Input: root = [3,2,3,null,3,null,1]
    Output: 7
    Explanation: Maximum amount of money the thief can rob = 3 + 3 + 1 = 7.
    Example 2:


    Input: root = [3,4,5,1,3,null,1]
    Output: 9
    Explanation: Maximum amount of money the thief can rob = 4 + 5 = 9.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 12/5/2021
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
/*----------------------------------- Micro --------------------------------------*/

int max(int a, int b) {
  return a > b ? a : b;
}

int rob(int* nums, int numsSize) {
  int* sum = (int*)calloc(numsSize + 1, sizeof(int));
  sum[0] = 0;
  sum[1] = nums[0];

  for(int i = 2; i <= numsSize; i++)
    sum[i] = max(sum[i - 1], nums[i - 1] + sum[i - 2]);

  return sum[numsSize];
}

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int rob1(int* nums, int numsSize) {
  int i;
  int *dp = malloc(sizeof(int) * numsSize);

  if (numsSize == 0)
    return 0;

  for (i = 0; i < numsSize; i++) {
    switch(i) {
    case 0:
      dp[i] = nums[0];
      break;
    case 1:
      dp[i] = MAX(nums[i], dp[i - 1]);
      break;
    default:
      dp[i] = MAX(nums[i] + dp[i - 2], dp[i - 1]);
    }
  }

  return dp[numsSize - 1];
}

int rob2(int* nums, int numsSize) {
  int sum = 0;
  for (int i=0; i<numsSize; ++i) {
    sum += nums[i];
    ++i;
  }
  return sum;
}

int main (int argc, char **argv) {
  int ret = 0;
  int nums[] = {1,2,3,1};
  int numsSize = 4;

  ret = rob(nums, numsSize);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=103 :Output = 4
**/
