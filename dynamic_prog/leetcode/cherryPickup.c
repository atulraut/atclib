/***
    https://leetcode.com/problems/cherry-pickup-ii/
    1463. Cherry Pickup II

    You are given a rows x cols matrix grid representing a field of
    cherries where grid[i][j] represents the number of cherries that
    you can collect from the (i, j) cell.

    You have two robots that can collect cherries for you:

    Robot #1 is located at the top-left corner (0, 0), and
    Robot #2 is located at the top-right corner (0, cols - 1).
    Return the maximum number of cherries collection using both
    robots by following the rules below:

    From a cell (i, j), robots can move to
    cell (i + 1, j - 1), (i + 1, j), or (i + 1, j + 1).
    When any robot passes through a cell, It picks up all cherries,
    and the cell becomes an empty cell.
    When both robots stay in the same cell, only one takes the cherries.
    Both robots cannot move outside of the grid at any moment.
    Both robots should reach the bottom row in grid.

    Input: grid = [[3,1,1],[2,5,1],[1,5,5],[2,1,1]]
    Output: 24
    Explanation: Path of robot #1 and #2 are described in color green and blue respectively.
    Cherries taken by Robot #1, (3 + 2 + 5 + 2) = 12.
    Cherries taken by Robot #2, (1 + 5 + 5 + 1) = 12.
    Total of cherries: 12 + 12 = 24.

    Input: grid = [[1,0,0,0,0,0,1],[2,0,0,0,0,3,0],[2,0,9,0,0,0,0],[0,3,0,5,4,0,0],[1,0,2,3,0,0,6]]
    Output: 28
    Explanation: Path of robot #1 and #2 are described in color green and blue respectively.
    Cherries taken by Robot #1, (1 + 9 + 5 + 2) = 17.
    Cherries taken by Robot #2, (1 + 3 + 4 + 3) = 11.
    Total of cherries: 17 + 11 = 28.

    Constraints:
    rows == grid.length
    cols == grid[i].length
    2 <= rows, cols <= 70
    0 <= grid[i][j] <= 100

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 7 Jan 2021
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
#define atsizeof(object) (char *)(&object+1) - (char*)(&object)
#define arrsz(x)  (sizeof(x) / sizeof((x)[0]))
#define max(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a > _b ? _a : _b; })
#define min(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

int cherryPickup(int** grid, int gridSize, int* gridColSize) {
  int n = gridSize;
  int m = *gridColSize;
  int dp[70][71][71];
  memset(dp, -1, sizeof(dp));
  dp[1][1][m] = grid[0][0] + grid[0][m - 1];

  for(int i = 2; i <= n; ++i) {
    for(int j = 1; j <= m; ++j) {
      for(int k = 1; k <= m; ++k) {
	int t = -1;
	for(int dj = -1; dj <= 1; ++dj) {
	  for(int dk = -1; dk <= 1; ++dk) {
	    t = max(t, dp[i - 1][j + dj][k + dk]);
	  }
	}
	dp[i][j][k] = t;
	if (dp[i][j][k] == -1)
	  continue;
	if (j == k)
	  dp[i][j][k] += grid[i - 1][j - 1];
	else
	  dp[i][j][k] += (grid[i - 1][j - 1] + grid[i - 1][k - 1]);
      }
    }
  }

  int ans = 0;
  for(int j = 1; j <= m; ++j) {
    for(int k = 1; k <= m; ++k) {
      ans = max(ans, dp[n][j][k]);
    }
  }
  return ans;
}

int** create_matrix(int rows, int cols) {
  int** max = (int**)calloc(sizeof(int), rows);
  for (int i=0; i<rows; ++i) {
    max[i] = (int*)calloc(sizeof(int *),  cols);
  }
  return max;
}

void test() {
  int ret = 0;
  int rows = 4;
  int cols = 3;
  int gridSize = rows;
  int gridColSize = cols;
  int **grid = create_matrix(rows, cols);

  *(*(grid + 0) + 0) = 3;
  *(*(grid + 0) + 1) = 1;
  *(*(grid + 0) + 2) = 1;

  *(*(grid + 1) + 0) = 2;
  *(*(grid + 1) + 1) = 5;
  *(*(grid + 1) + 2) = 1;

  *(*(grid + 2) + 0) = 1;
  *(*(grid + 2) + 1) = 5;
  *(*(grid + 2) + 2) = 5;

  *(*(grid + 3) + 0) = 2;
  *(*(grid + 3) + 1) = 1;
  *(*(grid + 3) + 2) = 1;


  ret = cherryPickup(grid, gridSize, &gridColSize);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [test] L=146 :Output = 24
**/
