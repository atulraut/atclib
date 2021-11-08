/***
    https://leetcode.com/problems/unique-binary-search-trees
    Unique Binary Search Trees

    Given an integer n, return the number of structurally unique BST's
    (binary search trees) which has exactly n nodes of unique values from 1 to n.

    Input: n = 3
    Output: 5

    Input: n = 1
    Output: 1

    Constraints:
    1 <= n <= 19

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address numTrees.c -lm

    Date: 8 Nov 2021
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

int numTrees(int n) {
  int cache[n+1];
  for (int x = 0; x < n+1; x++) {
    if (x == 0) {
      cache[x] = 1;
      continue;
    }

    int total = 0;
    for (int i = 1; i < x+1; i++) {
      total += cache[i-1] * cache[x-i];
    }

    cache[x] = total;
  }

  return cache[n];
}

int numTrees2(int n) {
  if(n==0)
    return 0;
  int R[n+1];
  R[0] = 0;
  R[1] = 1;
  int i,j;
  for(i = 2; i <= n; i++) {
    R[i]=2*R[i-1];
    for(j = 2; j < i; j++)
      R[i]+=R[j-1]*R[i-j];
  }
  return R[n];
}


int main (int argc, char **argv) {
  int ret = 0;
  int n = 3;

  ret = numTrees(n);
  debug("Output = %d", ret);
  return 0;
}

/**
   ~/dev/c/atclib $ ./a.out
   [main] L=89 :Output = 5
**/
