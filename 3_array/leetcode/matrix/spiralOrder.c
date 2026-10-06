/***
    Given an m x n matrix, return all elements of the
    matrix in spiral order.

    Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
    Output: [1,2,3,6,9,8,7,4,5]

    Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
    Output: [1,2,3,4,8,12,11,10,9,5,6,7]

    Constraints:

    m == matrix.length
    n == matrix[i].length
    1 <= m, n <= 10
    -100 <= matrix[i][j] <= 100

    https://leetcode.com/problems/spiral-matrix/

    Date: 16 Sept 2021
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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize) {
  int * result,pt=0;
  result = (int*) malloc(sizeof(int) * matrixSize * *matrixColSize);
  int up = 0, down = matrixSize-1, left = 0, right = *matrixColSize-1;
  while((up <= down) || (left <= right)) {
    if (up <= down) {
      for (int i = left ; i <= right ; i++)
	result[pt++] = matrix[up][i];
      up++;
    }
    if (left <= right) {
      for (int i = up ; i <= down ; i++)
	result[pt++] = matrix[i][right];
      right--;
    }
    if (up <= down) {
      for (int i = right ; i >= left ; i--)
	result[pt++] = matrix[down][i];
      down--;
    }
    if (left <= right) {
      for (int i = down ; i >= up ; i--)
	result[pt++] = matrix[i][left];
      left++;
    }
  }
  *returnSize = pt;
  return result;
}

int** create_matrix(int rows, int cols) {
  int** max = (int**)malloc(sizeof(int) * rows);
  for (int i=0; i<rows; ++i) {
    max[i] = (int*)malloc(sizeof(int *) * cols);
  }
  return max;
}

int main (int argc, char **argv) {
  int* ret;
  int matrixSize = 3;
  int matrixColSize = 3;
  int returnSize;

  int **grid = create_matrix(matrixSize,  matrixColSize);

  *(*(grid + 0) + 0) = 1;
  *(*(grid + 0) + 1) = 2;
  *(*(grid + 0) + 2) = 3;
  *(*(grid + 1) + 0) = 4;
  *(*(grid + 1) + 1) = 5;
  *(*(grid + 1) + 2) = 6;
  *(*(grid + 2) + 0) = 7;
  *(*(grid + 2) + 1) = 8;
  *(*(grid + 2) + 2) = 9;

  ret = spiralOrder(grid, matrixSize, &matrixColSize, &returnSize);
  for (int i=0; i<returnSize; ++i)
    debug("Output = %d", ret[i]);

  return 0;
}

/**
   => ./a.out
   [main] L=98 :Output = 1
   [main] L=98 :Output = 2
   [main] L=98 :Output = 3
   [main] L=98 :Output = 6
   [main] L=98 :Output = 9
   [main] L=98 :Output = 8
   [main] L=98 :Output = 7
   [main] L=98 :Output = 4
   [main] L=98 :Output = 5
**/
