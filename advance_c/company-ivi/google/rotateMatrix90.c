/**
   Google: Mirror Image
   Given an image represented by an NxN matrix, where each pixel in the image is 4
   bytes, write a method to rotate the image by 90 degrees. Can you do this in place?

   2016-10-10 22:29:20
**/
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

#define r 3
#define c 3

int** create_matrix(int rows, int cols) {
  debug ("Rows = %d Cols = %d", rows, cols);
  int** max = (int**)calloc(sizeof(int *), rows);

  for (int i=0; i<rows; ++i) {
    max[i] = (int*)calloc(sizeof(int),  cols);
  }
  return max;
}

int rotateMatrixBy90Degree(int** matrix, int n) {
  int i, j, first, layer, offset, last, top;
  for(layer=0; layer<n/2; ++layer) {
    first = layer;
    last = n-1-layer;
    printf ("first = %d, last = %d, layer = %d\n", first, last, layer);
    for (i=first; i<last; ++i) {
      printf ("FIRST = %d i = %d\n", first, i);
      offset = i - first;
      // save top
      top = matrix[first][i];
      // left -> top
      matrix[first][i] = matrix[last-offset][first];
      // bottom -> left
      matrix[last-offset][first] = matrix[last][last-offset];
      // right -> bottom
      matrix[last][last-offset] = matrix[i][last];
      // top->right
      matrix[i][last]=top;
    } // 2nd for ends
  } // 1st for ends
  printf("Matrix After Rotating 90 degree:-\n");

  for (i=0; i<r; i++) {
    for (j=0; j<c; j++) {
      printf ("arr[%d][%d] = |%d| ",i,j, matrix[i][j]);
    }
    printf ("\n");
  }
    printf ("\n");
  //  printMatrix(matrix, n);
  return 0;
}

void freeMatrix(int **matrix ,int row) {
    for(int i=0; i<row; i++)
        free(matrix[i]);
    free(matrix);
}

void test() {
  int row, col, i, j, ret;
  row = r; col = c;

  int** grid = create_matrix(row, col);

  *(*(grid + 0) + 0) = 11110100;
  *(*(grid + 0) + 1) = 10101010;
  *(*(grid + 0) + 2) = 7;//00111010;

  *(*(grid + 1) + 0) = 11000000;
  *(*(grid + 1) + 1) = 10111010;
  *(*(grid + 1) + 2) = 8;//00100011;

  *(*(grid + 2) + 0) = 10010001;
  *(*(grid + 2) + 1) = 11100111;
  *(*(grid + 2) + 2) = 9;//00111010;

  i=2, j=2;
  debug ("arr[%d][%d] = |%d| ",i,j, grid[i][j]);
  debug("Input 2D Array: ");
  for (i=0; i<row; i++) {
    for (j=0; j<col; j++) {
      // grid[i][j] = i+j;
      printf ("arr[%d][%d] = |%d| ",i,j, grid[i][j]);
    }
    printf ("\n");
  }
  debug ("Rows = %d Cols = %d", i, j);
  // ret = sizeof (grid[0][c])/ sizeof (grid[0][0]);
  //printf ("sz of arr = %d\n", ret);

  debug("Output 2D Array: ");
  ret = rotateMatrixBy90Degree (grid, 3);
  for (i=0; i<row; i++) {
    for (j=0; j<col; j++) {
      grid[i][j] = i+j;
      printf ("arr[%d][%d] = |%d| ",i,j, grid[i][j]);
    }
    printf ("\n");
  }
}

int main () {
  test();
  return 0;
}
