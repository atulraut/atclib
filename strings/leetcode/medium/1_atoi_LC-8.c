/***

    8. String to Integer (atoi)

    https://leetcode.com/problems/string-to-integer-atoi/description/

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Sat Sep 26 16:02:35 PDT 2026
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

int myAtoi(char* s) {
  int i = 0;
  int sign = 1;
  int result = 0;

  // 1. Skip leading spaces
  while (s[i] == ' ') {
    i++;
  }

  // 2. Check sign
  if (s[i] == '-') {
    sign = -1;
    i++;
  } else if (s[i] == '+') {
    i++;
  }

  // 3. Convert digits
  while (s[i] >= '0' && s[i] <= '9') {
    int digit = s[i] - '0';

    // Check overflow before multiplying by 10
    if (result > INT_MAX / 10 ||
	(result == INT_MAX / 10 && digit > 7)) {
      return sign == 1 ? INT_MAX : INT_MIN;
    }

    result = result * 10 + digit;
    i++;
  }

  return result * sign;
}

void test() {
  int ret = 0;
  char arr[] = "42";
  ret = myAtoi(arr);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   L=[67][1_atoi_LC-8.c]->[test] :| Output = 4
**/
