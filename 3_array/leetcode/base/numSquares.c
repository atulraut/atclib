/***
    https://leetcode.com/problems/perfect-squares/
    Perfect Squares

    Given an integer n, return the least number of
    perfect square numbers that sum to n.

    A perfect square is an integer that is the square of an integer;
    in other words, it is the product of some integer with itself.
    For example, 1, 4, 9, and 16 are perfect squares while
    3 and 11 are not.

    Input: n = 12
    Output: 3
    Explanation: 12 = 4 + 4 + 4.
    Example 2:

    Input: n = 13
    Output: 2
    Explanation: 13 = 4 + 9.

    Constraints:
    1 <= n <= 104

    gcc numSquares.c -o aout -lm

    Date: 14 Oct 2021
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

static int is_square(int n) {
    debug ("n = %d", n);
    int root = sqrt(n);
    debug ("r
oot = %d", root);
    if (n == root * root)
        return 1;
    else
        return 0;
}

int numSquares(int n) {
  if (is_square(n) != 0)
    return 1;

  debug ("n = %d", n);
  while ((n & 0x3) == 0) {
    n >>= 2;
    debug ("n = %d", n); // 3
  }

  if ((n & 0x7) == 7)
    return 4;
  {
    int root = sqrt(n);
    int idx;
    debug ("root = %d", root); // 1
    for (idx = 1; idx <= root; idx++) {
      if (is_square(n - idx * idx) != 0) // 3-1 == 2
	return 2;
    }
  }
  return 3;
}

int main (int argc, char **argv) {
  int ret = 0;
  int n = 12;

  ret =  numSquares(n);
  debug("Output = %d", ret);
  return 0;
}

/**

 **/
