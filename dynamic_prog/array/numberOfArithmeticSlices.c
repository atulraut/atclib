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
    if (A[i] - A[i - 1] == A[i - 1] - A[i - 2]) {  // Range {2 1 0} : {2-1} == {1-0}
      dp = 1 + dp;
      sum += dp;
      debug ("i=%d A[i]=%d A[i-1]=%d, A[i-2]=%d sum=%d, dp=%d", i, A[i], A[i-1], A[i-2], sum, dp);
    } else
      dp = 0;
  }
  return sum;
}

int main () {
  int arr1[] = {1,2,3,4};
  int arr[] = {1, 3, 5, 7, 9};
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
   Algo : Now, suppose we know the number of arithmetic slices in the range (0,i−1)
   constituted by the elements [a0,a1,a2,...a(i−1)], to be say x.
   If this range itself is an arithmetic slice, all the consecutive
   elements have the same difference(equal to say, a(i−1)−a(i−2).
   Now, adding a new element ai it to extend the range to (0,i) will
   constitute an arithmetic slice only if this new element satisfies ai−a(i−1)=a(i−1)−a(i−2).
   Thus, now, the addition of this new element, will lead to an addition of ap number of
   arithmetic slices to the ones obtained in the range (0,i−1).
   The new arithmetic slices will be the ones constituting the ranges (0,i),(1,i),...(i−2,i,
   which are a total of x+1 additional arithmetic slices.
   This is because, apart from the range (0,i) the rest of the ranges
   (1,i),(2,i),...(i−2,i)(1,i), (2,i),...(i-2,i) can be mapped to (0,i−1),(1,i−1),...(i−3,i−1),
   with count equal to x.
   Thus, in every call to slices, if the ithi^{th}ith element has the same common
   difference with the last element as the previous common difference, we can find the number
   of new arithmetic slices added by the use of this element, apapap and also update the
   sumsumsum to include this apapap into it, apart from the count obtained by the smaller ranges.
   But, if the new element doesn't have the same common difference, extra arithmetic slices can't
   be contributed by it and hence, no addition is done to sumsumsum for the current element.
   But, of course sumsumsum will be updated as per the count obtained from the smaller ranges.
   Dynamic Programming :
   In the last approach, we start with the full range (0,n−1) ,
   where nnn is the number of elements in the given A array.
   We can observe that the result for the range (0,i) only depends
   on the elements in the range (0,i)(0,i)(0,i) and not on any
   element beyond this range.
   Thus, we can make use of Dynamic Programming to solve the given problem.

   We can make use of a 1-D dpdpdp with number of elements equal to n.
   dp[i] is used to store the number of arithmetic slices possible
   in the range (k,i)(k,i)(k,i) and not in any range (k,j) such that j<i.
   Again, k refers to the minimum index possible such that (k,j) constitutes a valid Arithmetic Slice.

   Instead of going in the reverse order as in the recursive approach,
   we can start filling the dpdpdp in a forward manner.
   The intuition remains the same as in the last approach. For the ithi^{th} element
   being considered,
   we check if this element satsfies the common difference criteria with the
   previous element.
   If so, we know the number of new arithmetic slices added will be 1+dp[i−1]as
   discussed in the last approach.
   The sumsumsum is also updated by the same count to reflect the new arithmetic slices added.
   Complexity Analysis
   Time complexity : O(n). We traverse over the given AAA array with n
   elements once only.
   Space complexity : O(n). 1-D dpdpdp of size nnn is used.
**/
