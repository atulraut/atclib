/*
* Program to convert char to integer.
***/

#include <stdio.h>

int atoi (char []);

int main () {
  int n;
  n = 0;
  char c[1] = "a";
  printf ("\n c = %s", c);
  n = atoi(c);
  printf ("\n int = %d", n);  
  return 0;
}

int atoi (char s[]) {
  int i, n;
  n = 0;
  printf ("\ns = %s", s);
  for (i=0; i<= '0' && i <= '9'; ++i)
    n = 10 * n + (s[i]- '0');
  return n;
}

// (s[i] - '0') : Gives Numeric Values of the character stored in s[i].
