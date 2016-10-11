#include <stdio.h>
#include <stdlib.h>

#define r 4
#define c 4
#define DEBUG 0

int **getDynamicArray(int, int);
int getDy(int ***, int, int);
void rotate90 ();

int main () {
  int row, col, i, j, ret;
  int **arr;  
  row = r; col = c;
  if(DEBUG)
    arr = getDynamicArray(row, col);
  else
    ret = getDy(&arr, row, col);

  for (i=0; i<row; i++) {
    for (j=0; j<col; j++) {
      arr[i][j] = i+j;
      printf ("arr[%d][%d] = |%d| ",i,j, arr[i][j]);
    }
    printf ("\n");
  }
  ret = sizeof (arr[0][4])/ sizeof (arr[0][0]);   
  printf ("sz of arr = %d\n", ret);
  ret = rotateMatrixBy90Degree (arr, 4);
  /*
  for (i=0; i<row; i++) {
    for (j=0; j<col; j++) {
      arr[i][j] = i+j;
      printf ("arr[%d][%d] = |%d| ",i,j, arr[i][j]);
    }
    printf ("\n");
  }
  */
  return 0;
}

int **getDynamicArray(int row, int col) {
  int i, j;
  int **ar;
  ar = (int **)malloc(row * sizeof(int *));
  for (i=0; i<row; i++)
    ar[i] = (int *)malloc(col * sizeof(int));
  printf ("In getDynamicArray \n");
  return ar;
}

int getDy(int ***ar, int row, int col) {
  int i, j;
  *ar = (int **)malloc(row * sizeof(int *));
  if (NULL == ar)
    return 1;
  for (i=0; i<row; i++)
    (*ar)[i] = (int *)malloc(col * sizeof(int));
  printf ("In getDy \n");
  if (NULL != ar)
    return 0;
  else
    return 1;
}

int rotateMatrixBy90Degree(int *matrix[], int n) {
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

