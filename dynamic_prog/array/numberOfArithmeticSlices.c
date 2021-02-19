/***
    LeetCode : https://leetcode.com/problems/arithmetic-slices/
    Arithmetic Slices
    A sequence of numbers is called arithmetic if it consists of at least
    three elements and if the difference between any two consecutive elements is the same.

    For example, these are arithmetic sequences:
    1, 3, 5, 7, 9
    7, 7, 7, 7
    3, -1, -5, -9

    The following sequence is not arithmetic.
    1, 1, 2, 5, 7

    A zero-indexed array A consisting of N numbers is given. A slice of that
    array is any pair of integers (P, Q) such that 0 <= P < Q < N.

    A slice (P, Q) of the array A is called arithmetic if the sequence:
    A[P], A[P + 1], ..., A[Q - 1], A[Q] is arithmetic. In particular, this means that P + 1 < Q.
    The function should return the number of arithmetic slices in the array A.

    Example:
    A = [1, 2, 3, 4]
    return: 3, for 3 arithmetic slices in A: [1, 2, 3], [2, 3, 4] and [1, 2, 3, 4] itself.
    Date : 18 Feb 2021
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

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

int numberOfArithmeticSlices2(int* A, int ASize) {
  int sum = 0;

  int *dp = (int *)malloc(ASize * sizeof(int));
  dp[ASize] = 0;
  for (int i = 2; i < ASize; i++) {
    if (A[i] - A[i - 1] == A[i - 1] - A[i - 2]) {
      dp[i] = 1 + dp[i - 1];
      sum += dp[i];
      debug ("i=%d A[i]=%d A[i-1]=%d, A[i-2]=%d sum=%d, dp=%d", i, A[i], A[i-1], A[i-2], sum, dp[i]);
    }
  }
  return sum;
}

/* Optimise Version */
int numberOfArithmeticSlices(int* A, int ASize) {
  int dp = 0;
  int sum = 0;

  for (int i = 2; i < ASize; i++) {
    if (A[i] - A[i - 1] == A[i - 1] - A[i - 2]) {
      dp = 1 + dp;
      sum += dp;
      debug ("i=%d A[i]=%d A[i-1]=%d, A[i-2]=%d sum=%d, dp=%d", i, A[i], A[i-1], A[i-2], sum, dp);
    } else
      dp = 0;
  }
  return sum;
}

int main () {
  int arr[] = {1,2,3,4};
  int sz = sizeof(arr) / sizeof(arr[0]);
  int op = numberOfArithmeticSlices2(arr, sz);
  debug ("op = %d ", op);

  return 0;
}

/**
   => ./a.out
   [numberOfArithmeticSlices] L=45 :i=2 A[i]=3 A[i-1]=2, A[i-2]=1 sum=1, dp=1
   [numberOfArithmeticSlices] L=45 :i=3 A[i]=4 A[i-1]=3, A[i-2]=2 sum=3, dp=2
   [main] L=56 :op = 3
**/
/**
   Complexity Analysis
    Time complexity : O(n)O(n)O(n). We traverse over the given AAA array with n
    elements once only.
    Space complexity : O(n)O(n)O(n). 1-D dpdpdp of size nnn is used.
 **/
