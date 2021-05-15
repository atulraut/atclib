/***
    Easy: 204. Count Primes
    https://leetcode.com/problems/count-primes/submissions/

    Count the number of prime numbers less than a non-negative number, n.

    Input: n = 10
    Output: 4
    Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.

    Input: n = 0
    Output: 0

    Input: n = 1
    Output: 0

    Constraints:
    0 <= n <= 5 * 106

    Date: 11 May 2021
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

int countPrimes(int n) {
  if((n-1) < 2) return 0;

  bool *isPrime = malloc(sizeof(bool) * n);
  memset(isPrime, true, n);

  int primeCount = 1 ; // 2 is the only even number that is a prime

  for(int i = 3; i < n; i = i+2) { // only odd numbers can be primes

    if(isPrime[i]) { //is a prime number
      primeCount++;
      //sieve all multiples
      for(int j = i; j < n; j = j+i) {
	isPrime[j] = false;
      }
    }
  }
  return primeCount
}

int main () {
  int ret = 0;
  int n = 10;

  ret =  countPrimes(n);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=63 :Output = 4
**/
