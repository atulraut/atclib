/*
* my_itoa :Convert n to characters in s
* I/P : -1234
* O/P : 1234-
* Date : 7/3/2021, Sunday.
* San Diego, CA.
***/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverseString(char* s, int sSize){
  int len = sSize/2;
  char c;

  for (int i=0; i<len; i++) {
    c = s[sSize-1-i];
    s[sSize-1-i] = s[i];
    s[i] = c;
  }

  printf("\n Reverse String --> %s \n", s);
}

void my_itoa (int n, char s[]) {
  printf ("\n >>>> n = %d", n);
  int i, sign;
  char k;
  if ((sign = n) < 0) { /* record sign */
    n = -n;           /* make n positive */
  }
  i = strlen(s) - 1; // 4-1 = 3, start from End & copy each character.
  s[i--] = '\0';
  do {               /* Generate digits in reverse order */
    printf ("\n n mod 10 >>>>> %d and n = %d", (n % 10), n);
    k = n % 10 + '0';   /* get next digit */
    printf ("\n n mod 10 + '0' >>>>> %c", k);
    s[i--] = k;
  } while ((n /= 10) > 0); /* delete it */
    if (sign < 0)
      s[i--] = '-';

  printf ("\n string = %s\n", s);
  // reverseString (s, i);
}

int main () {
  int i, j;
  char s[2];
  i = -1234;
  j = 10;
  printf ("\nj = %d\n", j++);
  printf ("\nj = %d\n", j);
  printf ("\n >>>> i = %d", i);
  my_itoa (i, s);
  return 0;
}
