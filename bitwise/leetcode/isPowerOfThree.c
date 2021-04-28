/***
    Easy: 326. Power of Three
    https://leetcode.com/problems/power-of-three/

    Given an integer n, return true if it is a power of three.
    Otherwise, return false.
    An integer n is a power of three, if there exists an
    integer x such that n == 3x.

    Input: n = 27
    Output: true

    Input: n = 0
    Output: false

    Input: n = 9
    Output: true

    Input: n = 45
    Output: false

    Constraints:
    -231 <= n <= 231 - 1
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

bool isPowerOfThree1(int n) {
  if(n <= 0)
    return false;

  long i = 1;
  while (i <= n ) {
    if (i == n)
      return true;
    else
      i *= 3;
  }
  return false;
}

bool isPowerOfThree(int n){
  if(n <= 0)
    return false;
  while(n > 1) {
    if((n%3) != 0)
      return false;
    n/=3;
  }
  return true;
}

int main () {
  int num = 27;
  bool ret;

  ret = bool isPowerOfThree(num);
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

    Hence it should be possible to divide n by b x times
    every time with a remainder of 0 and the end result to be 1.
*/

/*
  Complexity Analysis

  * Time complexity : O(log⁡b(n)
  In our case that is O(log⁡3n)
  The number of divisions is given by that logarithm.
  * Space complexity : O(1)O(1)O(1). We are not using any
  additional memory.
*/
