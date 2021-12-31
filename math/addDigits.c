/***
    https://leetcode.com/problems/add-digits
    Add Digits

    Given an integer num, repeatedly add all its digits until
    the result has only one digit, and return it.

    Input: num = 38
    Output: 2
    Explanation: The process is
    38 --> 3 + 8 --> 11
    11 --> 1 + 1 --> 2
    Since 2 has only one digit, return it.

    Input: num = 0
    Output: 0

    Constraints:
    0 <= num <= 231 - 1

    Follow up: Could you do it without any loop/recursion in O(1) runtime?

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 12/30/2021
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

/*
  Must Check - https://leetcode.com/problems/add-digits/solution/
*/
int addDigits2(int num){
  if (num == 0)
    return 0;
  if (num % 9 == 0)
    return 9;
  return num % 9;
}

int addDigits(int num) {
  return num == 0 ? 0 : 1 + (num - 1) % 9;
}

int main (int argc, char **argv) {
  int ret = 0;
  int num = 38;

  ret = addDigits(num);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=75 :Output = 2
**/
