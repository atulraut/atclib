/***

    Extract n bits starting at position from msb to lsb

    Ask by matx

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Fri Oct  2 13:54:20 PDT 2026
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

uint32_t extract_bits(uint32_t value, int m, int n) {
  int width = n - m + 1;

  uint32_t mask = (1U << width) - 1;

  return (value >> m) & mask;
}

void test() {

  uint32_t x = 0x12345678;
  int p = 7;
  int n = 5;

  uint32_t ans = extract_bits(x, p, n);
  debug("Output = %d", ans);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   L=[43][5_2-extract-bits-msb_lsb.c]->[test] :| Output = 2386092
 **/
