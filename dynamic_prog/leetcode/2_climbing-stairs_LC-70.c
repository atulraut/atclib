/***
    70. Climbing Stairs
    https://leetcode.com/problems/climbing-stairs/description/
    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Sat Sep 26 13:17:56 PDT 2026
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

int climbStairs(int n){
  if (n == 1) {
    return 1;
  }
  int* dp = (int *)calloc((n + 1), sizeof(int));
  dp[1] = 1;
  dp[2] = 2;
  for (int i = 3; i <= n; i++) {
    dp[i] = dp[i - 1] + dp[i - 2];
  }
  return dp[n];
}

void test() {
  int ret = 0;
  ret = climbStairs(3);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   L=[41][2_climbing-stairs_LC-70.c]->[test] :| Output = 3
**/
