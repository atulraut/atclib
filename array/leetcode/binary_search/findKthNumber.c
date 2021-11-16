/***
    https://leetcode.com/problems/kth-smallest-number-in-multiplication-table/
    Nearly everyone has used the Multiplication Table.
    The multiplication table of size m x n is an integer
    matrix mat where mat[i][j] == i * j (1-indexed).

    Given three integers m, n, and k, return the kth
    smallest element in the m x n multiplication table.

    Input: m = 3, n = 3, k = 5
    Output: 3
    Explanation: The 5th smallest number is 3.

    Input: m = 2, n = 3, k = 6
    Output: 6
    Explanation: The 6th smallest number is 6.


    Constraints:
    1 <= m, n <= 3 * 104
    1 <= k <= m * n

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address findKthNumber.c -lm

    Date: 11/15/2021
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
#define max(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a > _b ? _a : _b; })
#define min(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

int count(int m, int n, int x) {
  int count = 0;
  for(int i = 1; i <= m; i++)
    count += n < x/i ? n : x/i;
  return count;
}

int findKthNumber(int m, int n, int k) {
  int start = 1, end = m * n + 1;
  while(start < end) {
    int mid = (start + end) / 2;
    if(count(m, n, mid) >= k)
      end = mid;
    else
      start = mid + 1;
  }
  return start;
}

int main (int argc, char **argv) {
  int ret = 0;
  int m=3;
  int n=3;
  int k=5;

  ret =  findKthNumber(m, n, k);
  debug("Output = %d", ret);
  return 0;
}

/**
   [main] L=61 :Output = 3
**/
