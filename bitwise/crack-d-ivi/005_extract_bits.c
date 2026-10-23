/***

    Extract n bits starting at position p from an integer.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Sat Sep 19 18:58:19 PDT 2026
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

uint32_t extract_bits(uint32_t x, int p, int n) {

  if (p < 0 || n <= 0 || p + n > 32)
    return 0;

  if (n == 32)
    return x;

  return (x >> p) & ((1U << n) - 1);
}

void test() {

  uint32_t x = 0x12345678;
  int p = 0;
  int n = 32;

  uint32_t ans = extract_bits(x, p, n);
  debug("Output = %d", ans);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   L=[42][5_extract_bits.c]->[test] :| Output = 305419896
 **/
