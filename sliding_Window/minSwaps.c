/***
    Minimum Swaps to Group All 1's Together
    Given a binary array data, return the minimum number of swaps
    required to group all 1’s present in the array together in any
    place in the array.

    Input: data = [1,0,1,0,1]
    Output: 1
    Explanation:
    There are 3 ways to group all 1's together:
    [1,1,1,0,0] using 1 swap.
    [0,1,1,1,0] using 2 swaps.
    [0,0,1,1,1] using 1 swap.
    The minimum is 1.

    Input: data = [0,0,0,1,0]
    Output: 0
    Explanation:
    Since there is only one 1 in the array, no swaps needed.

    Input: data = [1,0,1,0,1,0,0,1,1,0,1]
    Output: 3
    Explanation:
    One possible solution that uses 3 swaps is [0,0,0,0,0,1,1,1,1,1,1].

    Input: data = [1,0,1,0,1,0,1,1,1,0,1,0,0,1,1,1,0,0,1,1,1,0,1,0,1,1,0,0,0,1,1,1,1,0,0,1]
    Output: 8
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

int minSwaps(int* data, int dataSize) {
  int numberOfOnes = 0;

  // find total number of all 1's in the array
  for (int i = 0; i < dataSize; i++) {
    if (data[i] == 1)
      numberOfOnes++;
  }

  // length of subarray to check for
  int x = numberOfOnes;

  int count_ones = 0, maxOnes;

  // Find 1's for first subarray of length x
  for(int i = 0; i < x; i++){
    if(data[i] == 1)
      count_ones++;
  }

  maxOnes = count_ones;

  // using sliding window technique to find
  // max number of ones in subarray of length x
  for (int i = 1; i <= dataSize-x; i++) {

    // first remove leading element and check
    // if it is equal to 1 then decreament the
    // value of count_ones by 1
    if (data[i-1] == 1)
      count_ones--;

    // Now add trailing element and check
    // if it is equal to 1 Then increment
    // the value of count_ones by 1
    if(data[i+x-1] == 1)
      count_ones++;

    if (maxOnes < count_ones)
      maxOnes = count_ones;
  }

  // calculate number of zeros in subarray
  // of length x with maximum number of 1's
  int numberOfZeroes = x - maxOnes;

  return numberOfZeroes;
}

int main () {
  int arr[] = {1, 0, 1, 0, 1};
  int sz = sizeof(arr) / sizeof(arr[0]);
  int result = minSwaps(arr, sz);

  debug("Result = %d", result);

  return 0;
}

/**
   => ./a.out
   [main] L=96 :Result = 1
**/
