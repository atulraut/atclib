
/***
    Date : 2/2/2021
    San Diego, CA
*/

#include <stdio.h>
#include "../../../at_lib.h"


/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** diagonalSort(int** mat1, int matSize, int* matColSize, int* returnSize, int** returnColumnSizes) {
  int i, j;

  static int mat[3][4] = {
    {3,3,1,1},
    {2,2,1,2},
    {1,1,1,2}
  };
  //  mat = arr[0][0];

  for (i = 2; i >= 0; --i) {
    for (j = 0; j < 4; j++)
      printf("[%s] --> %d\t", __func__, mat[i][j]);
    printf("\n");
  }
  return 0;

}

int (*generate())[4] {
  static int arr[3][4] = {
    {3,3,1,1},
    {2,2,1,2},
    {1,1,1,2}
  };
  return arr;
}


int **allocate_2D_array(int rows, int columns) {
  int k = 0;
  int **array = malloc(rows * sizeof (int *) );

  array[0] = malloc(columns * rows * sizeof (int) );
  for (k=1; k < rows; k++)
    {
      array[k] = array[0] + columns*k;
      bzero(array[k], columns * sizeof (int) );
    }

  bzero(array[0], columns * sizeof (int) );

  return array;
}

int main() {
  int i, j;
  int **ptr;
  int matSize = 3;
  int colSz   = 4;
  int *matColSize = &colSz;
  int returnSize;
  int* returnColumnSizes;
  //int (*mat1)[4] = generate();
  int **mat2 = allocate_2D_array(matSize, colSz);
  static int mat[3][4] = {
    {3,3,1,1},
    {2,2,1,2},
    {1,1,1,2}
  };
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 4; j++)
      printf("[%s] --> %d\t", __func__, mat[i][j]);
    printf("\n");
  }

  ptr = diagonalSort(mat2, matSize, matColSize, &returnSize, &returnColumnSizes);
  return 0;
}

/***
 */
