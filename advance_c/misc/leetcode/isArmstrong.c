/***
    1134. Armstrong Number
    Given an integer n, return true if and only if it is an Armstrong number.
    The k-digit number n is an Armstrong number if and only if the
    kth power of each digit sums to n.

    Input: n = 153
    Output: true
    Explanation: 153 is a 3-digit number, and 153 = 13 + 53 + 33.

    Input: n = 123
    Output: false
    Explanation: 123 is a 3-digit number, and 123 != 13 + 23 + 33 = 36.

    https://leetcode.com/problems/armstrong-number/

    gcc -o main isArmstrong.c -lm

    Date: July 19, 2021
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

bool isArmstrong(int n){
  int init = n, result = 0;
  int count = 0;
  while(n){
    n /= 10;
    count++;
    printf ("n = %d cnt = %d \n",n, count);
  }
  n = init;
  while(n) {
    result += pow(n%10, count);
    n /= 10;
    printf ("n=%d result=%d \n", n, result);
  }
  printf ("init=%d result=%d \n", init, result);
  return init == result;
}

int main () {
  bool ret = 0;
  int n = 153;

  ret = isArmstrong(n);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=65 :Output = 1
**/
