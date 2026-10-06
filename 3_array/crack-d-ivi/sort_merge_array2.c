/*
  Sort Two array & merge.
*/
#include <stdio.h>
#include <stdlib.h>

void merge(int ar1[], int ar2[], int m, int n)
{
  // Iterate through all elements of ar2[] starting from
  // the last element
  for (int i=n-1; i>=0; i--) {
    /* Find the smallest element greater than ar2[i]. Move all
       elements one position ahead till the smallest greater
       element is not found */
    int j, last = ar1[m-1];
    for (j=m-2; j >= 0 && ar1[j] > ar2[i]; j--)
      ar1[j+1] = ar1[j];
    // If there was a greater element
    if (j != m-2 || last > ar2[i]) {
      ar1[j+1] = ar2[i];
      ar2[i] = last;
    }
  }
}
int main () {
  int i;
  int arr1[] = {1, 2, 4, 5, 6};
  int arr2[] = {2, 3, 5, 7};
  int m = sizeof(arr1)/sizeof(arr1[0]);
  int n = sizeof(arr2)/sizeof(arr2[0]);
  merge(arr1, arr2, m, n);
	
  printf("After Merging First Array: \n");
  for (int i=0; i<m; i++)
    printf("--> %d \t", arr1[i]);
	
  printf("\nSecond Array: \n");
  for (int i=0; i<n; i++)
    printf("--> %d \t", arr2[i]);
  printf ("\n\n");
}

/**
   => ./a.out
   After Merging First Array:
   --> 1 	--> 2 	--> 2 	--> 3 	--> 4
   Second Array:
   --> 5 	--> 5 	--> 6 	--> 7
**/
