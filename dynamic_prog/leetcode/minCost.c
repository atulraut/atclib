/***
    Medium: 256. Paint House
    https://leetcode.com/problems/paint-house/

    There is a row of n houses, where each house can be painted
    one of three colors: red, blue, or green. The cost of painting
    each house with a certain color is different. You have to
    paint all the houses such that no two adjacent houses have
    the same color.

    The cost of painting each house with a certain color is represented
    by an n x 3 cost matrix costs.

    For example, costs[0][0] is the cost of painting house 0 with the
    color red; costs[1][2] is the cost of painting house 1 with color
    green, and so on...

    Return the minimum cost to paint all houses.

    Input: costs = [[17,2,17],[16,16,5],[14,3,19]]
    Output: 10
    Explanation: Paint house 0 into blue, paint house 1 into green, paint
    house 2 into blue.
    Minimum cost: 2 + 5 + 3 = 10.

    Input: costs = [[7,6,2]]
    Output: 2

    Constraints:

    costs.length == n
    costs[i].length == 3
    1 <= n <= 100
    1 <= costs[i][j] <= 20

    Date: June 1, 2021.
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
#define ROW 4
#define COL 3

int min(int a, int b) {
  return a < b ? a : b;
}

int minCost(int** costs, int costsRowSize, int costsColSize) {
  if (costsRowSize == 0)
    return 0;

  int first = costs[0][0];
  int second = costs[0][1];
  int third = costs[0][2];

  debug(" first=%d second=%d third=%d", first, second, third);
  for (int i = 1; i < costsRowSize; i++) {
    int tmp1 = costs[i][0] + min(second, third);
    int tmp2 = costs[i][1] + min(first, third);
    int tmp3 = costs[i][2] + min(second, first);
    debug (" tmp1=%d, tmp2=%d, tmp3=%d", tmp1, tmp2, tmp3);
    first = tmp1;
    second = tmp2;
    third = tmp3;
  }
  return min(min(first, second), third);
}

int** create_matrix(int rows, int cols) {
  int** mat = (int**)malloc(rows * sizeof(int *));
  for (int i=0; i<rows; i++)
    mat[i] = (int *)malloc(cols * sizeof(int));

  return mat;
}

int main () {
  int ret = 0;
  //[[17, 2, 17], [8, 4, 10], [6, 3, 19], [4, 8, 12]]

  int** costs = create_matrix(4, 3);
  int costsRowSize = ROW;
  int costsColSize = COL;

  *(*(costs + 0) + 0) = 17;
  *(*(costs + 0) + 1) = 2;
  *(*(costs + 0) + 2) = 17;

  *(*(costs + 1) + 0) = 8;
  *(*(costs + 1) + 1) = 4;
  *(*(costs + 1) + 2) = 10;

  *(*(costs + 2) + 0) = 6;
  *(*(costs + 2) + 1) = 3;
  *(*(costs + 2) + 2) = 19;

  *(*(costs + 3) + 0) = 4;
  *(*(costs + 3) + 1) = 8;
  *(*(costs + 3) + 2) = 12;

  ret = minCost(costs, costsRowSize, costsColSize);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=108 :Output = 17
**/
