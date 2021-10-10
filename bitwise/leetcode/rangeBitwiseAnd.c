/***
    https://leetcode.com/problems/bitwise-and-of-numbers-range/
    Bitwise AND of Numbers Range

    Given two integers left and right that represent the range
    [left, right], return the bitwise AND of all numbers in
    this range, inclusive.

    Input: left = 5, right = 7
    Output: 4

    Input: left = 0, right = 0
    Output: 0

    Input: left = 1, right = 2147483647
    Output: 0

    Constraints:
    0 <= left <= right <= 231 - 1

    Date: 10/10/2021
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

//http://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetKernighan
void test() {
  static const unsigned char BitsSetTable256[256] = {
#   define B2(n) n,     n+1,     n+1,     n+2
#   define B4(n) B2(n), B2(n+1), B2(n+1), B2(n+2)
#   define B6(n) B4(n), B4(n+1), B4(n+1), B4(n+2)
    B6(0), B6(1), B6(1), B6(2)
  };

  unsigned int v; // count the number of bits set in 32-bit value v
  unsigned int c; // c is the total bits set in v

  // Option 1:
  c = BitsSetTable256[v & 0xff] +
    BitsSetTable256[(v >> 8) & 0xff] +
    BitsSetTable256[(v >> 16) & 0xff] +
    BitsSetTable256[v >> 24];

  // Option 2:
  unsigned char * p = (unsigned char *) &v;
  c = BitsSetTable256[p[0]] + BitsSetTable256[p[1]] + BitsSetTable256[p[2]] + BitsSetTable256[p[3]];

  /*
  // To initially generate the table algorithmically:
  BitsSetTable256[0] = 0;
  for (int i = 0; i < 256; i++) {
    BitsSetTable256[i] = (i & 1) + BitsSetTable256[i / 2];
    debug ("BitsSetTable256[%d] = %d",i, BitsSetTable256[i]);
  }
  */
}

int rangeBitwiseAnd(int left, int right) {
  while (left < right) {
    debug ("right = %d right-1=%d", right, (right-1));
    // turn off rightmost 1-bit
    right = right & (right - 1);
    debug ("right = %d", right);
  }
  return left & right;
}

int main (int argc, char **argv) {
  int ret = 0;
  int left = 5;
  int right =7;
  ret = rangeBitwiseAnd(left, right);
  debug("Output = %d", ret);
  test();
  return 0;
}

/**
   Complexity Analysis
   Time Complexity: O(1)
   Although there is a loop in the algorithm, the number of
   iterations is bounded by the number of bits that an
   integer has, which is fixed.
   Therefore, the time complexity of the algorithm is constant.
   Space Complexity: O(1). The consumption of the memory
   for our algorithm is constant, regardless the input.
**/

/**
   => ./a.out
   [rangeBitwiseAnd] L=72 :right = 7 right-1=6
   [rangeBitwiseAnd] L=75 :right = 6
   [rangeBitwiseAnd] L=72 :right = 6 right-1=5
   [rangeBitwiseAnd] L=75 :right = 4
   [main] L=85 :Output = 4
**/
