/***
    Medium: 120. Triangle
    Given a triangle array, return the minimum path sum
    from top to bottom.
    For each step, you may move to an adjacent number of
    the row below. More formally, if you are on index i
    on the current row, you may move to either index i or
    index i + 1 on the next row.

    Input: triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
    Output: 11
    Explanation: The triangle looks like:
    2
    3 4
    6 5 7
    4 1 8 3
    The minimum path sum from top to bottom is 2 + 3 + 5 + 1 = 11 (underlined above).

    https://leetcode.com/problems/triangle/
    Date : 26/04/2021 April
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

#define min(a, b) ((a) < (b) ? (a) : (b))

/***
    0ms:
*/
int minimumTotal1(int** triangle, int triangleSize, int* triangleColSize) {
  int* dp = malloc(sizeof(int) * triangleSize);
  int i = 0;
  int j = 0;

  for(i=0; i<triangleColSize[triangleSize-1]; i++)
    dp[i] = triangle[triangleSize-1][i];

  for(i=triangleSize-2; i>=0; i--) {
    for(j=0; j<=i; j++) {
      dp[j] = min(triangle[i][j]+dp[j],triangle[i][j]+dp[j+1]);
    }
  }
  return dp[0];
}

/***
    8ms:
 */
int minimumTotal(int** triangle, int triangleSize, int* triangleColSize) {
  debug ("triangleSize = %d", triangleSize);

  for (int i = 1; i < triangleSize; ++i) {
    triangle[i][0] += triangle[i - 1][0];
    triangle[i][i] += triangle[i - 1][i - 1];
    for (int j = 1; j < i; ++j) {
      triangle[i][j] += min(triangle[i - 1][j - 1], triangle[i - 1][j]);
    }
  }

  int minimum = triangle[triangleSize - 1][0];
  for (int i = 0; i < triangleSize; ++i) {
    minimum = min(minimum, triangle[triangleSize - 1][i]);
  }
  return minimum;
}

int main() {
  int triangle[][4] = {
    {2},
    {3,4},
    {6,5,7},
    {4,1,8,3},
  };

  int row = sizeof(triangle) / sizeof(triangle[0]);
  int col = sizeof(triangle[0]) / sizeof(triangle[0][0]);
  int triangleSize = sizeof(triangle) / sizeof(triangle[0]);
  int triangleColSize;
  debug ("TriangleSize = %d", triangleSize);
  debug("row = %d, col = %d", row, col);

  int output =  minimumTotal(triangle, triangleSize, &triangleColSize);

  debug ("Output = %d", output);
  return 0;
}
