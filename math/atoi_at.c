/**
   Program to convert char to integer.
   https://leetcode.com/problems/string-to-integer-atoi/

   String to Integer (atoi)

   Implement the myAtoi(string s) function, which converts a
   string to a 32-bit signed integer (similar to C/C++'s atoi function).

   The algorithm for myAtoi(string s) is as follows:

   Read in and ignore any leading whitespace.
   Check if the next character (if not already at the end of the string)
   is '-' or '+'. Read this character in if it is either. This determines
   if the final result is negative or positive respectively. Assume the
   result is positive if neither is present.
   Read in next the characters until the next non-digit character or the
   end of the input is reached. The rest of the string is ignored.

   Convert these digits into an integer (i.e. "123" -> 123, "0032" -> 32).
   If no digits were read, then the integer is 0. Change the sign as
   necessary (from step 2).
   If the integer is out of the 32-bit signed integer range [-231, 231 - 1],
   then clamp the integer so that it remains in the range. Specifically, integers
   less than -231 should be clamped to -231, and integers greater than 231 - 1
   should be clamped to 231 - 1.

   Return the integer as the final result.
   Note:

   Only the space character ' ' is considered a whitespace character.
   Do not ignore any characters other than the leading whitespace or the rest
   of the string after the digits.

   Input: s = "42"
   Output: 42
   Explanation: The underlined characters are what is read in,
   the caret is the current reader position.
   Step 1: "42" (no characters read because there is no leading whitespace)
   ^
   Step 2: "42" (no characters read because there is neither a '-' nor '+')
   ^
   Step 3: "42" ("42" is read in)
   ^
   The parsed integer is 42.
   Since 42 is in the range [-231, 231 - 1], the final result is 42.
   Example 2:

   Input: s = "   -42"
   Output: -42
   Explanation:
   Step 1: "   -42" (leading whitespace is read and ignored)
   ^
   Step 2: "   -42" ('-' is read, so the result should be negative)
   ^
   Step 3: "   -42" ("42" is read in)
   ^
   The parsed integer is -42.
   Since -42 is in the range [-231, 231 - 1], the final result is -42.
   Example 3:

   Input: s = "4193 with words"
   Output: 4193
   Explanation:
   Step 1: "4193 with words" (no characters read because there is no leading whitespace)
   ^
   Step 2: "4193 with words" (no characters read because there is neither a '-' nor '+')
   ^
   Step 3: "4193 with words" ("4193" is read in; reading stops because the next character is a non-digit)
   ^
   The parsed integer is 4193.
   Since 4193 is in the range [-231, 231 - 1], the final result is 4193.
   Example 4:

   Input: s = "words and 987"
   Output: 0
   Explanation:
   Step 1: "words and 987" (no characters read because there is no leading whitespace)
   ^
   Step 2: "words and 987" (no characters read because there is neither a '-' nor '+')
   ^
   Step 3: "words and 987" (reading stops immediately because there is a non-digit 'w')
   ^
   The parsed integer is 0 because no digits were read.
   Since 0 is in the range [-231, 231 - 1], the final result is 0.
   Example 5:

   Input: s = "-91283472332"
   Output: -2147483648
   Explanation:
   Step 1: "-91283472332" (no characters read because there is no leading whitespace)
   ^
   Step 2: "-91283472332" ('-' is read, so the result should be negative)
   ^
   Step 3: "-91283472332" ("91283472332" is read in)
   ^
   The parsed integer is -91283472332.
   Since -91283472332 is less than the lower bound of the range [-231, 231 - 1],
   the final result is clamped to -231 = -2147483648.

   Constraints:
   0 <= s.length <= 200
   s consists of English letters (lower-case and upper-case),
   digits (0-9), ' ', '+', '-', and '.'.

   Date: 11/23 World Fibonacci Day
   Folsom, CA
*/

#include <stdio.h>
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

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

int leetcode_atoi(char * str) {
  if (str == NULL)
    return 0;

  int i = 0;
  bool neg = false;

  char c = str[i];
  while (c != '\0') {
    if (isdigit(c))
      break;

    char nextChar = str[i+1];
    if (nextChar == '\0')
      return 0;
    else if (c == '.' && isdigit(nextChar)) {
      return 0;
    } else if (c == '+' || c == '-') {
      if (!isdigit(nextChar))
	return 0;
      i++;

      if (c == '-')
	neg = true;

      break;
    }
    else if (isalpha(c))
      return 0;

    c = str[++i];
  }

  int res = 0;
  printf("i=%d c=%c\n", i, str[i]);
  while(isdigit(str[i])) {
    int d = str[i] - '0';

    if (neg)
      d = -d;

    if (res > INT_MAX/10 || (res == INT_MAX/10 && d > 7))
      return INT_MAX;

    if (res < INT_MIN/10 || (res == INT_MIN/10 && d < -8))
      return INT_MIN;

    res = res*10 + d;

    i++;
  }

  return res;

}

/* Linux Implemention */
long atoi_linux(const char *s) {
  unsigned long ret = 0;
  unsigned long d;
  int neg = 0;

  if (*s == '-') {
    neg = 1;
    s++;
  }

  while (1) {
    d = (*s++) - '0';
    if (d > 9)
      break;
    ret *= 10;
    ret += d;
  }

  return neg ? -ret : ret;
}

// (s[i] - '0') : Gives Numeric Values of the character stored in s[i].
int atoi_atclib (char s[]) {
  int i, n;
  n = 0;
  printf ("\ns = %s", s);
  for (i=0; i<= '0' && i <= '9'; ++i)
    n = 10 * n + (s[i]- '0');
  return n;
}

int main () {
  int n;
  n = 0;
  char c[1] = "a";
  printf ("\n c = %s", c);
  n = atoi_atclib(c);
  printf ("\n int = %d \n", n);

  char d[] = "789";
  n = atoi_linux (d);
  debug ("String to Number Linux Way atoi-->%d", n);
  n = leetcode_atoi(d);
  debug ("String to Number Linux Way atoi-->%d", n);
  return 0;
}

/**
   => ./a.out

   c = a�
   s = a�
   int = 1585068083
   [main] L=222 :String to Number Linux Way atoi-->789
   i=0 c=7
   [main] L=224 :String to Number Linux Way atoi-->789
*/

