/*
 Write an algorithm such that if an element in an MxN matrix is 0,
 its entire row and column is set to 0.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void setZeros(int matrix[][4], int ro, int col) {
  int *row = (int *)malloc(ro * sizeof(int));
  int *column = (int *)malloc(col * sizeof(int));

  // Store the row and column index with value 0
  for (int i = 0; i <ro; i++) {
    for (int j = 0; j <col;j++) {
      if (matrix[i][j] == 0) {
	printf ("Set: i = %d j = %d \n", i, j);
	row[i] = 1;
	column[j] = 1;
      }
    }
  }
  printf("\nStart Filling \n");
  // Set arr[i][j] to 0 if either row i or column j has a 0
  for (int i = 0; i < ro; i++) {
    for (int j = 0; j < col; j++) {
      if ((row[i] == 1 || column[j] == 1)) {
	printf ("Get: i = %d j = %d \n", i, j);
	matrix[i][j] = 0;
      }
    }
    printf("\n");
  }
  free(row);
  free(column);
}

int main() {
  int i, j;
  int sz = 4;
  int arr[][4] = {
    {9,0,3,4},
    {5,6,7,8},
    {9,10,0,12},
    {13,14,15,16},
  };
  for(i=0; i<sz; i++) {
    for(j=0; j<sz; j++) {
      printf("--> %d \t", arr[i][j]);
    }
    printf("\n");
  }
  printf ("Start Filling 0 \n");

  setZeros(arr, 4,4);
  for(i=0; i<sz; i++) {
    for(j=0; j<sz; j++) {
      printf("--> %d \t", arr[i][j]);
    }
    printf("\n");
  }
  printf ("End\n");
}
