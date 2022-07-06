/***
    Calculate Fibonacci series using Dynamic Programming
    What is the 50th number in the Fibonacci series?

    https://www.youtube.com/watch?v=oBt53YbR9Kk&list=LL&index=35&t=7s
    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 29 Jan 2022
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

unsigned long long fib(int n, unsigned long long *memo) {
  if (memo[n])
    return memo[n];

  if (n <= 2)
    return 1;

  memo[n] = fib(n-1, memo) + fib(n-2, memo);
  return memo[n];
}

/**
    Takes 1 Minute on My System
    => cat /proc/cpuinfo  | grep 'name'| uniq
    model name	: Intel(R) Core(TM) i7-8550U CPU @ 1.80GHz
**/
unsigned long long int fib_50(unsigned n) {
  if (n <= 2)
    return 1;
  return fib_50(n-1) + fib_50(n-2);
}


int fib_leetcode(int n) {
  if (n == 0)
    return 0;

  if(n == 1 || n == 2)
    return 1;

  return fib_leetcode(n-1) + fib_leetcode(n-2);
}

void test() {
  unsigned long long int ret = 0;
  ret = fib_50(50);
  debug("Output  = %llu ", ret);
}

void test2() {
  int N = 50;
  unsigned long long ret = 0;
  unsigned long long* memo = (unsigned long long *)malloc(sizeof(unsigned long long) * (N + 1));
  //  int* memo = (int *)calloc(56, sizeof(int));
  ret = fib(N, memo);
  debug("Output = %llu ", ret);
}

void test3() {
  int ret = fib_leetcode(2);
  debug("Output = %d ", ret);
}

int main (int argc, char **argv) {
  //  test();
  test2();
  test3();
  return 0;
}

/**
   [test] L=54 :Output  = 12586269025
   [test2] L=61 :Output = 12586269025
**/
