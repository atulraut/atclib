/***
    Medium: 62. Unique Paths
    A robot is located at the top-left corner of a m x n grid (marked
    'Start' in the diagram below).

    The robot can only move either down or right at any point in time.
    The robot is trying to reach the bottom-right corner of the grid
    (marked 'Finish' in the diagram below).

    How many possible unique paths are there ?

    Input: m = 3, n = 7
    Output: 28

    Input: m = 3, n = 2
    Output: 3
    Explanation:
    From the top-left corner, there are a total of 3 ways to reach the bottom-right corner:
    1. Right -> Down -> Down
    2. Down -> Down -> Right
    3. Down -> Right -> Down

    Input: m = 7, n = 3
    Output: 28

    Input: m = 3, n = 3
    Output: 6

    Constraints:
    1 <= m, n <= 100
    It's guaranteed that the answer will be less than or equal to 2 * 109.

    https://leetcode.com/problems/unique-paths/
    https://www.youtube.com/watch?v=rBAxUTqvlQA

    Date: 30 April 2021.
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

int uniquePaths(int m, int n) {
  int ret = 0;
  int dp[m][n];

  for(int i=0;i<m;++i) {
    for(int j=0;j<n;++j) {
      if(i==0 || j==0)
	dp[i][j] = 1;
      else {
	debug("i=%d j=%d, dp1=%d dp2 = %d",i, j, dp[i-1][j], dp[i][j-1]);
	dp[i][j] = dp[i-1][j] + dp[i][j-1];
	ret = dp[i][j];
      }
    }
  }
  return ret;
  return dp[m-1][n-1];
}

int main () {
  int m1 = 3, n1 = 7;
  int m = 3, n = 3;
  int ret = uniquePaths(m, n);

  debug("Output = %d", ret);

  return 0;
}

/**
   Complexity Analysis

   Time complexity: O(N×M)
   Space complexity: O(N×M)
**/

/**
   => ./a.out
   [uniquePaths] L=60 :i=1 j=1, dp1=1 dp2 = 1
   [uniquePaths] L=60 :i=1 j=2, dp1=1 dp2 = 2
   [uniquePaths] L=60 :i=2 j=1, dp1=2 dp2 = 1
   [uniquePaths] L=60 :i=2 j=2, dp1=3 dp2 = 3
   [main] L=73 :Output = 6
**/
