/***
    Medium: 970. Powerful Integers
    Given three integers x, y, and bound, return a list of all the
    powerful integers that have a value less than or equal to bound.
    An integer is powerful if it can be represented as xi + yj for
    some integers i >= 0 and j >= 0.
    You may return the answer in any order. In your answer, each
    value should occur at most once.

    Input: x = 2, y = 3, bound = 10
    Output: [2,3,4,5,7,9,10]
    Explanation:
    2 = 20 + 30
    3 = 21 + 30
    4 = 20 + 31
    5 = 21 + 31
    7 = 22 + 31
    9 = 23 + 30
    10 = 20 + 32

    Input: x = 3, y = 5, bound = 15
    Output: [2,4,6,8,10,14]

    Constraints:
    1 <= x, y <= 100
    0 <= bound <= 106

    https://leetcode.com/problems/powerful-integers/
    Date:
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

int cmpfunc (const void * a, const void * b) {
  return ( *(int*)a - *(int*)b );
}

/* Call to call Free */
int* powerfulIntegers(int x, int y, int bound, int* returnSize) {

  int px=1,py=1,count=0;
  int *N = (int *)malloc((bound+1)*sizeof(int));

  // Solve special case when x=1 and y=1
  if(x==1 && y==1) {
    if(bound>1) {
      N[0]=2;
      *returnSize = 1;
      return N;
    }
    *returnSize = 0;
    return N;
  }

  // Brute Force
  for(px=1;px+py<=bound;px*=x) {
    for(py=1;px+py<=bound;py*=y) {
      N[count++] = px+py;
      printf("%d ",px+py);
      if(y==1) break;  // avoid infinite loop 1->1*1*1....
    }
    py=1;
    if(x==1) break;  // avoid infinite loop 1->1*1*1....
  }

  // Sort Array using Quick Sort
  qsort(N, count, sizeof(int), cmpfunc);

  // Remove duplicates from sorted Array
  int i,k=0;
  for(i=0;i<count-1;i++) {
    if(N[i] != N[i+1]) {
      N[k] = N[i];
      k++;
    }
  }
  N[k]=N[count-1];

  *returnSize = k+1;
  return N;
}

int main () {
  int x = 3;
  int y = 5;
  int bound = 15;
  int returnSize;

  int*ret = powerfulIntegers(x, y, bound, &returnSize);

  printf("\n");
  for(int i=0; i<returnSize; i++)
    debug("Output = %d", ret[i]);
  free(ret);
  return 0;
}

/**
   => ./a.out
   2 6 4 8 10 14
   [main] L=103 :Output = 2
   [main] L=103 :Output = 4
   [main] L=103 :Output = 6
   [main] L=103 :Output = 8
   [main] L=103 :Output = 10
   [main] L=103 :Output = 14
**/
