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

  Date: 11/23/1981
  Folsom, CA.
*/
#include <stdio.h>

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
    printf ("x%10 = %d temp = %d \t", (x%10), temp);
    if (temp / 10 != ans)
      return 0;
    ans = temp;
    x /= 10;
    printf ("\nx= %d \t", x);
  }
  return ans;
}

int main() {
  printf("\n Reverse Int = %d\n", reverseInteger(321));

  return 0;
}

/***
    x%10 = 1 temp = 1
    x= 32
    x%10 = 2 temp = 12
    x= 3
    x%10 = 3 temp = 123
    x= 0
    Reverse Int = 123
*/
