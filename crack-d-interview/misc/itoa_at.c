/*
* my_itoa :Convert n to characters in s
* I/P : -1234
* O/P : 1234-
* Date : Wed Sep 7, 7:14PM
***/
#include <stdio.h>

void my_itoa (int n, char s[]) {
  printf ("\n >>>> n = %d", n);
  int i, sign;
  char k;
  if ((sign = n) < 0) { /* record sign */
    n = -n;           /* make n positive */
  }
    i = 0;
  do {               /* Generate digits in reverse order */
    printf ("\n (n%10)      >>>>> %ds and n = %d", (n % 10) , n);  
    k = n % 10 + '0';   /* get next digit */
    printf ("\n (n%10)+ '0' >>>>> %c", k);
    s[i++] = k;
  } while ((n /= 10) > 0); /* delete it */
    if (sign < 0)
      s[i++] = '-';
  s[i] = '\0';
  printf ("\n string = %s\n", s);
  //  reverse (s);
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
