/***
    Medium: 63. Unique Paths II

    A robot is located at the top-left corner of a m x n grid (marked 'Start'
    in the diagram below).

    The robot can only move either down or right at any point in time.
    The robot is trying to reach the bottom-right corner of the grid
    (marked 'Finish' in the diagram below).

    Now consider if some obstacles are added to the grids.
    How many unique paths would there be?

    An obstacle and space is marked as 1 and 0 respectively in the grid.

    Input: obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
    Output: 2
    Explanation: There is one obstacle in the middle of the 3x3 grid above.
    There are two ways to reach the bottom-right corner:
    1. Right -> Right -> Down -> Down
    2. Down -> Down -> Right -> Right

    Input: obstacleGrid = [[0,1],[0,0]]
    Output: 1

    Constraints:
    m == obstacleGrid.length
    n == obstacleGrid[i].length
    1 <= m, n <= 100
    obstacleGrid[i][j] is 0 or 1.

    https://leetcode.com/problems/unique-paths-ii/
    https://www.youtube.com/watch?v=z6kelCB0ww4

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

#define ROWS 3
#define COLS 3

int uniquePathsWithObstacles(int** obstacleGrid, int obstacleGridSize, int* obstacleGridColSize) {
  int rows = obstacleGridSize;
  int cols = *obstacleGridColSize;
  int dp[rows][cols];

  bool flag = false;
  // If the starting cell has an obstacle, then simply return as there would be
  // no paths to the destination.
  if (obstacleGrid[0][0] == 1) {
    return 0;
  }
  //Fill  1st row
  for(int i=0;i<cols;++i) {
    if(flag || obstacleGrid[0][i]==1) {
      flag = true;
      dp[0][i] = 0;
    }
    else
      dp[0][i] = 1;
  }

  for(int i=0; i<rows; ++i)
    for(int j=0; j<cols; ++j)
      debug("dp[%d][%d]=%d",i, j, dp[i][j]);

  debug("____R Ends ____");

  //Fill 1st column
  flag = false;
  for(int i=0;i<rows;++i) {
    if(flag || obstacleGrid[i][0]==1) {
      flag = true;
      dp[i][0] = 0;
    }
    else
      dp[i][0] = 1;
  }

  for(int i=0; i<rows; ++i)
    for(int j=0; j<cols; ++j)
      debug("dp[%d][%d]=%d",i, j, dp[i][j]);

  debug("____C+R Ends____");

  for(int i=1;i<rows;++i) {
    for(int j=1;j<cols;++j) {
      if(obstacleGrid[i][j]==1)
	dp[i][j] = 0;
      else
	dp[i][j] = dp[i-1][j] + dp[i][j-1];
    }
  }

  for(int i=0; i<rows; ++i)
    for(int j=0; j<cols; ++j)
      debug("dp[%d][%d]=%d",i, j, dp[i][j]);

  debug("____Ends____");

  return dp[rows-1][cols-1];
}

int** create_matrix(int rows, int cols) {
    int** mat = (int**) malloc(rows * sizeof(int*));
    int i;
    for (i = 0; i < rows; i++)
        mat[i] = (int*)malloc(cols * sizeof(int));
    return mat;
}

int main () {
  int obstacleGrid1[ROWS][COLS] = {
    {0, 0, 0},
    {0, 1, 0},
    {0, 0, 0},
  };

  int **obstacleGrid = create_matrix(ROWS, COLS);

  int obstacleGridSize = ROWS;//sizeof(obstacleGrid)/ sizeof(obstacleGrid[0]);;
  int obstacleGridColSize = COLS;

  //*(*(arr+i)+j)
  *(*(obstacleGrid + 0) + 0) = 0;
  *(*(obstacleGrid + 0) + 1) = 0;
  *(*(obstacleGrid + 0) + 2) = 0;

  *(*(obstacleGrid + 1) + 0) = 0;
  *(*(obstacleGrid + 1) + 1) = 1;
  *(*(obstacleGrid + 1) + 2) = 0;

  *(*(obstacleGrid + 2) + 0) = 0;
  *(*(obstacleGrid + 2) + 1) = 0;
  *(*(obstacleGrid + 2) + 2) = 0;

  int ret = uniquePathsWithObstacles(obstacleGrid, obstacleGridSize, &obstacleGridColSize);

  debug("Output = %d", ret);

  return 0;
}

/**
   Complexity Analysis

    Time Complexity: O(M×N)O
    Space Complexity: O(1)
**/

/**
   => ./a.out
   [uniquePathsWithObstacles] L=77 :dp[0][0]=1
   [uniquePathsWithObstacles] L=77 :dp[0][1]=1
   [uniquePathsWithObstacles] L=77 :dp[0][2]=1
   [uniquePathsWithObstacles] L=77 :dp[1][0]=48
   [uniquePathsWithObstacles] L=77 :dp[1][1]=0
   [uniquePathsWithObstacles] L=77 :dp[1][2]=0
   [uniquePathsWithObstacles] L=77 :dp[2][0]=0
   [uniquePathsWithObstacles] L=77 :dp[2][1]=0
   [uniquePathsWithObstacles] L=77 :dp[2][2]=91
   [uniquePathsWithObstacles] L=79 :____R Ends ____
   [uniquePathsWithObstacles] L=94 :dp[0][0]=1
   [uniquePathsWithObstacles] L=94 :dp[0][1]=1
   [uniquePathsWithObstacles] L=94 :dp[0][2]=1
   [uniquePathsWithObstacles] L=94 :dp[1][0]=1
   [uniquePathsWithObstacles] L=94 :dp[1][1]=0
   [uniquePathsWithObstacles] L=94 :dp[1][2]=0
   [uniquePathsWithObstacles] L=94 :dp[2][0]=1
   [uniquePathsWithObstacles] L=94 :dp[2][1]=0
   [uniquePathsWithObstacles] L=94 :dp[2][2]=91
   [uniquePathsWithObstacles] L=96 :____C+R Ends____
   [uniquePathsWithObstacles] L=109 :dp[0][0]=1
   [uniquePathsWithObstacles] L=109 :dp[0][1]=1
   [uniquePathsWithObstacles] L=109 :dp[0][2]=1
   [uniquePathsWithObstacles] L=109 :dp[1][0]=1
   [uniquePathsWithObstacles] L=109 :dp[1][1]=0
   [uniquePathsWithObstacles] L=109 :dp[1][2]=1
   [uniquePathsWithObstacles] L=109 :dp[2][0]=1
   [uniquePathsWithObstacles] L=109 :dp[2][1]=1
   [uniquePathsWithObstacles] L=109 :dp[2][2]=2
   [uniquePathsWithObstacles] L=111 :____Ends____
   [main] L=151 :Output = 2
**/
