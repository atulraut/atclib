/***
    http://c-faq.com/lib/itoa.html
 */

/* sprintf example */
#include <stdio.h>

void sprintf_atclib () {
  char buffer [50];
  int n, a=5, b=3;
  n=sprintf (buffer, "%d plus %d is %d", a, b, a+b);
  printf ("[%s] is a string %d chars long\n",buffer,n);
}

int main () {
  sprintf_atclib ();
  return 0;
}

/***
    => ./a.out
    [5 plus 3 is 8] is a string 13 chars long
*/
