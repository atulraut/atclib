/*
  Selection sort : Select Index & compair it with element of indices. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void selection_sort (int arr[], int sz) {
  int i = 0, j = 0;
  int temp = 0;
  
  for (i=0; i<sz-1; i++) {
    for (j=i+1; j<sz-1; j++) {
      if (arr[i] > arr[j]) {
	temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
      }
    }
  }
}

int main () {
  int i = 0;
  int arr[] = {9, 4, 8, 3, 1};
  //int arr[] = {1, 2, 3, 4, 5};
  printf ("\n");
  int sz = sizeof(arr)/sizeof(arr[0]);
  for (i=0; i<sz-1; i++) {
    printf ("->[%d]", arr[i]);
  }
  printf ("\n");
  selection_sort (arr, sz);
  for (i=0; i<sz-1; i++) {
    printf ("->[%d]", arr[i]);
  }
  printf ("\n");
}
