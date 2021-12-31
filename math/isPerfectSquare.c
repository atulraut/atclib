/***
    https://leetcode.com/problems/valid-perfect-square/
    alid Perfect Square

    Given a positive integer num, write a function which returns
    True if num is a perfect square else False.

    Follow up: Do not use any built-in library function such as sqrt.

    Input: num = 16
    Output: true

    Input: num = 14
    Output: false

    Constraints:
    1 <= num <= 2^31 - 1

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address isPerfectSquare.c -lm

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
#define max(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a > _b ? _a : _b; })
#define min(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

bool isPerfectSquare(int num) {
  if (num < 2)
    return true;

  long x = num / 2;
  while (x * x > num) {
    x = (x + num / x) / 2;
  }
  return (x * x == num);
}

int main (int argc, char **argv) {
  int ret = 0;
  int num = 36;

  ret = isPerfectSquare(num);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=67 :Output = 1
 **/
