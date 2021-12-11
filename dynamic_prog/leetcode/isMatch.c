/***
    https://leetcode.com/problems/regular-expression-matching

    Regular Expression Matching

    Given an input string s and a pattern p, implement regular expression
    matching with support for '.' and '*' where:

    '.' Matches any single character.
    '*' Matches zero or more of the preceding element.
    The matching should cover the entire input string (not partial).

    Input: s = "aa", p = "a"
    Output: false
    Explanation: "a" does not match the entire string "aa".

    Input: s = "aa", p = "a*"
    Output: true
    Explanation: '*' means zero or more of the preceding element, 'a'.
    Therefore, by repeating 'a' once, it becomes "aa".

    Input: s = "ab", p = ".*"
    Output: true
    Explanation: ".*" means "zero or more (*) of any character (.)".

    Input: s = "aab", p = "c*a*b"
    Output: true
    Explanation: c can be repeated 0 times, a can be repeated 1 time
    Therefore, it matches "aab".

    Input: s = "mississippi", p = "mis*is*p*."
    Output: false

    Constraints:
    1 <= s.length <= 20
    1 <= p.length <= 30
    s contains only lowercase English letters.
    p contains only lowercase English letters, '.', and '*'.
    It is guaranteed for each appearance of the character '*',
    there will be a previous valid character to match.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address isMatch.c -lm

    Date: 121121 : Palindrome Date (Dec 11, 2021)
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
#define max(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a > _b ? _a : _b; })
#define min(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

bool isMatch(char *s, char *p) {
  const int textSize = strlen(s);
  const int patternSize = strlen(p);
  bool dp[textSize + 1][patternSize + 1];

  // initialize the array to true
  for (int i = 0; i <= textSize; ++i)
    for (int j = 0; j <= patternSize; ++j)
      dp[i][j] = 0;

  dp[textSize][patternSize] = 1;
  for (int i = textSize; i >= 0; --i)
    for (int j = patternSize - 1; j >= 0; --j) {
      bool first_match = (i < textSize && (p[j] == s[i] || p[j] == '.'));
      if (j + 1 < patternSize && p[j + 1] == '*')
	dp[i][j] = dp[i][j + 2] || first_match && dp[i + 1][j];
      else
	dp[i][j] = first_match && dp[i + 1][j + 1];
    }

  return dp[0][0];
}

bool isMatch2(char * s, char * p) {
  int adv/*ance p*/ = 1;
  if (*p == 0)
    return *s == 0;
  if (*p && *(p+1) && *(p+1) == '*') {
    if (isMatch(s, p + 2))
      return 1;
    adv = 0;
  }
  if (*s && *p == '.' || *s == *p)
    return isMatch(s + 1, p + adv);
  return 0;
}

int main (int argc, char **argv) {
  int ret = 0;
  char s[] = "ab";
  char p[] = ".*";

  ret = isMatch(s, p);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=117 :Output = 1
**/
