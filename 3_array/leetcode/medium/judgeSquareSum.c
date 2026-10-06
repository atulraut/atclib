/***
    Sum of Square Numbers
    Given a non-negative integer c, decide whether there're two
    integers a and b such that a2 + b2 = c.

    Input: c = 5
    Output: true
    Explanation: 1 * 1 + 2 * 2 = 5

    Input: c = 3
    Output: false

    Input: c = 4
    Output: true

    Input: c = 2
    Output: true

    Input: c = 1
    Output: true

    Constraints:
    0 <= c <= 231 - 1

    gcc judgeSquareSum.c -o aout -lm

    Date: 25 August 2021.
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

bool judgeSquareSum(int c) {
  long left = 0;
  long right = (int)sqrt(c);

  while (left <= right) {
    debug("left=%ld right=%ld", left, right);
    long sum = left * left + right * right;
    if (sum == c)
      return true;
    else if (sum > c)
      right--;
    else
      left++;
  }
  return false;
}

int main (int argc, char **argv) {
  int ret = 0;
  int c = 5;

  ret = judgeSquareSum(c);
  debug("Output = %d", ret);
  return 0;
}

/**
   => gcc judgeSquareSum.c -o aout -lm
   => ./aout
   [judgeSquareSum] L=49 :left=0 right=2
   [judgeSquareSum] L=49 :left=1 right=2
   [main] L=66 :Output = 1
**/
