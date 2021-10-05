/***
    Climbing Stairs
    You are climbing a staircase. It takes n steps
    to reach the top.

    Each time you can either climb 1 or 2 steps.
    In how many distinct ways can you climb to the top?

    Input: n = 2
    Output: 2
    Explanation: There are two ways to climb to the top.
    1. 1 step + 1 step
    2. 2 steps

    Input: n = 3
    Output: 3
    Explanation: There are three ways to climb to the top.
    1. 1 step + 1 step + 1 step
    2. 1 step + 2 steps
    3. 2 steps + 1 step

    Constraints:

    1 <= n <= 45

    https://leetcode.com/problems/climbing-stairs/
    Date: 10-04-2021
    Fair Oaks, CA.
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

/*
  Dynamic Programming - Algorithm :
  As we can see this problem can be broken into subproblems,
  and it contains the optimal substructure property
  i.e. its optimal solution can be constructed efficiently
  from optimal solutions of its subproblems, we can use
  dynamic programming to solve this problem.

  One can reach ith step in one of the two ways:

  1. Taking a single step from (i-1)^{th} step.
  2. Taking a step of 22 from (i-2)^{th} step.

  So, the total number of ways to reach i^{th}
  is equal to sum of ways of reaching (i-1)^{th}
  step and ways of reaching (i-2)^{th} step.

  Let dp[i]dp[i] denotes the number of ways to reach on ith
  step:
  dp[i]=dp[i-1]+dp[i-2]
*/

int climbStairs(int n) {
  if (n == 1) {
    return 1;
  }
  int* dp = (int *)calloc((n + 1), sizeof(int));
  dp[1] = 1;
  dp[2] = 2;

  for (int i = 3; i <= n; i++)
    dp[i] = dp[i - 1] + dp[i - 2];

  return dp[n];
}

/*
  Complexity Analysis

  Time complexity : O(n). Single loop upto n.
  Space complexity : O(n). dp array of size n is used.
*/

int main (int argc, char **argv) {
  int ret = 0;

  ret =  climbStairs(3);
  debug("Output = %d", ret);
  return 0;
}

/**
   [main] L=91 :Output = 3
**/
