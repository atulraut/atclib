/***
    https://leetcode.com/problems/smallest-integer-divisible-by-k/
    Smallest Integer Divisible by K

    Given a positive integer k, you need to find the length of the
    smallest positive integer n such that n is divisible by k, and
    n only contains the digit 1.

    Return the length of n. If there is no such n, return -1.
    Note: n may not fit in a 64-bit signed integer.

    Input: k = 1
    Output: 1
    Explanation: The smallest answer is n = 1, which has length 1.

    Input: k = 2
    Output: -1
    Explanation: There is no such positive integer n divisible by 2.

    Input: k = 3
    Output: 3
    Explanation: The smallest answer is n = 111, which has length 3.

    Constraints:
    1 <= k <= 105

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address smallestRepunitDivByK.c -lm

    Date: 12/29/2021
    Folsom, CA.
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


int smallestRepunitDivByK(int k){
  int remainder = 0;
  for (int length_N = 1; length_N <= k; length_N++) {
    remainder = (remainder * 10 + 1) % k;
    debug ("length_N=%d remainder=%d", length_N, remainder);
    if (remainder == 0)
      return length_N;
  }
  return -1;
}

int main (int argc, char **argv) {
  int ret = 0;
  int k = 3;
  ret = smallestRepunitDivByK(k);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [smallestRepunitDivByK] L=64 :length_N=1 remainder=1
   [smallestRepunitDivByK] L=64 :length_N=2 remainder=2
   [smallestRepunitDivByK] L=64 :length_N=3 remainder=0
   [main] L=75 :Output = 3
**/
