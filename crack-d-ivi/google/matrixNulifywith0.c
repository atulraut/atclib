/*
*  Date - Oct-12, 2016
*  San Diego, CA
*/
#include <stdio.h>
#include <stdlib.h>
#include "../../at_lib.h"

#define row 4
#define col 4
#define DEBUG 0

void nullifyRow(int ar[][col], int sz);
void nullifyCol(int ar[][col], int sz);
void m_Display(int ar[][col]);

void nullifyCol(int ar[][col], int sz) {
  int i, j;
  debug(" NullifyCol sz = %d !", sz);
  for(i=0; i<row; i++)
    ar[i][sz] = 0;
}

void nullifyRow(int ar[][col], int sz) {
  int i, j;
  debug("NullifyRow sz = %d !", sz);
  for(i=0; i<row; i++)
    ar[sz][i] = 0;
}

void m_Display(int ar[][col]) {
  int i,j;
  for (i=0; i<row; i++) {
    for (j=0; j<col; j++) {
      debug("ar[%d][%d]=%d ",i,j, ar[i][j] );
    }
    printf ("\n");
  }
}

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
	debug("Check for 0-> arr[%d][%d]=%d ",i,j,arr[i][j]);
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

/**
   => ./a.out
   [m_Display] L=35 :ar[0][0]=0
   [m_Display] L=35 :ar[0][1]=1
   [m_Display] L=35 :ar[0][2]=2
   [m_Display] L=35 :ar[0][3]=3

   [m_Display] L=35 :ar[1][0]=1
   [m_Display] L=35 :ar[1][1]=2
   [m_Display] L=35 :ar[1][2]=3
   [m_Display] L=35 :ar[1][3]=4

   [m_Display] L=35 :ar[2][0]=2
   [m_Display] L=35 :ar[2][1]=3
   [m_Display] L=35 :ar[2][2]=4
   [m_Display] L=35 :ar[2][3]=5

   [m_Display] L=35 :ar[3][0]=3
   [m_Display] L=35 :ar[3][1]=4
   [m_Display] L=35 :ar[3][2]=5
   [m_Display] L=35 :ar[3][3]=6

   [main] L=55 :Check for 0-> arr[0][0]=0

   [nullifyRow] L=26 :NullifyRow sz = 0 !
   [nullifyCol] L=19 : NullifyCol sz = 0 !

   [m_Display] L=35 :ar[0][0]=0
   [m_Display] L=35 :ar[0][1]=0
   [m_Display] L=35 :ar[0][2]=0
   [m_Display] L=35 :ar[0][3]=0

   [m_Display] L=35 :ar[1][0]=0
   [m_Display] L=35 :ar[1][1]=2
   [m_Display] L=35 :ar[1][2]=3
   [m_Display] L=35 :ar[1][3]=4

   [m_Display] L=35 :ar[2][0]=0
   [m_Display] L=35 :ar[2][1]=3
   [m_Display] L=35 :ar[2][2]=4
   [m_Display] L=35 :ar[2][3]=5

   [m_Display] L=35 :ar[3][0]=0
   [m_Display] L=35 :ar[3][1]=4
   [m_Display] L=35 :ar[3][2]=5
   [m_Display] L=35 :ar[3][3]=6
**/
