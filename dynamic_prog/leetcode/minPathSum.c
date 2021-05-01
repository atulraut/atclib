/***
    Medium: 64. Minimum Path Sum
    https://leetcode.com/problems/minimum-path-sum/
    Given a m x n grid filled with non-negative numbers,
    find a path from top left to bottom right, which minimizes
    the sum of all numbers along its path.

    Note: You can only move either down or right at any point in time.

    Input: grid = [[1,3,1],[1,5,1],[4,2,1]]
    Output: 7
    Explanation: Because the path 1 → 3 → 1 → 1 → 1 minimizes the sum.

    Input: grid = [[1,2,3],[4,5,6]]
    Output: 12

    Constraints:
    m == grid.length
    n == grid[i].length
    1 <= m, n <= 200
    0 <= grid[i][j] <= 100

    Date : May 1, 2021.
    San Diego, CA
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
#define min(x, y) ( ((x) < (y)) ? (x) : (y) )

#define ROWS 2//3
#define COLS 3

/***
    4ms
 */
int minPathSum(int** grid, int gridSize, int* gridColSize){
  int** memo = NULL;
  int row = gridSize;
  int col = gridColSize[0];
  int r, c;
  int min_val = 0;

  debug("Enter");
  memo = (int**)malloc(sizeof(int*) * row);
  for (r = 0; r < row; r++)
    memo[r] = (int*)malloc(sizeof(int) * col);

  memo[0][0] = grid[0][0];

  // only comes from left: Fill 1st Row
  for (c = 1; c < col; c++)
    memo[0][c] = memo[0][c - 1] + grid[0][c];

  // only comes from top: Fill 1st Col
  for (r = 1; r < row; r++)
    memo[r][0] = memo[r - 1][0] + grid[r][0];

  // min(top, left) + current cost
  for (r = 1; r < row; r++) {
    for (c = 1; c < col; c++) {
      memo[r][c] = min(memo[r][c - 1], memo[r - 1][c]) + grid[r][c];
    }
  }

  min_val = memo[row - 1][col - 1];

  for (r = 0; r < row; r++)
    free(memo[r]);

  free(memo);

  return min_val;
}

/***
    Runtime Error: To Fix, allocate local array.
 */
int minPathSum2(int** grid, int gridSize, int* gridColSize) {
  int i = 0, j = 0;
  int ROW = gridSize;
  int COL = *gridColSize;
  for(i=0;i<ROW;++i)
    for(j=0;j<COL;++j)
      debug("out = %d", grid[i][j]);

  if (ROW == 0)
    return 0;

  int dp[ROW][COL];      // = {0}; Error - Variable size object initialize
  dp[0][0] = grid[0][0];

  /* Fill 1st Row */
  for (i=1; i<COL; i++) {
    dp[0][i] = dp[0][i-1] + grid[0][i];
  }

  /* Fill 1st Col */
  for(i=0; i<ROW; i++)
    dp[i][0] = dp[i-1][0] + grid[i][0];

  /* Fill Rest of the Cell. */
  for (i=1; i<ROW; ++i)
    for (j=1; j<COL; ++j)
      dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1]);

  return dp[ROW-1][COL-1];
}

int** create_matrix(int rows, int cols) {
  int** mat = (int**) malloc(rows * sizeof(int*));
  int i;
  for (i = 0; i < rows; i++)
    mat[i] = (int*)malloc(cols * sizeof(int));
  return mat;
}


int main () {
  int **obstacleGrid = create_matrix(ROWS, COLS);
  int gridSize = ROWS;
  int gridColSize = COLS;

  //*(*(arr+i)+j)
  //Ex-1: Input: grid = [[1,3,1],[1,5,1],[4,2,1]]
  /*
   *(*(obstacleGrid + 0) + 0) = 1;
   *(*(obstacleGrid + 0) + 1) = 3;
   *(*(obstacleGrid + 0) + 2) = 1;

   *(*(obstacleGrid + 1) + 0) = 1;
   *(*(obstacleGrid + 1) + 1) = 5;
   *(*(obstacleGrid + 1) + 2) = 1;

   *(*(obstacleGrid + 2) + 0) = 4;
   *(*(obstacleGrid + 2) + 1) = 2;
   *(*(obstacleGrid + 2) + 2) = 1;
   */
  //Ex-2:  [[1,2,3],[4,5,6]]
  *(*(obstacleGrid + 0) + 0) = 1;
  *(*(obstacleGrid + 0) + 1) = 2;
  *(*(obstacleGrid + 0) + 2) = 3;

  *(*(obstacleGrid + 1) + 0) = 4;
  *(*(obstacleGrid + 1) + 1) = 5;
  *(*(obstacleGrid + 1) + 2) = 6;

  int ret = minPathSum(obstacleGrid, gridSize, &gridColSize);
  debug("Output = %d", ret);

  return 0;
}

/**
   [main] L=114 :Output = 12
**/
