/***
    https://leetcode.com/problems/find-the-divisibility-array-of-a-string/

    2575. Find the Divisibility Array of a String

    You are given a 0-indexed string word of length n consisting of
    digits, and a positive integer m.

    The divisibility array div of word is an integer array of length
    n such that:

    div[i] = 1 if the numeric value of word[0,...,i] is divisible by m, or
    div[i] = 0 otherwise.
    Return the divisibility array of word.

    Input: word = "998244353", m = 3
    Output: [1,1,0,0,0,1,1,0,0]
    Explanation: There are only 4 prefixes that are divisible
    by 3: "9", "99", "998244", and "9982443".

    Input: word = "1010", m = 10
    Output: [0,1,0,1]
    Explanation: There are only 2 prefixes that are divisible b
    y 10: "10", and "1010".

    Constraints:
    1 <= n <= 105
    word.length == n
    word consists of digits from 0 to 9
    1 <= m <= 109

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Sat 27 Jul 2024 08:21:00 AM PDT
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

#define debug(str,args...) printf("L=[%d] [%s] :| "str"\n", __LINE__, __func__, ##args)

/***
    Intuition :
    We need a preSum from left to right. But preSum might overflow
    if the string is long enough. Since it just checks the divisibility,
    modulo operation will be considered.

    Approach :
    If (prevSum % m == r), prevSum can be written
    prevSum = k * m + r;

    Sum % m = (prevSum * 10 + currentNum) % m
    = ((k * m + r) * 10 + currentNum) % m
    = (r * 10 + currentNum) % m

    We will get the same result to use either prevSum or the
    remainder of prevSum.

    Complexity :
    Time complexity:
    O(n)

    Space complexity:
    O(n)
*/

int *divisibilityArray(const char *const word, const int m, int *const returnSize) {

  const int size = strlen(word);
  int *div = malloc(size * sizeof *div);
  long long sum = 0;
  for (int i = 0; i < size; ++i) {
    debug ("Sum = %lld", (sum * 10 + word[i] - '0'));
    sum = (sum * 10 + word[i] - '0') % m;
    debug ("sum = %lld", sum);
    div[i] = (!sum) ? 1 : 0;
  }
  *returnSize = size;
  return div;
}

void test() {
  int* ret;
  char word[] = "998244353";
  int m = 3;
  int returnSize;

  ret = divisibilityArray(word, m, &returnSize);
  for (int i=0; i<returnSize; ++i)
    debug("Output = %d", ret[i]);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   L=[83] [divisibilityArray] :| Sum = 9
   L=[85] [divisibilityArray] :| sum = 0
   L=[83] [divisibilityArray] :| Sum = 9
   L=[85] [divisibilityArray] :| sum = 0
   L=[83] [divisibilityArray] :| Sum = 8
   L=[85] [divisibilityArray] :| sum = 2
   L=[83] [divisibilityArray] :| Sum = 22
   L=[85] [divisibilityArray] :| sum = 1
   L=[83] [divisibilityArray] :| Sum = 14
   L=[85] [divisibilityArray] :| sum = 2
   L=[83] [divisibilityArray] :| Sum = 24
   L=[85] [divisibilityArray] :| sum = 0
   L=[83] [divisibilityArray] :| Sum = 3
   L=[85] [divisibilityArray] :| sum = 0
   L=[83] [divisibilityArray] :| Sum = 5
   L=[85] [divisibilityArray] :| sum = 2
   L=[83] [divisibilityArray] :| Sum = 23
   L=[85] [divisibilityArray] :| sum = 2
   L=[100] [test] :| Output = 1
   L=[100] [test] :| Output = 1
   L=[100] [test] :| Output = 0
   L=[100] [test] :| Output = 0
   L=[100] [test] :| Output = 0
   L=[100] [test] :| Output = 1
   L=[100] [test] :| Output = 1
   L=[100] [test] :| Output = 0
   L=[100] [test] :| Output = 0
**/
