/***
    https://leetcode.com/problems/perfect-number
    507. Perfect Number

    A perfect number is a positive integer that is equal to the
    sum of its positive divisors, excluding the number itself.
    A divisor of an integer x is an integer that can divide x evenly.

    Given an integer n, return true if n is a perfect number,
    otherwise return false.

    Input: num = 28
    Output: true
    Explanation: 28 = 1 + 2 + 4 + 7 + 14
    1, 2, 4, 7, and 14 are all divisors of 28.

    Input: num = 7
    Output: false

    Constraints:
    1 <= num <= 108

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 12/21/2021
    Folsom, CA.
*/

/*----------------------------------- Header --------------------------------------*/
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

/*----------------------------------- Micro --------------------------------------*/
#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)
#define atsizeof(object) (char *)(&object+1) - (char*)(&object)
#define arrsz(x)  (sizeof(x) / sizeof((x)[0]))
#define max(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a > _b ? _a : _b; })
#define min(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

bool checkPerfectNumber(int num) {
  int sum = 1;
  if(1 == num)
    return false;
  for(int i=2; i<=sqrt(num); i++) {
    if(num%i==0) {
      sum += i;
      int t = num/i;
      if(t!=i)
	sum += t;
    }
  }
  return num == sum;
}

bool checkPerfectNumber_(int num) {
  if(num == 1)
    return false;
  int temp = 1;
  for(int i = 2; i*i < num; i++) {
    if(num % i == 0) {
      temp += i + num/i;
    }
  }
  return(temp == num);
}

int main (int argc, char **argv) {
  int ret = 0;

  ret = checkPerfectNumber(28);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=86 :Output = 1
**/
