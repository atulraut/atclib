/***
    https://leetcode.com/problems/sum-of-digits-in-base-k/
    1837. Sum of Digits in Base K

    Given an integer n (in base 10) and a base k, return the
    sum of the digits of n after converting n from base 10 to base k.

    After converting, each digit should be interpreted as a base
    10 number, and the sum should be returned in base 10.

    Input: n = 34, k = 6
    Output: 9
    Explanation: 34 (base 10) expressed in base 6 is 54. 5 + 4 = 9.

    Input: n = 10, k = 10
    Output: 1
    Explanation: n is already in base 10. 1 + 0 = 1.

    Constraints:

    1 <= n <= 100
    2 <= k <= 10

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Jan, 02, 2022
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

int sumBase(int n, int k) {
  int sums_k_base = 0;

  while (n > 0){
    sums_k_base += (n % k);
    n /= k;
  }

  return sums_k_base;
}

int sumBase1(int n, int k) {
  int ans = 0;
  while (n > 0) {
    int r = n % k;
    n = n / k;
    ans += r;
  }
  return ans;
}

int main (int argc, char **argv) {
  int ret = 0;
  int n = 34;
  int k = 6;

  ret = sumBase(n, k);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=62 :Output = 9
**/
