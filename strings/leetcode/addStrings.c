/***
    Easy: Add Strings
    Given two non-negative integers, num1 and num2 represented as string,
    return the sum of num1 and num2 as a string.

    You must solve the problem without using any built-in library for handling
    large integers (such as BigInteger). You must also not convert the
    inputs to integers directly.

    Input: num1 = "11", num2 = "123"
    Output: "134"

    Input: num1 = "456", num2 = "77"
    Output: "533"

    Input: num1 = "0", num2 = "0"
    Output: "0"

    Constraints:
    1 <= num1.length, num2.length <= 104
    num1 and num2 consist of only digits.
    num1 and num2 don't have any leading zeros except for the zero itself.

    https://leetcode.com/problems/add-strings/
    Date: 9 August 2021.
    Fair Oaks, CA.
*/

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

char* addStrings(char* num1, char* num2) {
  size_t end1, end2, end3, siz3;
  char *num3;
  int digit, carry;

  end1 = strlen(num1);
  end2 = strlen(num2);
  end3 = end1 > end2 ? end1 : end2;

  if (end1 == end2 && num1[0] + num2[0] > '0' + '0' + 9)
    ++end3;

  num3 = malloc((siz3 = end3 + 1) * sizeof(char));
  carry = 0;

  while(end1 != 0 || end2 != 0) {
    digit = (end1 == 0 ? 0 : num1[--end1] - '0')
      + (end2 == 0 ? 0 : num2[--end2] - '0');
    if (carry)
      ++digit;
    debug("--->digit=%d  >= %d", digit, (digit > 9));
    carry = digit > 9;
    if (carry)
      digit -= 10;
    num3[--end3] = (char)('0' + digit);
  }
  debug("end3 = %ld", end3);
  if (carry) {
    if (end3 == 0) {
      num3 = realloc(num3, ++siz3);
      (void)memmove(num3 + 1, num3, (siz3 - 2) * sizeof(char));
    }
    num3[0] = '1';
  }
  debug ("siz3=%ld", siz3);
  num3[siz3 - 1] = '\0';
  return num3;
}

int main () {
  int ret = 0;
  char num1[] = "173";
  char num2[] = "34";

  char*op = addStrings(num1, num2);
  debug("Output = %s", op);
  return 0;
}

/**
   => ./a.out
   [addStrings] L=62 :--->digit=7  >= 0
   [addStrings] L=62 :--->digit=10  >= 1
   [addStrings] L=62 :--->digit=2  >= 0
   [addStrings] L=68 :end3 = 0
   [addStrings] L=76 :siz3=4
   [main] L=87 :Output = 207
**/
