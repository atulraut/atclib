#include <stdio.h>
#include <stdlib.h>

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

int multiply(int x, int y) {
  debug(" x = %d y = %d", x, y);

  if (y == 0)
    return 0;

  if(y > 0)
    return (x + multiply(x, y-1));

  if(y < 0)
    return -multiply(x, -y);
}

/**
   Function to swap adjacent bits of a given number
   How does this work ?
   The value of a*b is same as (a*2)*(b/2) if b is even, otherwise the value is
   same as ((a*2)*(b/2) + a). In the while loop, we keep multiplying ‘a’ with 2
   and keep dividing ‘b’ by 2. If ‘b’ becomes odd in loop, we add ‘a’ to ‘res’.
   When value of ‘b’ becomes 1, the value of ‘res’ + ‘a’, gives us the result.
   Note that when ‘b’ is a power of 2, the ‘res’ would remain 0 and ‘a’ would
   have the multiplication. See the reference for more information.
**/
unsigned int russianPeasant(unsigned int a, unsigned int b) {
  int res = 0;  // initialize result
  // While second number doesn't become 1
  while (b > 0)  {
    // If second number becomes odd, add the first number to result
    if (b & 1) {
      res = res + a;
      debug ("a = %d b = %d res = %d ", a, b, res);
    }
    // Double the first number and halve the second number
    a = a << 1;
    b = b >> 1;
    debug ("a = %d b = %d res = %d ", a, b, res);
  }
  return res;
}

int main () {
  debug ("multiplication --> %d ", multiply(5, -11));
  debug("o/p = %d \n", russianPeasant(2, 4) );
}

/***
    => ./a.out
    [multiply] L=7 : x = 5 y = -11
    [multiply] L=7 : x = 5 y = 11
    [multiply] L=7 : x = 5 y = 10
    [multiply] L=7 : x = 5 y = 9
    [multiply] L=7 : x = 5 y = 8
    [multiply] L=7 : x = 5 y = 7
    [multiply] L=7 : x = 5 y = 6
    [multiply] L=7 : x = 5 y = 5
    [multiply] L=7 : x = 5 y = 4
    [multiply] L=7 : x = 5 y = 3
    [multiply] L=7 : x = 5 y = 2
    [multiply] L=7 : x = 5 y = 1
    [multiply] L=7 : x = 5 y = 0
    [main] L=47 :multiplication --> -55
    [russianPeasant] L=41 :a = 4 b = 2 res = 0
    [russianPeasant] L=41 :a = 8 b = 1 res = 0
    [russianPeasant] L=36 :a = 8 b = 1 res = 8
    [russianPeasant] L=41 :a = 16 b = 0 res = 8
    [main] L=48 :o/p = 8
*/

/**
   Given this equation: multiplier × multiplicand = product ,
   Algorithm :
   Set product to 0.
   If multiplier is odd, add multiplicand to product.
   Halve multiplier (i.e., divide it by 2) and double multiplicand (i.e., multiply it by 2).
   Note that integer division is used, so remainders are discarded.
   Repeat steps 2 and 3 until multiplier reaches 1
   Ref : https://montcs.bloomu.edu/~bobmon/Semesters/2011-09/240/rpmultiplication/
**/
