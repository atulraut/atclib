/***
    https://leetcode.com/problems/search-a-2d-matrix/

    Search a 2D Matrix

    Write an efficient algorithm that searches for a value target
    in an m x n integer matrix matrix. This matrix has the following properties:

    Integers in each row are sorted from left to right.
    The first integer of each row is greater than the last integer of the previous row.

    Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
    Output: true

    Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
    Output: false

    Constraints:

    m == matrix.length
    n == matrix[i].length
    1 <= m, n <= 100
    -104 <= matrix[i][j], target <= 104

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date:
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

bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target) {
  int i ,j;
  i = 0;
  j = *matrixColSize * matrixSize - 1;

  while( i <= j ){
    int mid = (i + j) / 2;
    int row ,col;
    row = mid / * matrixColSize;
    col = mid % * matrixColSize;
    if(matrix[row][col] < target) i = mid + 1;
    else if(matrix[row][col] > target) j = mid - 1;
    else return true;
  }
  return false;
}

int** create_matrix(int rows, int cols) {
  int** max = (int**)calloc(sizeof(int *), rows);
  for (int i=0; i<rows; ++i) {
    max[i] = (int*)calloc(sizeof(int),  cols);
  }
  return max;
}

void test() {
  int ret = 0;
  int matrixSize = 4;
  int matrixColSize = 3;
  int target = 3;
  int** grid = create_matrix(matrixSize, matrixColSize);

  *(*(grid + 0) + 0) = 1;
  *(*(grid + 0) + 1) = 3;
  *(*(grid + 0) + 2) = 5;
  *(*(grid + 0) + 3) = 7;

  *(*(grid + 1) + 0) = 10;
  *(*(grid + 1) + 1) = 11;
  *(*(grid + 1) + 2) = 16;
  *(*(grid + 1) + 3) = 20;

  *(*(grid + 2) + 0) = 23;
  *(*(grid + 2) + 1) = 30;
  *(*(grid + 2) + 2) = 34;
  *(*(grid + 2) + 3) = 60;

  ret =  searchMatrix(grid, matrixSize, &matrixColSize,target);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [test] L=105 :Output = 1
**/
