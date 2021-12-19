/***
    https://leetcode.com/problems/palindrome-number
    Palindrome Number

    Given an integer x, return true if x is palindrome integer.

    An integer is a palindrome when it reads the same backward
    as forward. For example, 121 is palindrome while 123 is not.

    Input: x = 121
    Output: true

    Input: x = -121
    Output: false
    Explanation: From left to right, it reads -121. From
    right to left, it becomes 121-. Therefore it is not a palindrome.

    Input: x = 10
    Output: false
    Explanation: Reads 01 from right to left. Therefore it is
    not a palindrome.

    Input: x = -101
    Output: false

    Constraints:
    -231 <= x <= 231 - 1

    Follow up: Could you solve it without converting the integer to a string?

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address isPalindrome.c -lm

    Date: 28 Oct 2021
    Fair Oaks, CA.
*/

/*----------------------------------- Header --------------------------------------*/
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

/*----------------------------------- Micro --------------------------------------*/
#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)
#define atsizeof(object) (char *)(&object+1) - (char*)(&object)
#define arrsz(x)  (sizeof(x) / sizeof((x)[0]))
#define max(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a > _b ? _a : _b; })
#define min(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

bool isPalindrome(int x) {
  long int rev = 0;
  int temp = x;
  if(x < 0)
    return false;

  while(x) {
    rev = rev * 10 + x % 10;
    x /= 10;
  }
  debug ("temp=%d rev=%ld", temp, rev);
  return (temp == rev);
}

bool isPalindrome2(int x) {

  if(x < 0)
    return false;

  long long revert, temp;

  temp = x;
  revert = 0;
  while(temp >= 10) {
    revert += temp%10;
    temp /= 10;
    revert *= 10;
  }
  revert += temp;
  debug("revert %lld, x %d", revert, x);
  return (revert==x);
}

int main (int argc, char **argv) {
  int ret = 0;
  int x = 121;

  ret = isPalindrome(x);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [isPalindrome2] L=91 :revert 121, x 121
   [main] L=100 :Output = 1
**/
