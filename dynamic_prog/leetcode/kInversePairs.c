/***
    Hard: 629. K Inverse Pairs Array


    For an integer array nums, an inverse pair is a pair of integers
    [i, j] where 0 <= i < j < nums.length and nums[i] > nums[j].

    Given two integers n and k, return the number of different arrays consist
    of numbers from 1 to n such that there are exactly k inverse pairs.
    Since the answer can be huge, return it modulo 109 + 7.

    Input: n = 3, k = 0
    Output: 1
    Explanation: Only the array [1,2,3] which consists of numbers from 1 to 3
    has exactly 0 inverse pairs.

    Input: n = 3, k = 1
    Output: 2
    Explanation: The array [1,3,2] and [2,1,3] have exactly 1 inverse pair.

    https://leetcode.com/problems/k-inverse-pairs-array/
    Date: 19 May 2021
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

unsigned int min(unsigned a, unsigned b) {
  return a < b ? a : b;
}

unsigned** create_matrix(int rows, int cols) {
  unsigned** mat = (unsigned**)malloc(rows * sizeof(unsigned *));
  for (unsigned i=0; i<rows; i++)
    mat[i] = (unsigned *)malloc(cols * sizeof(unsigned));

  return mat;
}

int kInversePairs(int n, int k) {
  //int[][] dp = new int[n + 1][k + 1];
  unsigned **dp = create_matrix(n+1, k+1);

  for (unsigned i = 1; i <= n; i++) {
    for (int j = 0; j <= k; j++) {
      if (j == 0)
	dp[i][j] = 1;
      else {
	for (int p = 0; p <= min(j, i - 1); p++)
	  dp[i][j] = (dp[i][j] + dp[i - 1][j - p]) % 1000000007;
      }
    }
  }
  return dp[n][k];
}

int main () {
  int ret = 0;
  int n = 3;
  int k = 1;
  ret =  kInversePairs(n, k);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=73 :Output = 2
**/
