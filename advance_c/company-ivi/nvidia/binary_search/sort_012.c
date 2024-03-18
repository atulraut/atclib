/***
    Sort an array of 0s, 1s and 2s | Dutch National Flag problem

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Sat 09 Mar 2024 07:13:20 PM PST
    Folsom, CA.
*/

/*----------------------------------- Header --------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */

#define debug(str,args...) printf("L=[%d] [%s] :| "str"\n", __LINE__, __func__, ##args)

void swap(int* a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

// Sort the input array, the array is assumed to
// have values in {0, 1, 2}
void sort012(int a[], int arr_size) {
  int lo = 0;
  int hi = arr_size - 1;
  int mid = 0;
  // Iterate till all the elements
  // are sorted
  while (mid <= hi) {
    switch (a[mid]) {
      // If the element is 0
    case 0:
      swap(&a[lo++], &a[mid++]);
      break;
      // If the element is 1
    case 1:
      mid++;
      break;
      // If the element is 2
    case 2:
      swap(&a[mid], &a[hi--]);
      break;
    }
  }
}

/* Utility function to print array arr[] */
void printArray(int arr[], int arr_size)
{
  int i;
  for (i = 0; i < arr_size; i++)
    printf("%d ", arr[i]);
}

void test() {
  int ret = 0;
  int arr[] = { 0, 1, 1, 0, 1, 2, 1, 2, 0, 0, 0, 1 };
  int arr_size = sizeof(arr) / sizeof(arr[0]);
  int i;

  sort012(arr, arr_size);

  printArray(arr, arr_size);

}

/* driver program to test */
int main() {
  test();
  return 0;
}

/**

 **/
