/***
    LeetCode : Permutation Sequence :- Generate the permutation number k (current problem).
    The set [1, 2, 3, ..., n] contains a total of n! unique permutations.
    By listing and labeling all of the permutations in order,
    we get the following sequence for n = 3:
    "123"
    "132"
    "213"
    "231"
    "312"
    "321"

    Given n and k, return the kth permutation sequence.

    Example 1:
    Input: n = 3, k = 3
    Output: "213"

    Example 2:
    Input: n = 4, k = 9
    Output: "2314"

    Example 3:
    Input: n = 3, k = 1
    Output: "123"

    Constraints:
    1 <= n <= 9
    1 <= k <= n!

    Check LeetCode Logic :
    https://leetcode.com/problems/permutation-sequence/
*/
#include <stdio.h>
#include "../../../at_lib.h"

int factorial(int f) {
  int ret = 1;
  for (int i = 2; i <= f; i++) ret *= i;
  return ret;
}

char * getPermutation(int n, int k) {
  int tmp = 0, idx, i, j;
  char* ret = malloc((n + 1) * sizeof(char));
  int* used = calloc(n + 1, sizeof(int));
  k--;
  for (i = n - 1; i >= 1; i--) {
    idx = 0;
    for (j = 0; j <= k / factorial(i); j++) {
      idx++;
      while (used[idx]) idx++;
    }
    tmp = tmp * 10 + idx;
    used[idx] = 1;
    k %= factorial(i);
  }
  for (i = 1; i <= n; i++) if (!used[i]) {
      tmp = tmp * 10 + i;
      break;
    }
  sprintf(ret, "%d", tmp);
  return ret;
}

int main () {
  int n = 4;
  int k = 9;

  char *op =  getPermutation(n, k);

  debug (" op = %s ", op);

  return 0;
}

/**
   => ./a.out
   [main] L=71 : op = 2314
**/

/**
   Generate the permutation number k (current problem) :

 **/
