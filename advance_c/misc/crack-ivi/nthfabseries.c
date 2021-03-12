/*
* Function to compute Nth fibonacci number
* https://www.geeksforgeeks.org/program-for-nth-fibonacci-number/
* https://leetcode.com/problems/fibonacci-number/
*/
#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */

int fib(int n) {
  int f = 0, g = 1;
  while(n--) {
    g += f;
    f = g - f;
  }
  return f;
}

int main () {
  int ret = 0;
  ret = fib (5999);
  printf ("\nret = %d \n", ret);
}
