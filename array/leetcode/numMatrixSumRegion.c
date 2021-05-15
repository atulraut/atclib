/***
    LeetCode: Medium: 304. Range Sum Query 2D - Immutable
    https://leetcode.com/problems/range-sum-query-2d-immutable/

    Given a 2D matrix matrix, handle multiple queries of the following type:

    Calculate the sum of the elements of matrix inside the rectangle
    defined by its upper left corner (row1, col1) and lower right corner (row2, col2).

    Implement the NumMatrix class:

    NumMatrix(int[][] matrix) Initializes the object with the integer matrix matrix.
    int sumRegion(int row1, int col1, int row2, int col2) Returns the sum of the
    elements of matrix inside the rectangle defined by its upper left corner
    (row1, col1) and lower right corner (row2, col2).

    Input
    ["NumMatrix", "sumRegion", "sumRegion", "sumRegion"]
    [[[[3, 0, 1, 4, 2], [5, 6, 3, 2, 1], [1, 2, 0, 1, 5], [4, 1, 0, 1, 7],
    [1, 0, 3, 0, 5]]], [2, 1, 4, 3], [1, 1, 2, 2], [1, 2, 2, 4]]
    Output
    [null, 8, 11, 12]

    Explanation
    NumMatrix numMatrix = new NumMatrix([[3, 0, 1, 4, 2], [5, 6, 3, 2, 1],
    [1, 2, 0, 1, 5], [4, 1, 0, 1, 7], [1, 0, 3, 0, 5]]);
    numMatrix.sumRegion(2, 1, 4, 3); // return 8 (i.e sum of the red rectangle)
    numMatrix.sumRegion(1, 1, 2, 2); // return 11 (i.e sum of the green rectangle)
    numMatrix.sumRegion(1, 2, 2, 4); // return 12 (i.e sum of the blue rectangle)

    Constraints:
    m == matrix.length
    n == matrix[i].length
    1 <= m, n <= 200
    -105 <= matrix[i][j] <= 105
    0 <= row1 <= row2 < m
    0 <= col1 <= col2 < n
    At most 104 calls will be made to sumRegion.

    Date: 12 May 2021
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

#define ROWS 5
#define COLS 5

typedef struct  {
  int *sum;
  int rlen;
  int clen;
} NumMatrix;

/** Initialize your data structure here. */
NumMatrix* numMatrixCreate(int** m, int matrixSize, int* matrixColSize){
  int rlen = matrixSize;
  int clen = matrixColSize[0];
  NumMatrix* array = (NumMatrix*)malloc(1*sizeof(NumMatrix));
  array->rlen = rlen;
  array->clen = clen;
  array->sum = (int*) calloc (rlen*clen,sizeof(int));

  if(rlen==0||clen==0)
    return array;

  //first row
  array->sum[0] = m[0][0];
  for(int j=1;j<clen; j++)
    array->sum[j] = array->sum[j-1] + m[0][j];

  debug("Row4: = %d", array->sum[4]);

  for(int i=1; i<rlen; i++){
    //first column
    int tempsum = m[i][0];
    debug("tempsum=%d i*clen=%d, sum=%d", tempsum, (i*clen), array->sum[(i-1) * clen]);
    array->sum[i*clen] = array->sum[(i-1) * clen] + m[i][0];
    debug("arry->sum = %d", array->sum[i*clen]);
    for(int j=1; j<clen; j++){
      tempsum += m[i][j];
      array->sum[i*clen+j] = array->sum[(i-1) * clen+j] + tempsum;
    }
  }

  return array;
}

int numMatrixSumRegion(NumMatrix* numMatrix, int row1, int col1, int row2, int col2) {
  int clen = numMatrix->clen;

  int a = numMatrix->sum[row2 * clen+col2];
  int b = (col1 == 0) ? 0 : numMatrix->sum[row2 * clen+(col1-1)];
  int c = (row1 == 0) ? 0 : numMatrix->sum[(row1-1) * clen+col2];
  int d = (row1 == 0 || col1 == 0) ? 0 : numMatrix->sum[(row1-1) * clen+(col1-1)];

  return a-b-c+d;
}

/** Deallocates memory previously allocated for the data structure. */
void numMatrixFree(NumMatrix* numMatrix) {
  free(numMatrix->sum);
  free(numMatrix);
}

int** create_matrix(int rows, int cols) {
  int** mat = (int**) malloc(rows * sizeof(int*));
  int i;
  for (i = 0; i < rows; i++)
    mat[i] = (int*)malloc(cols * sizeof(int));
  return mat;
}

int main () {
  int ret = 0;
  int matrixSize = ROWS;
  int matrixColSize = COLS;

  int **obstacleGrid = create_matrix(ROWS, COLS);

  int gridSize = ROWS;
  int gridColSize = COLS;

  //*(*(arr+i)+j)
  //Ex-1: Input: grid = [[1,3,1],[1,5,1],[4,2,1]]
   *(*(obstacleGrid + 0) + 0) = 3;
   *(*(obstacleGrid + 0) + 1) = 0;
   *(*(obstacleGrid + 0) + 2) = 1;
   *(*(obstacleGrid + 0) + 3) = 4;
   *(*(obstacleGrid + 0) + 4) = 2;

   *(*(obstacleGrid + 1) + 0) = 5;
   *(*(obstacleGrid + 1) + 1) = 6;
   *(*(obstacleGrid + 1) + 2) = 3;
   *(*(obstacleGrid + 1) + 3) = 2;
   *(*(obstacleGrid + 1) + 4) = 1;

   *(*(obstacleGrid + 2) + 0) = 1;
   *(*(obstacleGrid + 2) + 1) = 2;
   *(*(obstacleGrid + 2) + 2) = 0;
   *(*(obstacleGrid + 2) + 3) = 1;
   *(*(obstacleGrid + 2) + 4) = 5;

   *(*(obstacleGrid + 3) + 0) = 4;
   *(*(obstacleGrid + 3) + 1) = 1;
   *(*(obstacleGrid + 3) + 2) = 0;
   *(*(obstacleGrid + 3) + 3) = 1;
   *(*(obstacleGrid + 3) + 4) = 5;

   *(*(obstacleGrid + 4) + 0) = 1;
   *(*(obstacleGrid + 4) + 1) = 0;
   *(*(obstacleGrid + 4) + 2) = 3;
   *(*(obstacleGrid + 4) + 3) = 0;
   *(*(obstacleGrid + 4) + 4) = 5;

  NumMatrix* mat = numMatrixCreate(obstacleGrid, matrixSize, &matrixColSize);
  int row1 = 2;
  int col1 = 1;
  int row2 = 4;
  int col2 = 3;
  ret = numMatrixSumRegion(mat, row1, col1, row2, col2);

  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=170 :Output = 8
**/
