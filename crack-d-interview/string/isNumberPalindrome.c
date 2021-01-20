/***
    Check number is Palindrome or not.
*/
#include <stdio.h>
#include "../../at_lib.h"

int isNumberPalindrome(int x) {
  if(x < 0)
    return -1;
  int n = 1;
  while(x / n >= 10) {
    printf ("[A] = %d n=%d\t", (x/n), n);
    n *= 10;
    printf ("[B] n=%d\t", n);
  }
  printf ("\n");
  while(n > 1) {
    debug ("1 M = %d D = %d", (x % 10), (x / n));
    if( (x % 10) != (x / n) ) {
      debug (" 2 Returning -1");
      return -1;
    }
    x = (x % n) / 10;
    debug ("3 Mx = %d", (x%n));
    debug ("3 x = %d", x);
    n /= 100;
    debug ("4 n = %d", n);
  }
  return 1;
}

int main()
{
  printf("Hello World L = %d ", isNumberPalindrome(101) );

  return 0;
}

/***
    => ./a.out
    [A] = 101 n=1	[B] n=10	[A] = 10 n=10	[B] n=100
    [isNumberPalindrome.c] [isNumberPalindrome()] L=18 :1 M = 1 D = 1
    [isNumberPalindrome.c] [isNumberPalindrome()] L=24 :3 Mx = 0
    [isNumberPalindrome.c] [isNumberPalindrome()] L=25 :3 x = 0
    [isNumberPalindrome.c] [isNumberPalindrome()] L=27 :4 n = 1
*/
