/***
    N-th Tribonacci Number

    The Tribonacci sequence Tn is defined as follows:

    T0 = 0, T1 = 1, T2 = 1, and Tn+3 = Tn + Tn+1 + Tn+2 for n >= 0.

    Given n, return the value of Tn.

    Input: n = 4
    Output: 4
    Explanation:
    T_3 = 0 + 1 + 1 = 2
    T_4 = 1 + 1 + 2 = 4

    Input: n = 25
    Output: 1389537

    https://leetcode.com/problems/n-th-tribonacci-number/
    Date: 24 Sept 2021
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

int tribonacci(int n) {
  //base cases
  if (n == 0)
    return 0;
  if (n == 1 || n == 2)
    return 1;

  /**
      dynamic approach: we fill first the small sub-problems
      and from them we will build up the big sub-problems
  **/
  int *t = malloc(sizeof(int) * (n + 1));
  t[0] = 0;
  t[1] = 1;
  t[2] = 1;

  for(int i = 3; i <= n; i++) {
    // Tn+3 = Tn + Tn+1 + Tn+2
    t[i] = t[i - 1] + t[i - 2] + t[i - 3];
  }
  //here is the solution!
  return t[n];
}

int main (int argc, char **argv) {
  int ret = 0;

  ret = tribonacci(25);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=65 :Output = 1389537
**/
