/***

    Subarray Target Sum of Size K — Sliding Window in C

    Pattern: Fixed-size Sliding Window
    Time: O(n) | Space: O(1)
    
    Given an integer array arr[], a window size k, and a target,
    find a contiguous subarray of exactly K elements whose sum equals the target.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Fri Oct  9 10:23:58 PDT 2026
    Folsom, CA.
 */

/*----------------------------------- Header --------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h> // va_arg
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */

#define debug(str,args...) printf("L=[%d][%s]->[%s] :| "str"\n",__LINE__,__FILE__, __func__, ##args)

/**
   Q1 - Return count - count every matching window
   Q2 - Return Index - return the first matching index,.
**/
int subarrayTargetSum(int arr[], int n, int k, int target) {
  if (k <= 0 || k > n)
    return -1;

  int count = 0;
  int sum = 0;
  // Step 1: Calculate first window
  for(int i=0; i<k; ++i)
    sum += arr[i];

  if(sum == target)
    return 0;
  //    return 1; Q1
  
  // Step 2: Slide the window
  for (int i=k; i<n; i++) {
    sum += arr[i];      // Add incoming
    sum -= arr[i-k];    // Remove outgoing

    if (sum == target)
      return (i-k+1); // Q2
    //      count++; Q1
  }

  return count; // Q1
}

void test() {
  int arr[] = {2, 1, 5, 1, 3, 2};
  int n = sizeof(arr) / sizeof(arr[0]);
  int k = 3;
  int target = 9;

  int index = subarrayTargetSum(arr, n, k, target);

  if (index != -1) {
    debug("Found at index %d\n", index);

    debug("Subarray: ");
    for (int i = index; i < index + k; i++)
      debug("%d ", arr[i]);

  } else {
    debug("No matching subarray\n");
  }
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   L=[72][1_subarray_target_sum_size_k_2.c]->[test] :| Found at index 2

   L=[74][1_subarray_target_sum_size_k_2.c]->[test] :| Subarray: 
   L=[76][1_subarray_target_sum_size_k_2.c]->[test] :| 5 
   L=[76][1_subarray_target_sum_size_k_2.c]->[test] :| 1 
   L=[76][1_subarray_target_sum_size_k_2.c]->[test] :| 3 
**/
