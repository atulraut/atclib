/***
    Number / Int to string converter.
    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Wed Sep  9 17:47:40 2026
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

void reverse(char *str, int len) {

  int i = 0, j = len - 1;

  while (i < j) {
    char tmp = str[i];
    str[i] = str[j];
    str[j] = tmp;

    i++;
    j--;
  }
}

/**
   convert number to string
*/
char* atclib_itoa(int num, char *str) {

  unsigned int n;
  int i = 0;
  int negative = 0;

  if (num < 0) {
    negative = 1;
    n = 0U - (unsigned int)num;
  } else {
    n = (unsigned int)num;
  }

  do {
    str[i++] = (n % 10) + '0'; // '0' == 48 - 0 Char
    n /= 10;
  } while (n != 0);

  if (negative)
    str[i++] = '-';

  str[i] = '\0';

  reverse(str, i);

  return str;
}


/* Linux Implemention */
long atoi_linux(const char *s) {
  unsigned long ret = 0;
  unsigned long d;
  int neg = 0;

  if (*s == '-') {
    neg = 1;
    s++;
  }

  while (1) {
    d = (*s++) - '0';
    if (d > 9)
      break;
    ret *= 10;
    ret += d;
  }

  return neg ? -ret : ret;
}

void test() {
  char str[20];

  debug("Inte to String : -->");
  debug("-> [%s]", atclib_itoa(12345, str));
  debug("-> [%s]", atclib_itoa(-12345, str));
  debug("-> [%s]", atclib_itoa(0, str));

  debug("String to Int Linux : -->");
  debug("-> [%ld]", atoi_linux("123abc"));
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   L=[95][strings/crack-d-ivi/3_itoa.c]->[test] :| Inte to String : -->
   L=[96][strings/crack-d-ivi/3_itoa.c]->[test] :| -> [12345]
   L=[97][strings/crack-d-ivi/3_itoa.c]->[test] :| -> [-12345]
   L=[98][strings/crack-d-ivi/3_itoa.c]->[test] :| -> [0]
   L=[100][strings/crack-d-ivi/3_itoa.c]->[test] :| String to Int Linux : -->
   L=[101][strings/crack-d-ivi/3_itoa.c]->[test] :| -> [123]
**/
