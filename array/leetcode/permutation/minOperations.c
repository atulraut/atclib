/***
    775: Medium: https://leetcode.com/problems/global-and-local-inversions/
    Global and Local Inversions

    We have some permutation A of [0, 1, ..., N - 1],
    where N is the length of A.
    The number of (global) inversions is the number of i < j with 0 <= i < j < N
    and A[i] > A[j].
    The number of local inversions is the number of i with 0 <= i < N
    and A[i] > A[i+1].
    Return true if and only if the number of global inversions is equal
    to the number of local inversions.

    Input: A = [1,0,2]
    Output: true
    Explanation: There is 1 global inversion, and 1 local inversion.

    Input: A = [1,2,0]
    Output: false
    Explanation: There are 2 global inversions, and 1 local inversion.

    Note:
    A will be a permutation of [0, 1, ..., A.length - 1].
    A will have length in range [1, 5000].
    The time limit for this problem has been reduced.

    Date : 4/6/21
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

int getMax(int a, int b) {
    return a>b?a:b;
}

/* Optimized version */
bool isIdealPermutation(int* A, int ASize) {
  int max = -1;
  int i;
  for (i = 0; i < ASize-2; i++) {
    max = getMax(max, A[i]);
    if(max > A[i+2]) {
      return false;
    }
  }
  return true;
}

/* Start with this & improve version above */
bool isIdealPermutation_brute_force(int* A, int ASize) {
  for (int i = 0; i < ASize; ++i)
    for (int j = i+2; j < ASize; ++j)
      if (A[i] > A[j])
	return false;
  return true;
}

int main () {
  int arr[] = {1, 0, 2};
  int sz = sizeof(arr)/sizeof(arr[0]);
  bool ret = isIdealPermutation(arr, sz);

  debug ("output = %d", ret);

  return 0;
}

/**
   => ./a.out
   [main] L=74 :output = 1
**/
/**
   Complexity Analysis
   Time Complexity: O(N)O(N)O(N), where NNN is the length of A.
   Space Complexity: O(1)O(1)O(1).
**/
