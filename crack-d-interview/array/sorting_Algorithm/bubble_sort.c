/*
  bubble sort : Compair two consecutive element for every
  pass & if greater the first element than previous swap it.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bubble_sort (int arr[], int sz) {
  int i = 0, j = 0;
  int temp = 0;
  int flag = 0; // if sorted array dont do computing.
  
  for (i=0; i<sz-1; i++) {
    flag = 0;
    for (j=0; j<sz-1; j++) {
      printf ("ATUL \t");
      if (arr[j] > arr[j+1]) {
	flag = 1;
	temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
      }
    }
    if (0 == flag)
      break;
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
  bubble_sort (arr, sz);
  for (i=0; i<sz-1; i++) {
    printf ("->[%d]", arr[i]);
  }
  printf ("\n");
}
