/***
    https://leetcode.com/problems/greatest-common-divisor-of-strings
    1071. Greatest Common Divisor of Strings

    For two strings s and t, we say "t divides s" if and only if s = t + ... + t
    (i.e., t is concatenated with itself one or more times).

    Given two strings str1 and str2, return the largest string x such that
    x divides both str1 and str2.

    Input: str1 = "ABCABC", str2 = "ABC"
    Output: "ABC"

    Input: str1 = "ABABAB", str2 = "ABAB"
    Output: "AB"

    Input: str1 = "LEET", str2 = "CODE"
    Output: ""

    Constraints:
    1 <= str1.length, str2.length <= 1000
    str1 and str2 consist of English uppercase letters.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 1 Jan, 2022
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

char* gcdOfStrings(char* str1, char* str2) {
  int len1 = strlen(str1);
  int len2 = strlen(str2);

  if (len1 < len2)
    return gcdOfStrings(str2, str1);

  for (int i = 0; i < len2; i++)
    if (str1[i] != str2[i])
      return "";

  if (len1 == len2)
    return str1;

  return gcdOfStrings(str1+len2, str2);
}

int main (int argc, char **argv) {
  char* ret;
  char str1[] = "ABCABC";
  char str2[] = "ABC";

  ret = gcdOfStrings(str1, str2);
  debug("Output = %s", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=58 :Output = ABC
**/
