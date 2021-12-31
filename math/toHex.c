/***
    https://leetcode.com/problems/convert-a-number-to-hexadecimal
    Convert a Number to Hexadecimal

    Given an integer num, return a string representing its hexadecimal
    representation. For negative integers, two’s complement method is used.

    All the letters in the answer string should be lowercase characters,
    and there should not be any leading zeros in the answer except for
    the zero itself.

    Note: You are not allowed to use any built-in library method to
    directly solve this problem.

    Input: num = 26
    Output: "1a"

    Input: num = -1
    Output: "ffffffff"


    Constraints:
    -231 <= num <= 231 - 1

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address toHex.c -lm

    Date: 12/31/2021
    Folsom, CA.
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

char* toHex(int num) {
  unsigned int n = num;
  int size = 0;
  if (n==0)
    return "0";

  while(n > 0) {
    n /= 16;
    size++;
  }
  n=num;

  char* ans = (char*) malloc(sizeof(char*)*size);
  ans[size] = '\0';
  while(n>0) {
    char c = n%16;
    (c<10) ? (c+='0') : (c+='a'-10);
    n=n/16;
    ans[--size] = c;
  }
  return ans;
}

int main (int argc, char **argv) {
  char* ret;
  int a = 26;

  ret = toHex(a);
  debug("Output = %s", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=85 :Output = 1a
 **/
