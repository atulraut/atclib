/*
  Rearrange an array such that every odd indexed element is
  greater than it previous
  Given an unsorted array arr of size N, rearrange the elements
  of array such that number at the odd index is greater than
  the number at the previous even index. The task is to complete
  the function formatArray() which will return formatted array.
  Input:
  The first line of input contains T, denoting the number of
  testcases. First line of every test case consists of N, denoting
  number of elements in an array. Second line of every testcase
  consists of elements in an array separated by space.
Output:
If the array formed is according to rules print 1, else 0.
  Date: 5/18/2020 Monday 12:00AM
*/
#include <stdio.h>
#include <stdlib.h>

void swap(int *i, int *j) {
  int temp = *i;
  *i = *j;
  *j = temp;
}

void rearrange(int arr[], int n)  {
  // Common code for odd and even lengths
  for (int i=0; i<n-1; i=i+2) {
      if (arr[i] > arr[i+1])
	swap(&arr[i], &arr[i+1]);
   }

  // If length is odd
  if (n & 1) {
      for (int i=n-1; i>0; i=i-2)
	if (arr[i] > arr[i-1])
	  swap(&arr[i], &arr[i-1]);
  }
}

/* Utility that prints out an array on a line */
void printArray(int arr[], int size) {
  for (int i=0; i < size; i++)
    printf("[%s]--> %d \t",__func__, arr[i]);

  printf("\n");
}

/* Driver function to test above functions */
int main() {
  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int n = sizeof(arr)/sizeof(arr[0]);
  printf("Before rearranging ::-->\n");
  printArray(arr, n);
  rearrange(arr, n);
  printf("After rearranging ::-->\n");
  printArray(arr, n);
  return 0;
}

/*
atul@Raigad:~/dev/c/atclib/gforg/array
=> ./a.out
Before rearranging ::-->
--> 1 	--> 2 	--> 3 	--> 4 	--> 5 	--> 6 	--> 7 	--> 8 	--> 9
After rearranging ::-->
--> 1 	--> 3 	--> 2 	--> 5 	--> 4 	--> 7 	--> 6 	--> 9 	--> 8
atul@Raigad:~/dev/c/atclib/gforg/array
=>

*/
