/***
    Subset of problem :
    https://leetcode.com/problems/basic-calculator

    gcc -o main evalExpr.c -lm
    Date: 2021-09-11
    Fair Oaks, CA.
 */

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

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

#include <stdio.h>
#include <stdlib.h>

int evaluateExpr(char* str) {
  int operand = 0;
  int n = 0;
  for (int i = strlen(str) - 1; i >= 0; i--) {
    char ch = str[i];

    if (isdigit(ch)) {
      debug ("ch=%c ch=%d n=%d pow=%f", ch,(int) (ch - '0'), n, pow(10, n));
      // Forming the operand - in reverse order.
      operand = (int) pow(10, n) * (int) (ch - '0') + operand;
      n += 1;
      debug ("operand=%d n=%d", operand, n);
    }
    //debug ("ch = %c n=%d operand=%d", ch, n, operand);
  }
  return n;
}

int main (int argc, char **argv) {
  int ret = 0;
  char str[] = "(1+1)";
  ret = evaluateExpr(str);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [evaluateExpr] L=33 :ch=1 ch=1 n=0 pow=1.000000
   [evaluateExpr] L=37 :operand=1 n=1
   [evaluateExpr] L=33 :ch=1 ch=1 n=1 pow=10.000000
   [evaluateExpr] L=37 :operand=11 n=2
   [main] L=48 :Output = 2
   Caveat : This wont work with expression - "(1+10)"
**/
