/***

    gcc -o main evalExpr.c -lm
    Date:
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
      // Forming the operand - in reverse order.
      operand = (int) pow(10, n) * (int) (ch - '0') + operand;
      n += 1;

    }
    debug ("ch = %c n=%d operand=%d", ch, n, operand);
  }
}

int main (int argc, char **argv) {
  int ret = 0;
  char str[] = "(1+1)";
  evaluateExpr(str);
  debug("Output = %d", ret);
  return 0;
}

/**

 **/
