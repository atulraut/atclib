/***

    Variable-size sliding window

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Thu Oct  8 09:48:06 PDT 2026
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

void test() {

  int left = 0;

  for (int right = 0; right < n; right++) {

    // 1. EXPAND: add arr[right]

    while (/* window invalid */) {

      // 2. SHRINK: remove arr[left]
      left++;
    }

    // 3. UPDATE answer for valid window
  }
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**

 **/
