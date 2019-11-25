/*
  bubble sort : Compair two consecutive element for every
  pass & if greater the first element than previous swap it.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int (*cmpfunc)(int*, int, int);
void (*swapfunc)(int *, int, int);

void bubblesort(void* A, int n, int (*cmpfunc)(int *a, int b, int c), void(*swapfunc)(int *a, int b, int c)) {
  int i, j;
  for (i=0; i<n-1;i++)
    for (j=0; j<n-i-1;j++)
      if ( (*cmpfunc)(A,j,j+1) > 0)
	(*swapfunc)(A,j,j+1);
}

int intcomp(int A[],int i, int j) {
  return (A[i]-A[j]);
}
void intswap(int A[], int i, int j) {
  int temp = A[i];
  A[i] = A[j];
  A[j] = temp;
}

int main () {
  int i = 0;
  int arr[] = {9, 4, 8, 3, 1};
  int sz = sizeof(arr)/sizeof(arr[0]);
  for (i=0; i<sz; i++) {
    printf ("->[%d]", arr[i]);
  }
  printf ("\n");
  bubblesort(arr,5, intcomp, intswap);
  for (i=0; i<sz; i++) {
    printf ("->[%d]", arr[i]);
  }
  printf ("\n");
}
