/***
    Medium: Set Matrix Zeroes
    Input: matrix = [[1,1,1],[1,0,1],[1,1,1]]
    Output: [[1,0,1],[0,0,0],[1,0,1]]

    Given an m x n integer matrix matrix, if an element is 0,
    set its entire row and column to 0's, and return the matrix.

    You must do it in place.
    Constraints:
    m == matrix.length
    n == matrix[0].length
    1 <= m, n <= 200
    -231 <= matrix[i][j] <= 231 - 1

    Follow up:

    A straightforward solution using O(mn) space is probably a bad idea.
    A simple improvement uses O(m + n) space, but still not the best solution.
    Could you devise a constant space solution?

    https://leetcode.com/problems/set-matrix-zeroes/
    Date: 15 August 2021.
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

void setZeroes(int** matrix, int matrixSize, int* matrixColSize) {
  int m = matrixSize;
  int n = *matrixColSize;
  int i, j;
  int *pmap = malloc(sizeof(int)*(m+n));
  memset(pmap, 0, sizeof(int)*(m+n));
  for(i = 0; i < m; i++) {
    /*if(pmap[i+n] == 1) {
      continue;
      }*/
    for(j = 0; j < n; j++) {
      /*if(pmap[j] == 1) {
	continue;
	}*/
      if(matrix[i][j] == 0) {
	pmap[j] = 1; /* clear column */
	pmap[i+n] = 1; /* clear row */
	continue;
      }
    }
  }
  for(i = 0; i < (m+n); i++) {
    printf("pmap[%d]=%d\n", i, pmap[i]);
    if(pmap[i] == 1) {
      if(i < n) {
	for(j = 0; j < m;j++) {
	  matrix[j][i] = 0;
	}
      } else {
	for(j = 0; j < n;j++) {
	  matrix[i-n][j] = 0;
	}
      }
    }
  }
  free(pmap);
}

int** create_matrix(int rows, int cols) {
  int** max = (int**)malloc(sizeof(int) * rows);
  for (int i=0; i<rows; ++i) {
    max[i] = (int*)malloc(sizeof(int *) * cols);
  }
  return max;
}

int main (int argc, char **argv) {
  int ret = 0;
  int rows = 3;
  int cols = 3;
  int matrixSize = rows;
  int matrixColSize = cols;

  int **grid = create_matrix(rows, cols);

  *(*(grid + 0) + 0) = 1;
  *(*(grid + 0) + 1) = 1;
  *(*(grid + 0) + 2) = 1;
  *(*(grid + 1) + 0) = 1;
  *(*(grid + 1) + 1) = 0;
  *(*(grid + 1) + 2) = 1;
  *(*(grid + 2) + 0) = 1;
  *(*(grid + 2) + 1) = 1;
  *(*(grid + 2) + 2) = 1;

  setZeroes(grid, matrixSize, &matrixColSize);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   pmap[0]=0
   pmap[1]=1
   pmap[2]=0
   pmap[3]=0
   pmap[4]=1
   pmap[5]=0
   [main] L=107 :Output = 0
**/
