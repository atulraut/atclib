/***
    Range Addition II

    You are given an m x n matrix M initialized with all 0's
    and an array of operations ops, where ops[i] = [ai, bi]
    means M[x][y] should be incremented by one for
    all 0 <= x < ai and 0 <= y < bi.

    Count and return the number of maximum integers in the
    matrix after performing all the operations.

    Input: m = 3, n = 3, ops = [[2,2],[3,3]]
    Output: 4
    Explanation: The maximum integer in M is 2, and there are
    four of it in M. So return 4.

    Input: m = 3, n = 3, ops = [[2,2],[3,3],[3,3],[3,3],[2,2],
    [3,3],[3,3],[3,3],[2,2],[3,3],[3,3],[3,3]]
    Output: 4

    Input: m = 3, n = 3, ops = []
    Output: 9

    Constraints:
    1 <= m, n <= 4 * 104
    0 <= ops.length <= 104
    ops[i].length == 2
    1 <= ai <= m
    1 <= bi <= n

    https://leetcode.com/problems/range-addition-ii/
    Date: 4 Sept 2021
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

int maxCount(int m, int n, int** ops, int opsSize, int* opsColSize) {
  int minRow = m;
  int minCol = n;
  for(int i = 0; i < opsSize; i++) {
    if(minRow > ops[i][0])
      minRow = ops[i][0];
    if(minCol > ops[i][1])
      minCol = ops[i][1];

    debug ("minRow=%d minCol=%d", minRow, minCol);
  }
  return(minRow * minCol);
}

int** get_matrix(int row, int col) {
  int **max = (int**)calloc(row, sizeof(int*));
  for (int i=0; i<row; ++i)
    max[i] = (int*)calloc(col, sizeof(int));

  return max;
}

int main (int argc, char **argv) {
  int ret = 0;
  int m = 3;
  int n = 3;

  int **ops = get_matrix(2, 2);
  *(*(ops + 0) + 0) = 2;
  *(*(ops + 0) + 1) = 2;
  *(*(ops + 1) + 0) = 3;
  *(*(ops + 1) + 1) = 3;

  int opsSize = 2;
  int opsColSize = 2;
  debug("opsSize = %d opsColSize = %d", opsSize, opsColSize);

  ret = maxCount(m, n, ops, opsSize, &opsColSize);
  debug("Output = %d", ret);

  return 0;
}

/**
   [main] L=84 :opsSize = 2 opsColSize = 2
   [maxCount] L=58 :minRow=2 minCol=2
   [maxCount] L=58 :minRow=2 minCol=2
   [main] L=87 :Output = 4
**/
