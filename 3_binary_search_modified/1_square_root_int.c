/***

    https://leetcode.com/problems/sqrtx/

    69. Sqrt(x)

    Given a non-negative integer x, return the square root of x rounded
    down to the nearest integer.
    The returned integer should be non-negative as well.

    You must not use any built-in exponent function or operator.
    For example, do not use pow(x, 0.5) in c++ or x ** 0.5 in python.

    Input: x = 4
    Output: 2
    Explanation: The square root of 4 is 2, so we return 2.
    Example 2:

    Input: x = 8
    Output: 2
    Explanation: The square root of 8 is 2.82842..., and since we
    round it down to the nearest integer, 2 is returned.

    Constraints:
    0 <= x <= 231 - 1

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Tue Oct  6 12:24:13 PDT 2026
    Folsom, CA.
 */

/*----------------------------------- Header --------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h> // va_arg
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */

#define debug(str,args...) printf("L=[%d][%s]->[%s] :| "str"\n",__LINE__,__FILE__, __func__, ##args)

// The use of long long is for the prevention of overflow.
int mySqrt(int x) {

  if (x < 2) return x;

  long long num;
  int pivot, left = 2, right = x / 2;

  while (left <= right) {
    pivot = left + (right - left) / 2;
    num = (long long)pivot * pivot;
    if (num > x)
      right = pivot - 1;
    else if (num < x)
      left = pivot + 1;
    else
      return pivot;
  }
  return right;
}

void test() {
  int ret = 4;

  debug("Output = %d", mySqrt(4));
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   L=[67][1_square_root_int.c]->[test] :| Output = 2
**/

/**
   Binary Search : Intuition
   Let's go back to the interview context. For x≥2 the square root
   is always smaller than x/2 and larger than 0 : 0<a<x/2. Since
   a is an integer, the problem goes down to the iteration over
   the sorted set of integer numbers. Here the binary search
   enters the scene.

   Algorithm :

   If x < 2, return x.
   Set the left boundary to left = 2, and the right
   boundary to right = x / 2.

   While left <= right:
         Take num = (left + right) / 2 as a guess.
	 Compute num * num and compare it with x:

   If  num * num > x,
       move the right boundary `right = pivot - 1`
   Else, if num * num < x,
       move the left boundary left = pivot + 1

   Otherwise num * num == x, the integer square root is here, let's return it.

   Return right
**/

/**
   Complexity Analysis

   Time complexity : O(logN).

   Let's compute time complexity with the help of master theorem T(N)=aT(bN)+Θ(Nd).
   The equation represents dividing the problem up into a subproblems of size bN in Θ(Nd) time.
   Here at step, there is only one subproblem a = 1, its size is half of the initial problem b = 2, and all this happens in a constant time d = 0. That means that logb a=d and hence we're dealing with case 2 that results in O(nlogba logd+1 N) = O(logN) time complexity.

   Space complexity : O(1).
**/
