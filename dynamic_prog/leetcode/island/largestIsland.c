/***
    Hard: Making A Large Island
    You are given an n x n binary matrix grid. You are allowed to
    change at most one 0 to be 1.

    Return the size of the largest island in grid after applying
    this operation.
    An island is a 4-directionally connected group of 1s.

    Input: grid = [[1,0],[0,1]]
    Output: 3
    Explanation: Change one 0 to 1 and connect two 1s, then we get an island with area = 3.

    Input: grid = [[1,1],[1,0]]
    Output: 4
    Explanation: Change the 0 to 1 and make the island bigger, only one island with area = 4.

    Input: grid = [[1,1],[1,1]]
    Output: 4
    Explanation: Can't change any 0 to 1, only one island with area = 4.

    Constraints:
    n == grid.length
    n == grid[i].length
    1 <= n <= 500
    grid[i][j] is either 0 or 1.

    Date: August 03, 2021
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

int ** create_matrix(int rows, int cols) {
  int** max = (int **)malloc(rows * sizeof (int *));
  for (int i=0; i<rows; ++i)
    max[i] = (int *)malloc(cols * sizeof(int));

  return max;
}

int largestIsland(int** grid, int gridSize, int* gridColSize) {
  int flag = 0, i, j;
  int cnt = 0;

  for (i=0; i<gridSize; ++i) {
    for (j=0; j<*gridColSize; ++j) {
      debug("--> grid[%d][%d] = %d", i, j, grid[i][j]);
    }
  }
  //  return 1;
  for (i=0; i<gridSize; ++i) {
    for (j=0; j<*gridColSize; ++j) {
      if (grid[i][j] == 0) {
	if (!flag) {
	  grid[i][j] = 1;
	  flag = 1;
	  ++cnt;
	}
      } else
	  ++cnt;
    }
    debug("--> grid[%d][%d] = %d", i, j, grid[i][j]);
  }
  return cnt;
}

int main () {
  int ret = 0;
  int rows = 3;
  int cols = 3;
  int **grid = create_matrix(rows, cols);
  // Prob 1 : Works 2 * 2
/*
  *(*(grid + 0) + 0) = 1;
  *(*(grid + 0) + 1) = 1;
  *(*(grid + 1) + 0) = 1;
  *(*(grid + 1) + 1) = 0;
*/
  // Prob 2 : Fails
  *(*(grid + 0) + 0) = 1;
  *(*(grid + 0) + 1) = 0;
  *(*(grid + 0) + 2) = 1;
  *(*(grid + 1) + 0) = 0;
  *(*(grid + 1) + 1) = 0;
  *(*(grid + 1) + 2) = 0;
  *(*(grid + 2) + 0) = 0;
  *(*(grid + 2) + 1) = 1;
  *(*(grid + 2) + 2) = 1;

  ret = largestIsland(grid, rows, &cols);
  debug("Output = %d", ret);
  return 0;
}

/**

 **/
