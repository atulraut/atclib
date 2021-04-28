/***
    Easy: :Power of Two - Including negative numbers.

    Given an integer n, return true if it is a power of two
    Otherwise, return false. How handle -ve numbers.
    Input: n = 2
    Output: true

    Input: n = -8
    Output: false

    Constraints:
    Follow up: Could you solve it without loops/recursion?

    Date: 27 April 2021
    San Diego, CA.
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

bool isPowerOfTwo(int n) {
  if (n < 1) {
    return false;
  }

  debug ("nmod2= %d", (n%2));

  while (n % 2 == 0) {
    debug ("n = %d", n);
    n /= 2;
    debug ("n = %d", n);
    debug ("nmod2= %d", (n%2));
  }
  debug ("n = %d", n);
  return n == 1;
}

int main () {
  int num = -4;
  bool ret;

  ret = isPowerOfTwo(num);
  printf ("--> O/P = %d \n", ret);

  return 0;;
}

/***

    Approach 1: Loop Iteration

    One simple way of finding out if a number n is a power of a number b
    is to keep dividing n by b as long as the remainder is 0.
    This is because we can write

    n = b^x
    n = b × b ×… × b

    Hence it should be possible to divide n by b x times,
    every time with a remainder of 0 and the end result to be 1.
*/

/*
  Complexity Analysis

  * Time complexity : O(log⁡b(n)) .
  In our case that is O(log⁡3n).
  The number of divisions is given by that logarithm.
  * Space complexity : O(1)O(1)O(1). We are not using any
  additional memory.
*/
