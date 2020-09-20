#include <stdio.h>
#include <stdlib.h>

#define r 4
#define c 3
#define DEBUG 0

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
  return 0;
}
