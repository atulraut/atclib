/***
    Find the value of ln(N!) using Recursion
    Source : Algo in C by Robert Sedgewick, Exercises 5.1

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address logN.c -lm

    Date: 26 June 2022
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

/**
    Method -1: Calculate n! first, then take its log value.

    Method -2: By using the property of log, i.e. take the
    sum of log values of n, n-1, n-2 …1.

    ln(n!) = ln(n*n-1*n-2*…..*2*1) = ln(n)+ln(n-1)+……+ln(2)+ln(1)

    Below is the implementation of the Method-2:
**/
long double fact(int n) {
  if (n == 1)
    return 0;
  return fact(n - 1) + log(n);
}

void test() {
  int n = 3;

  debug("Output: %Lf", fact(n));
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./main
   [test] L=56 :Output: 1.791759
**/
