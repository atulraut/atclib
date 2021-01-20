/*
*  Date - Oct-12, 2016
*  San Diego, CA
*/
#include <stdio.h>
#include <stdlib.h>

#define row 4
#define col 4
#define DEBUG 0

void nullifyRow(int ar[][col], int sz);
void nullifyCol(int ar[][col], int sz);
void m_Display(int ar[][col]);
 
int main() {
  int i,j;
  int arr[row][col];
  int rww[row] = {0};
  int cll[col] = {0};
  for (i=0; i<row; i++) {
    for (j=0; j<col; j++) {
      arr[i][j] = i+j;
    }
  }
  m_Display(arr);
  for (i=0; i<row; i++) {
    for (j=0; j<col; j++) {
      if(0 == arr[i][j]) {
	printf("Check for 0-> arr[%d][%d]=%d ",i,j,arr[i][j]);
	rww[i] = 1;
	cll[j] = 1;
      }
    }
  }
  for (i=0; i<row; i++) {
    if(rww[i] == 1)
      nullifyRow(arr, i);
  }
  for (j=0; j<row; j++) {
    if(cll[j] == 1)
      nullifyCol(arr, j);
  }
  m_Display(arr);
  return 0;
}

void nullifyCol(int ar[][col], int sz) {
  int i, j;
  printf("nullifyCol sz = %d !\n", sz);
  for(i=0; i<row; i++)
    ar[i][sz] = 0;
}

void nullifyRow(int ar[][col], int sz) {
  int i, j;
  printf("\nnullifyRow sz = %d !\n", sz);
  for(i=0; i<row; i++)
    ar[sz][i] = 0;
}

void m_Display(int ar[][col]) {
  int i,j;
  for (i=0; i<row; i++) {
    for (j=0; j<col; j++) {
      printf("ar[%d][%d]=%d ",i,j, ar[i][j] );
    }
    printf ("\n");
  }
}
