/***
    https://leetcode.com/problems/arranging-coins/
    Arranging Coins

    You have n coins and you want to build a staircase
    with these coins. The staircase consists of k rows
    where the ith row has exactly i coins. The last row
    of the staircase may be incomplete.

    Given the integer n, return the number of complete
    rows of the staircase you will build.

    Input: n = 5
    Output: 2
    Explanation: Because the 3rd row is incomplete, we return 2.

    Input: n = 8
    Output: 3
    Explanation: Because the 4th row is incomplete, we return 3.

    Constraints:
    1 <= n <= 231 - 1

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address arrangeCoins.c -lm

    Date: 5 Nov 2021
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

/* Using Binary Search */
int arrangeCoins(int n) {
  long left = 0, right = n;
  long k, curr;
  while (left <= right) {
    k = left + (right - left) / 2;
    curr = k * (k + 1) / 2;

    if (curr == n)
      return (int)k;
    if (n < curr)
      right = k - 1;
    else
      left = k + 1;
  }
  return (int)right;
}

int main (int argc, char **argv) {
  int ret = 0;
  int n = 8;

  ret = arrangeCoins(n);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=79 :Output = 3
**/
