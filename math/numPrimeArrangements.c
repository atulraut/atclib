/***
    https://leetcode.com/problems/prime-arrangements/
    175. Prime Arrangements

    Return the number of permutations of 1 to n so that
    prime numbers are at prime indices (1-indexed.)

    (Recall that an integer is prime if and only if it is
    greater than 1, and cannot be written as a product of
    two positive integers both smaller than it.)

    Since the answer may be large, return the answer modulo 10^9 + 7.

    Input: n = 5
    Output: 12
    Explanation: For example [1,2,5,4,3] is a valid permutation,
    but [5,2,3,4,1] is not because the prime number 5 is at index 1.

    Input: n = 100
    Output: 682289015

    Constraints:
    1 <= n <= 100

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 2 Jan 2022
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

long int fact(long int a) {
  if(a==0 || a==1)
    return 1;
  else {
    long int f=a;
    f=f*fact(a-1);

    return f%(1000000007);
  }
}

bool isPrime(long int a) {
  long int i;
  if(a==1)
    return false;
  long int flg=0;
  for(i=2; i*i<=a; i++) {
    if(a%i==0)
      flg++;
  }
  if(flg==0)
    return true;
  else
    return false;
}

int numPrimeArrangements(int n){
  long int i,count=0;
  for(i=1;i<=n;i++)
    if(isPrime(i))
      count++;

  // printf("Count : %d, rem : %d",count,n-count);
  return (fact(count)*fact(n-count))%(1000000007);
}

int main (int argc, char **argv) {
  int ret = 0;

  ret = numPrimeArrangements(5);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=97 :Output = 12
**/
