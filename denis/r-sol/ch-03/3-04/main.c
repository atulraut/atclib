 /*
* WAP : In a two's complement number representation , our version of itoa
* does not handle the learget negative number, that is, the value of n equal
* to -(2wordsize-1)
*
* Date : Thursday Septmber 08 2011 7:45AM
***/

#include <stdio.h>

#define abs(x) ((x) < 0 ? -(x) : (x))

void my_itoa (int, char []);

int main () {
  int i, k;
  char s[2];
  i = -12341212;
  my_itoa (i, s);
}

void my_itoa (int n, char s[]) {
  int i, sign;
  char k;
  i = 0;
  
  void reverse(char s[]);
  sign = n;             /* record sign*/
  
  do {                             /* generate digits in reverse order */
    s[i++] = abs(n % 10) + '0';    /* get next digit */
  } while ((n /= 10) != 0);
  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';
  reverse(s);
  printf ("\n my_itoa = %s\n", s);
}
