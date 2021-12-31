/***
    https://leetcode.com/problems/ugly-number/

    An ugly number is a positive integer whose prime factors
    are limited to 2, 3, and 5.

    Given an integer n, return true if n is an ugly number.

    Input: n = 6
    Output: true
    Explanation: 6 = 2 × 3

    Input: n = 1
    Output: true
    Explanation: 1 has no prime factors, therefore all of its prime factors
    are limited to 2, 3, and 5.

    Input: n = 14
    Output: false
    Explanation: 14 is not ugly since it includes the prime factor 7.
    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address isUgly.c -lm

    Date: 12/30/2021
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
#define max(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a > _b ? _a : _b; })
#define min(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

bool isUgly(int n) {
  if(n == 1) {
    return true;
  }
  if(n <=0) {
    return false;
  }
  while(n % 2 == 0) {
    n /= 2;
  }
  while(n % 3 == 0) {
    n /= 3;
  }
  while(n % 5 == 0) {
    n /= 5;
  }
  return n == 1;
}

int main (int argc, char **argv) {
  int ret = 0;
  int n = 14;

  ret = isUgly(n);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=77 :Output = 0
**/
