/***
    Add 3D array allocation routines.

    Date: 16 August 2021
    Fair Oaks, CA.
 */

#include <stdio.h>
#include <stdlib.h>

#define r 4
#define c 3
#define DEBUG 0

/***
 * allocate a 3D array
 */
int*** allocate3D(int l,int rows, int cols) {
  int ***arr3D;
  int i,j,k;

  arr3D = (int***)malloc(l * sizeof(int **));

  for(i=0; i<l; i++) {
    arr3D[i] = (int**)malloc(rows * sizeof(int*));

    for(j=0; j<rows; j++) {
      arr3D[i][j] = (int*)malloc(cols * sizeof(int));
    }
  }

  return arr3D;
}

//deallocate a 3D array
void deallocate3D(int arr3D,int l,int m) {
  int i,j;

  for(i=0; i<l; i++) {
    for(int j=0;j<m;j++) {
      free(arr3D[i][j]);
    }
    free(arr3D[i]);
  }
  free(arr3D);
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
