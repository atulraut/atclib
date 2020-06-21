/***
 * Author : Atul R. Raut
 * Date   : 27 Sept 2015
 * Place  : San Diego
 * Do Check : http://geeksquiz.com/binary-search/
 * Question: Search a given number in an array and return its * index using binary search tree.
 */

#include <stdio.h>
 
// A iterative binary search function. It returns location of x in
// given array arr[low..r] if present, otherwise -1
int binarySearch(int arr[], int low, int high, int key) {
  int mid = 0;
  while (low <= high) {
    printf ("low = %d mid = %d high = %d \n", low, mid, high);   
    mid = low + (high-low)/2;
    printf ("mid = %d \n", mid); 
    if (arr[mid] == key) 
        return mid;  // Check if key is present at mid
    if (arr[mid] < key) 
        low = mid + 1; // If key greater, ignore left half
    else 
        high = mid - 1; // If key is smaller, ignore right half
  }
  return -1; // if we reach here, then element was not present
}
 
int main(void) {
   int arr[] = {2, 3, 4, 10, 40, 89, 96};
   int high = sizeof(arr)/ sizeof(arr[0]);
//   printf ("sizeof-arr = %d, arr[0] = %d\n", sizeof(arr), sizeof(arr[0]));
   int key = 4;
   int result = binarySearch(arr, 0, high-1, key);
   (result == -1)? printf("Element is not present in array")
                 : printf("Element is present at index %d", result);
   return 0;
}
