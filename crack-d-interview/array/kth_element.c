/* 
K’th Smallest/Largest Element in Unsorted Array | Set 1
*/
#include <stdio.h>
#include <string.h>

void bubble_sort (int arr[], int sz) {
  int i = 0, j = 0;
  int temp = 0;
  int flag = 0; // if sorted array dont do computing.
  printf ("bubble sorted array /n");
  for (i=0; i<sz; i++) {
    flag = 0;
    for (j=0; j<sz; j++) {
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
  for (i=0; i<n; i++) {
      printf ("-->[%d]", arr[i]);
  }
  printf ("\n");
}

// Function to return k'th smallest element in a given array
int kthSmallest(int arr[], int n, int k) {
    int i = 0;
    // Sort the given array
    bubble_sort(arr, n-1);
    
    // Return k'th element in the sorted array
    return arr[k-1];
}
 
int main() {
    int arr[] = {12, 3, 5, 7, 19};
    int n = sizeof(arr)/sizeof(arr[0]), k = 2;
    printf ("K'th smallest element is --> [%d] \n", kthSmallest(arr, n, k));
    return 0;
}
