/***
    Easy:746. Min Cost Climbing Stairs

    You are given an integer array cost where cost[i] is the cost of ith step
    on a staircase. Once you pay the cost, you can either climb one or two steps.
    You can either start from the step with index 0, or the step with index 1.

    Return the minimum cost to reach the top of the floor.

    Input: cost = [10,15,20]
    Output: 15
    Explanation: Cheapest is: start on cost[1], pay that cost, and go to the top.

    Input: cost = [1,100,1,1,1,100,1,1,100,1]
    Output: 6
    Explanation: Cheapest is: start on cost[0], and only step on 1s, skipping cost[3].

    Constraints:
    2 <= cost.length <= 1000
    0 <= cost[i] <= 999

    https://leetcode.com/problems/min-cost-climbing-stairs/

    Date: 21 June 2021
    San Diego, CA.
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

int minCostClimbingStairs(int* cost, int costSize){
  int a, b, tmp;
  a = b = 0;
  for (int j = costSize - 1; j >= 0; --j) {
    tmp = a;
    a = cost[j] + (a < b ? a : b);
    b = tmp;
  }
  return (a < b) ? a : b;
}

/*
  #define min(a,b) (a>b?b:a)

  int minCostClimbingStairs(int* cost, int costSize){

  int i=0,j=0;
  int n=costSize;
  int dp[1002];
  dp[0]=0;
  dp[1]=0;
  for(i=2;i<=n;i++)
  dp[i]=INT_MAX;

  for(i=0;i<n;i++){
  for(j=i+1;j<=n && j<=i+2;j++){
  dp[j]=min(dp[j],dp[i]+cost[i]);
  }
  }
  return dp[costSize];


  }
*/

int main () {
  int ret = 0;

  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=79 :Output = 0
**/
