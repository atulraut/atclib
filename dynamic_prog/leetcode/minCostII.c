/***
    Hard: Paint House II

    There are a row of n houses, each house can be painted with one
    of the k colors.
    The cost of painting each house with a certain color is different.
    You have to paint all the houses such that no two adjacent houses
    have the same color.

    The cost of painting each house with a certain color is represented
    by an n x k cost matrix costs.

    For example, costs[0][0] is the cost of painting house 0 with color 0;
    costs[1][2] is the cost of painting house 1 with color 2, and so on...

    Return the minimum cost to paint all houses.

    Input: costs = [[1,5,3],[2,9,4]]
    Output: 5
    Explanation:
    Paint house 0 into color 0, paint house 1 into color 2. Minimum cost: 1 + 4 = 5;
    Or paint house 0 into color 2, paint house 1 into color 0. Minimum cost: 3 + 2 = 5.

    Input: costs = [[1,3],[2,4]]
    Output: 5

    Constraints:

    costs.length == n
    costs[i].length == k
    1 <= n <= 100
    1 <= k <= 20
    1 <= costs[i][j] <= 20

    https://leetcode.com/problems/paint-house-ii/

    Date: 17 August 2021
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

int minCostII(int** costs, int costsSize, int* costsColSize) {
  int dp_min = 0, dp_second_min = 0, dp_min_pos = 0;

  for (int i = 0; i < costsSize; ++i) {
    int min_val = INT_MAX, second_min = INT_MAX, min_pos = 0;

    for (int j = 0; j < *costsColSize; ++j) {
      int cur_val = costs[i][j] + (j == dp_min_pos ? dp_second_min : dp_min);

      if (min_val <= cur_val) {
	if (second_min > cur_val)
	  second_min = cur_val;
      } else {
	second_min = min_val;
	min_val = cur_val;
	min_pos = j;
      }
    }

    dp_min = min_val;
    dp_min_pos = min_pos;
    dp_second_min = second_min;
  }

  return dp_min;
}

int** create_matrix(int rows, int cols) {
  int **grid = (int **)calloc(rows, sizeof(int*));
  for (int i=0; i<rows; ++i)
    grid[i] = (int *)calloc(cols, sizeof(int));

  return grid;
}

int main (int argc, char **argv) {
  int ret = 0;
  int **grid = create_matrix(3, 3);

  *(*(grid + 0) + 0) = 1;
  *(*(grid + 0) + 1) = 5;
  *(*(grid + 0) + 2) = 3;

  *(*(grid + 1) + 0) = 2;
  *(*(grid + 1) + 1) = 9;
  *(*(grid + 1) + 2) = 4;

  int costsSize = 3;
  int costsColSize = 3;

  ret = minCostII(grid, costsSize, &costsColSize);

  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=106 :Output = 5
**/
