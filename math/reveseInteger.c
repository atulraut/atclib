/*
  Reverse Integer
  https://leetcode.com/problems/reverse-integer

  Given a signed 32-bit integer x, return x with its digits
  reversed. If reversing x causes the value to go outside the
  signed 32-bit integer range [-231, 231 - 1], then return 0.

  Assume the environment does not allow you to store 64-bit
  integers (signed or unsigned).

  Input: x = 123
  Output: 321

  Input: x = -123
  Output: -321

  Input: x = 120
  Output: 21

  Input: x = 0
  Output: 0

  Constraints:
  -231 <= x <= 231 - 1

  Date: 11/23/ - Fibonacci Day
  Folsom, CA.
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

/**
   Approach 1: Pop and Push Digits & Check before Overflow
   Intuition

   We can build up the reverse integer one digit at a time.
   While doing so, we can check beforehand whether or not
   appending another digit would cause overflow.

   Algorithm
   Reversing an integer can be done similarly to reversing a string.

   We want to repeatedly "pop" the last digit off of x and "push"
   it to the back of the rev. In the end, rev
   will be the reverse of the xx.

   To "pop" and "push" digits without the help of some auxiliary
   stack/array, we can use math.

   //pop operation:
   pop = x % 10;
   x /= 10;

   //push operation:
   temp = rev * 10 + pop;
   rev = temp;
   However, this approach is dangerous, because the statement
   {temp} = {rev} * 10 + {pop} can cause overflow.

   Luckily, it is easy to check beforehand whether or this statement
   would cause an overflow.

   To explain, lets assume that {rev} is positive.

   1] If temp = {rev} * 10 + {pop} causes overflow, then it must
      be that {rev} >= {INTMAX}/{10}
   2] If {rev} > {INTMAX} / {10} , then temp = {rev} * 10 + {pop}
      is guaranteed to overflow.
   3] If {rev} == {INTMAX} / {10}, then temp = rev⋅10+pop will overflow
       if and only if {pop} > 7
   Similar logic can be applied when {rev}rev is negative.
*/
int reverse2(int x) {
  int rev = 0;
  while (x != 0) {
    int pop = x % 10;
    x /= 10;
    if (rev > INT_MAX/10 || (rev == INT_MAX / 10 && pop > 7))
      return 0;
    if (rev < INT_MIN/10 || (rev == INT_MIN / 10 && pop < -8))
      return 0;
    rev = rev * 10 + pop;
  }
  return rev;
}

/**
   Complexity Analysis:
   Time Complexity: O(log(x)). There are roughly log10(X) digits in x.
   Space Complexity: O(1).
*/

/**
   We want to repeatedly "pop" the last digit off of x and "push"
   it to the back of the rev. In the end, rev
   will be the reverse of the xx.

   To "pop" and "push" digits without the help of some auxiliary
   stack/array, we can use math.

   //pop operation:
   pop = x % 10;
   x /= 10;
*/
int reverseInteger(int x) {
  int ans = 0;
  while (x) {
    int temp = ans * 10 + x % 10;
    printf ("\nx %% 10 = %d temp = %d ans = %d\n", (x%10), temp, ans);
    printf ("(temp / 10) = %d\t", (temp / 10));

    if (temp / 10 != ans)
      return 0;
    ans = temp;
    x /= 10;
    printf ("x= %d ans = %d\n", x, ans);
  }
  return ans;
}

int main() {
  printf("\n");
  debug(" Reverse Int = %d ", reverseInteger(321));

  return 0;
}

/***
    => ./a.out

    x % 10 = 1 temp = 1 ans = 0
    (temp / 10) = 0	x= 32 ans = 1

    x % 10 = 2 temp = 12 ans = 1
    (temp / 10) = 1	x= 3 ans = 12

    x % 10 = 3 temp = 123 ans = 12
    (temp / 10) = 12	x= 0 ans = 123

    [main] L=133 : Reverse Int = 123
*/
