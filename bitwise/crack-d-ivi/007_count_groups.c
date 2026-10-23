/***

    count the number of set bits (1s) in the binary representation of a 128-bit integer.

    - Input: (2^{128}-1) → Output: 1 (the entire 128-bit number is one continuous sequence of 1s)
    - Input: 5 (101 in binary) → Output: 2
    So the task is actually to count consecutive groups of 1s, not individual set bits.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Fri Oct 23 16:26:57 PDT 2026
    #meta
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

int count_groups(unsigned __int128 n) {
  int count = 0;
  int prev = 0;

  while (n != 0) {
    int bit = n & 1;

    if (bit == 1 && prev == 0)
      count++;

    prev = bit;
    n >>= 1;
  }

  return count;
}

void test() {
  int ret = 0;
  unsigned __int128 n = 5;

  debug("%d\n", count_groups(n));
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   L=[52][007_count_groups.c]->[test] :| 2
**/
