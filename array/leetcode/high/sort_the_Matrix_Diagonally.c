/***
    https://leetcode.com/problems/sort-the-matrix-diagonally/
    Date : 2/2/2021
    San Diego, CA
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

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** get_matrix(int row, int col) {
  int** mat = (int **)malloc(sizeof(int) * row);
  for (int i=0; i<row; ++i) {
    mat[i] = (int *)malloc(sizeof(int) * col);
  }
  return mat;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int cmp(void *a, void *b){
  return *(int *)a-*(int *)b;
}

int** diagonalSort(int** mat, int matSize, int* matColSize, int* returnSize, int** returnColumnSizes) {
  int *dp = malloc(matSize*sizeof(int));
  int h=0, x, y;
  *returnColumnSizes=malloc(matSize*sizeof(int));
  debug ("Enter!");

  // row diagonal
  for(int i=0; i<matSize; i++) {
    (*returnColumnSizes)[i] = matColSize[0];
    x=i, y=0, h=0;
    while(x<matSize && y<matColSize[0])
      dp[h++]=mat[x++][y++];

    qsort(dp, h, sizeof(int), cmp);

    x=i, y=0, h=0;
    while(x<matSize && y<matColSize[0])
      mat[x++][y++]=dp[h++];
  }

  // col diagonal
  for(int i=0; i<matColSize[0]; i++) {
    x=0, y=i, h=0;
    while(x<matSize && y<matColSize[0])
      dp[h++]=mat[x++][y++];

    qsort(dp, h, sizeof(int), cmp);

    x=0, y=i, h=0;
    while(x<matSize && y<matColSize[0])
      mat[x++][y++]=dp[h++];
  }
  *returnSize=matSize;
  return mat;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** diagonalSort1__(int** mat, int matSize, int* matColSize, int* returnSize, int** returnColumnSizes) {
  int** grid = get_matrix(matSize, *returnSize);
  debug ("row  %d col = %d", matSize, *matColSize);

  // Print Normally
  for (int i=0; i<matSize; ++i) {
    for (int j=0; j<*matColSize; ++j) {
      printf ("mat[%d][%d] = %d \t", i, j, mat[i][j]);
    }
    printf ("\n");
  }

  // Print Diagonaly
  for (int i=0; i<matSize; ++i) {
    for (int j=0; j<*matColSize; ++j) {
      printf ("mat[%d][%d] = %d \t", i, j, mat[i][j]);
    }
    printf ("\n");
  }

  return grid;
}

void test() {
  int ret = 0;
  int matrixSize = 3;
  int matrixColSize = 4;
  int returnSize;
  int* returnColumnSizes;
  int** grid = get_matrix(matrixSize, matrixColSize);

  *(*(grid + 0) + 0) = 3;
  *(*(grid + 0) + 1) = 3;
  *(*(grid + 0) + 2) = 1;
  *(*(grid + 0) + 3) = 1;

  *(*(grid + 1) + 0) = 2;
  *(*(grid + 1) + 1) = 2;
  *(*(grid + 1) + 2) = 1;
  *(*(grid + 1) + 3) = 2;

  *(*(grid + 2) + 0) = 1;
  *(*(grid + 2) + 1) = 1;
  *(*(grid + 2) + 2) = 1;
  *(*(grid + 2) + 3) = 2;

  // Print Normally
  for (int i=0; i<matrixSize; ++i) {
    for (int j=0; j<matrixColSize; ++j) {
      printf ("grid[%d][%d] = %d \t", i, j, grid[i][j]);
    }
    printf ("\n");
  }
  grid = diagonalSort(grid, matrixSize, &matrixColSize, &returnSize,  &returnColumnSizes);
  debug("Output = %d", ret);

  debug ("row  %d col = %d", returnSize,  *returnColumnSizes);
  // Print Normally
  for (int i=0; i<returnSize; ++i) {
    for (int j=0; j<*returnColumnSizes; ++j) {
      printf ("mat[%d][%d] = %d \t", i, j, grid[i][j]);
    }
    printf ("\n");
  }
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   grid[0][0] = 3 	grid[0][1] = 3 	grid[0][2] = 1 	grid[0][3] = 1
   grid[1][0] = 2 	grid[1][1] = 2 	grid[1][2] = 1 	grid[1][3] = 2
   grid[2][0] = 1 	grid[2][1] = 1 	grid[2][2] = 1 	grid[2][3] = 2
   [diagonalSort] L=59 :Enter!
   [test] L=149 :Output = 0
   [test] L=151 :row  3 col = 4
   mat[0][0] = 1 	mat[0][1] = 1 	mat[0][2] = 1 	mat[0][3] = 1
   mat[1][0] = 1 	mat[1][1] = 2 	mat[1][2] = 2 	mat[1][3] = 2
   mat[2][0] = 1 	mat[2][1] = 2 	mat[2][2] = 3 	mat[2][3] = 3
**/
