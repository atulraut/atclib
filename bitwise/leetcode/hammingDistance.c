/***
    https://leetcode.com/problems/hamming-distance/
    Hamming Distance :
    The Hamming distance between two integers is the number of positions
    at which the corresponding bits are different.

    Given two integers x and y, calculate the Hamming distance.
    Note:
    0 ≤ x, y < 231.

    Example:
    Input: x = 1, y = 4

    Output: 2
    Explanation:
    1   (0 0 0 1)
    4   (0 1 0 0)
    ↑   ↑

    The above arrows point to positions where the corresponding bits are different.
    Date : 7/Feb/2021
    San Diego, CA
*/
#include <stdio.h>
#include <stdlib.h>
#include "../../at_lib.h"

int hammingDistance(int x, int y){
  int xor = x ^ y;
  int distance = 0;
  while (xor != 0) {
    distance += 1;
    // remove the rightmost bit of '1'
    xor = xor & (xor - 1);
  }
  return distance;
}

int main () {
  int m = 4;
  int n = 1;
  int ret = 0;
  ret = hammingDistance(m, n);
  printf ("[%s] ret-> %d L=%d\n",__func__, ret, __LINE__);
}

/***
   => ./a.out
   [main] ret-> 2 L=42
*/

/**
   Complexity Analysis :

   Time Complexity: O(1)\mathcal{O}(1)O(1).
   Similar as the approach of bit shift, since the size (i.e. bit number) of
   integer number is fixed, we have a constant time complexity.
   However, this algorithm would require less iterations than the bit shift
   approach, as we have discussed in the intuition.
   Space Complexity: O(1)\mathcal{O}(1)O(1), a constant size of memory is
   used, regardless the input
**/
