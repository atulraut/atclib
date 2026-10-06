/***
    Recursion Explain : Factorial Number & Recursion
    Ex 5.1 by Rober S. Page, Algo in C - 188
    Date: Sat Feb 12 10:01:30 PST 2022
    Folsom CA
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

/*----------------------------------- Micro --------------------------------------*/
#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)
#define atsizeof(object) (char *)(&object+1) - (char*)(&object)
#define arrsz(x)  (sizeof(x) / sizeof((x)[0]))
#define max(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a > _b ? _a : _b; })
#define min(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

int factorial_(int f) {
  int ret = 1;
  for (int i = 2; i <= f; i++) ret *= i;
  return ret;
}

int factorial(int N) {
  debug ("N = %d", N);
  if (N == 0)
    return 1;
  int temp = N * factorial(N-1);
  debug ("temp = %d", temp);
  return temp;
}

void test() {
  int ret = factorial(3);
  debug ("ret = %d", ret);
}

int main () {
  test2();
  return 0;
}

/*
  Approach 1: Factorial Number System:

  How to Construct the Permutation from its Factorial Representation

  Let us pick up N = 3N=3, which corresponds to the input
  array nums = [1, 2, 3], and construct its permutation
  number k = 3k=3. Since we number the permutations from 0 to N! - 1N!−1
  (and not from 1 to N!N! as in the problem description),
  for us that will be the permutation number k = 2k=2.

  Let us first construct the factorial representation of k = 2k=2:

  k = 2 = 1×2! + 0×1! +0×0! = (1,0,0)

  Algorithm:
    1] Generate input array nums of numbers from 1 to N.
    2] Compute all factorial bases from 00 to (N−1)!.
    3] Decrease kk by 1 to make it fit into (0, N!−1) interval.
    4] Compute factorial representation of k.
       Use factorial coefficients to construct the permutation.
    5] Return the permutation string.
*/

/**
   => ./a.out
   [factorial] L=69 :N = 3
   [factorial] L=69 :N = 2
   [factorial] L=69 :N = 1
   [factorial] L=69 :N = 0
   [factorial] L=73 :temp = 1
   [factorial] L=73 :temp = 2
   [factorial] L=73 :temp = 6
   [test2] L=109 :ret = 6
*/
