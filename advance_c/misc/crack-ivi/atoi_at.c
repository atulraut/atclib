/*
* Program to convert char to integer.
***/

#include <stdio.h>
#include "../../at_lib.h"

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

// (s[i] - '0') : Gives Numeric Values of the character stored in s[i].
int atoi_atclib (char s[]) {
  int i, n;
  n = 0;
  printf ("\ns = %s", s);
  for (i=0; i<= '0' && i <= '9'; ++i)
    n = 10 * n + (s[i]- '0');
  return n;
}

int main () {
  int n;
  n = 0;
  char c[1] = "a";
  printf ("\n c = %s", c);
  n = atoi_atclib(c);
  printf ("\n int = %d \n", n);

  char d[] = "789";
  n = atoi_linux (d);
  debug ("String to Number Linux Way atoi-->%d", n);
  return 0;
}

