#include <stdio.h>
#include <stdlib.h>

/* O(n): Max From Right Method */
void find_leader_in_array (int arr[], int n) {
  int mfr = arr[n-1];
  printf ("Lieader Is = %d \n", mfr);
  for(int i=n-2; i>=0; i--) {
    if(arr[i] > mfr) {
      printf ("Lieader Is = %d \n", arr[i]);
      mfr = arr[i];
    }
  }
}

/* O(n2) */
void simple_method(int *arr, int n) {
  int i, j;
  for (i=0; i<n; i++) {
    for(j=i+1; j<n; j++) {
      if(arr[j] >= arr[i]) {
	break;
      }
    }
    if (j == n)
      printf ("Leader Is = %d \n", arr[i]);
  }
}

int main() {
  int arr[] = {15,  16, 3, 2, 6, 1, 4};
  int sz = sizeof(arr) / sizeof(arr[0]);
  printf ("sz = %d \n", sz);
  find_leader_in_array(arr, sz);
  simple_method(arr, sz);
  return 0;
}
