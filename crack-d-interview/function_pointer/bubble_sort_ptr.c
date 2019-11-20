/*
  bubble sort : Compair two consecutive element for every
  pass & if greater the first element than previous swap it.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int (*cmpfunc)(int *, int *); 
void (*swapfunc)(int *, int *); 

void bubblesort(int* A, int n, int (*cmpfunc)(int *a, int *b), void(*swapfunc)(int *a, int *b)) {
  int i, j; 
  for (i=0; i<n-1;i++) 
    for (j=0; j<n-i-1;j++) 
      if ( (*cmpfunc)(&A[j],&A[j+1]) > 0) 
	(*swapfunc)(&A[j],&A[j+1]); 
} 

int intcomp(int *i, int *j) { 
  return (*i-*j); 
} 
void intswap(int *i, int *j) { 
  int temp = *i; 
  *i = *j; 
  *j = temp; 
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
