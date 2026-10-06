/***
    Given an array of integers of size ‘n’.
    Our aim is to calculate the maximum sum of ‘k’
    consecutive elements in the array.

    Input  : arr[] = {100, 200, 300, 400}
    k = 2
    Output : 700

    Input  : arr[] = {1, 4, 2, 10, 23, 3, 1, 0, 20}
    k = 4
    Output : 39
    We get maximum sum by adding subarray {4, 2, 10, 23}
    of size 4.

    Input  : arr[] = {2, 3}
    k = 3
    Output : Invalid
    There is no subarray of size 3 as size of whole
    array is 2.

    Date: 04/17/2021 April
    San Diego, CA
*/
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

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

#define max(x, y) (((x) > (y)) ? x : y)

// Returns maximum sum in a subarray of size k.
int maxSum(int arr[], int n, int k) {
  // n must be greater
  if (n < k) {
    debug("Invalid, Exit!");
    return -1;
  }

  // Compute sum of first window of size k
  int max_sum = 0;
  for (int i = 0; i < k; i++)
    max_sum += arr[i];

  // Compute sums of remaining windows by
  // removing first element of previous
  // window and adding last element of
  // current window.
  int window_sum = max_sum;
  for (int i = k; i < n; i++) {
    window_sum += arr[i] - arr[i - k];
    max_sum = max(max_sum, window_sum);
  }

  return max_sum;
}

int main() {
  int arr[] = { 1, 4, 2, 10, 2, 3, 1, 0, 20 };
  int k = 4;
  int n = sizeof(arr) / sizeof(arr[0]);

  debug("Max Sum = %d", maxSum(arr, n, k));

  return 0;
}

/**
   => ./a.out
   [main] L=71 :Max Sum = 24
   Time Complexity is O(n).
**/
