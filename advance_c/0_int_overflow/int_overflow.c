/***

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Wed 06 Nov 2024 08:18:50 PM PST
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

#define debug(str,args...) printf("L=[%d] [%s] :| "str"\n", __LINE__, __func__, ##args)

int arr[] = {0, 1, 2, 3, 4};
#define TOTAL_NUM_ELE (sizeof(arr)/sizeof(arr[0]))

void test2() {
  int d = -1, x;

  if (d <= TOTAL_NUM_ELE-2) {
    x = arr[d+1];
    debug ("x = %d", x);
  } else
    debug ("Nothing!");
}

void test() {
  if (-1 < (unsigned char) 1) {
    debug("-1 is Less than (unsigned char) 1: ANSI semantics");
  } else
    debug("-1 is NOT less than (unsigned char) 1: ANSI semantics");
}

int main (int argc, char **argv) {
  test2();
  return 0;
}

/**

 **/
