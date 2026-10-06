/***
    Longest Turbulent Subarray

    Given an integer array arr, return the length of a
    maximum size turbulent subarray of arr.
    A subarray is turbulent if the comparison sign flips
    between each adjacent pair of elements in the subarray.

    More formally, a subarray [arr[i], arr[i + 1], ..., arr[j]]
    of arr is said to be turbulent if and only if:

    For i <= k < j:
    arr[k] > arr[k + 1] when k is odd, and
    arr[k] < arr[k + 1] when k is even.
    Or, for i <= k < j:
    arr[k] > arr[k + 1] when k is even, and
    arr[k] < arr[k + 1] when k is odd.

    Input: arr = [9,4,2,10,7,8,8,1,9]
    Output: 5
    Explanation: arr[1] > arr[2] < arr[3] > arr[4] < arr[5]
    Example 2:

    Input: arr = [4,8,12,16]
    Output: 2

    Input: arr = [100]
    Output: 1

    Constraints:
    1 <= arr.length <= 4 * 104
    0 <= arr[i] <= 109

    Date: 15 Sept 2021
    Fair Oaks, CA.
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

/*
  Simple State-Machine:
  0 (init) <--> 1 (up)
  0 (init) <--> 2 (down)
  1 (up) <--> 2 (down)
*/
int maxTurbulenceSize (int* arr, int arrSize) {
  int  i, cnt, max = 1;
  int  state = 0; // 0-init; 1-up; 2-down

  for (i = 1; i < arrSize; i++) {
    if (arr[i] > arr[i-1]) {
      if (state != 2) cnt = 1;
      cnt++;
      state = 1;
    } else if (arr[i] < arr[i-1]) {
      if (state != 1) cnt = 1;
      cnt++;
      state = 2;
    } else {
      state = 0;
      cnt = 0;
    }
    max = cnt > max ? cnt : max;
  }

  return max;
}

int main (int argc, char **argv) {
  int ret = 0;
  int arr[] = {4,8,12,16};

  ret = maxTurbulenceSize (arr, 4);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=85 :Output = 2
**/
