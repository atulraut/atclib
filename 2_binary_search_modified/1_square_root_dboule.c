/***
    square root for double or float using modified binary search.
    Explain here - 92126a@gmail.com
    https://chatgpt.com/c/6ac536bb-c424-83e8-af6e-75868c6504bc

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Tue Oct  6 12:38:28 2026
    Folsom, CA.
 */

/*----------------------------------- Header --------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h> // va_arg
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */

#define debug(str,args...) printf("L=[%d][%s]->[%s] :| "str"\n",__LINE__,__FILE__, __func__, ##args)


#include <stdio.h>
#include <math.h>

double binary_sqrt(double n)
{
  if (n < 0.0 || isnan(n))
    return NAN;

  if (n == 0.0 || isinf(n))
    return n;

  double left = 0.0;
  double right = (n < 1.0) ? 1.0 : n;

  // Relative precision; floating-point rounding also stops the loop.
  while (1) {
    double mid = left + (right - left) / 2.0;

    if (mid == left || mid == right)
      return mid;

    if (mid > n / mid)
      right = mid;
    else
      left = mid;

    if (right - left <= 1e-12 * right)
      return left + (right - left) / 2.0;
  }
}

int test(void) {
  debug("%.10f\n", binary_sqrt(20.0));
  return 0;
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   L=[60][1_square_root_dboule.c]->[test] :| 4.4721359550
 **/
