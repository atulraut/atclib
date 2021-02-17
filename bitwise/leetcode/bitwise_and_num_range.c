/*
  Below Both Problems are same.
  1] Bitwise AND of Numbers Range :
  2] Hamming Distance :
  Given a range [m, n] where 0 <= m <= n <= 2147483647, return the
  bitwise AND of all numbers in this range, inclusive.
  Explain: https://www.youtube.com/watch?v=-qrpJykY2gE

  https://leetcode.com/problems/bitwise-and-of-numbers-range/
  https://leetcode.com/problems/hamming-distance/solution/
*/
#include <stdio.h>
#include <stdlib.h>
#include "../../at_lib.h"

int rangeBitwiseAnd(int m, int n) {
  int count = 0;
  while (m!=n) {
    m >>= 1;
    n >>= 1;
    count += 1;
  }
  debug(" count = %d m = %d n = %d", count, m, n);
  return (m <<= count);
}

int main () {
  int m = 5;
  int n = 7;
  int ret = 0;
  ret = rangeBitwiseAnd(m, n);
  printf ("[%s] ret-> %d L=%d\n",__func__, ret, __LINE__);
}

/***
    Algo :
    A1] Left Most (LSB) will always same, hence we have first check m!n.
    A2] Right shit (discard right most 1 bit every time to compare A1).
    A3] This is minimum way we get the difference, using count variable.
    To Proe A1 :
      LSB | MSB
    M - 1 0 1 - 5
    N - 1 1 1 - 7
 */
/***
    Complexity Analysis

    Time Complexity: O(1).
    Similar as the bit shift approach, the number of iteration in the
    algorithm is bounded by the number of bits in an integer number,
    which is constant.

    Though having the same asymptotic complexity as the bit shift approach,
    the Brian K ernighan's algorithm requires less iterations,
    since it skips all the zero bits in between.

    Space Complexity: O(1), since no additional memory is consumed by
    the algorithm.
*/
