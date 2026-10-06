/***
    https://leetcode.com/problems/island-perimeter
    Island Perimeter

    You are given row x col grid representing a map
    where grid[i][j] = 1 represents land and
    grid[i][j] = 0 represents water.

    Grid cells are connected horizontally/vertically
    (not diagonally). The grid is completely surrounded
    by water, and there is exactly one island (i.e.,
    one or more connected land cells).

    The island doesn't have "lakes", meaning the water
    inside isn't connected to the water around the island.
    One cell is a square with side length 1. The grid is
    rectangular, width and height don't exceed 100.
    Determine the perimeter of the island.

    Input: grid = [[0,1,0,0],[1,1,1,0],[0,1,0,0],[1,1,0,0]]
    Output: 16
    Explanation: The perimeter is the 16 yellow stripes
    in the image above.

    Input: grid = [[1]]
    Output: 4

    Input: grid = [[1,0]]
    Output: 4

    Constraints:
    row == grid.length
    col == grid[i].length
    1 <= row, col <= 100
    grid[i][j] is 0 or 1.
    There is exactly one island in grid.

    Date: 4/10/2021
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

int islandPerimeter(int** grid, int gridSize, int* gridColSize) {
  int ans = 0;

  for (int i = 0; i < gridSize; i++) {
    for (int j = 0; j < *gridColSize; j++) {
      if (grid[i][j] == 1) {
	ans += 2;
	if (i != 0 && grid[i - 1][j] == 1)
	  ans--;
	if (j != 0 && grid[i][j - 1] == 1)
	  ans--;
      }
    }
  }
  return ans * 2;
}

int** create_matrix(int rows, int cols) {
  int **grid = (int **)calloc(rows, sizeof(int*));
  for (int i=0; i<rows; ++i)
    grid[i] = (int *)calloc(cols, sizeof(int));

  return grid;
}

int main (int argc, char **argv) {
  int ret = 0;
  int **grid = create_matrix(4, 4);

  *(*(grid + 0) + 0) = 0;
  *(*(grid + 0) + 1) = 1;
  *(*(grid + 0) + 2) = 0;
  *(*(grid + 0) + 3) = 0;

  *(*(grid + 1) + 0) = 1;
  *(*(grid + 1) + 1) = 1;
  *(*(grid + 1) + 2) = 1;
  *(*(grid + 1) + 3) = 0;

  *(*(grid + 2) + 0) = 0;
  *(*(grid + 2) + 1) = 1;
  *(*(grid + 2) + 2) = 0;
  *(*(grid + 2) + 3) = 0;

  *(*(grid + 3) + 0) = 1;
  *(*(grid + 3) + 1) = 1;
  *(*(grid + 3) + 2) = 0;
  *(*(grid + 3) + 3) = 0;

  int gridSize = 4;
  int gridColSize = 4;

  ret = islandPerimeter(grid, gridSize, &gridColSize);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=108 :Output = 16
**/
