/***
    https://leetcode.com/problems/daily-temperatures/
    Daily Temperatures

    Given an array of integers temperatures represents the
    daily temperatures, return an array answer such that
    answer[i] is the number of days you have to wait after
    the ith day to get a warmer temperature. If there is
    no future day for which this is possible, keep
    answer[i] == 0 instead.

    Input: temperatures = [73,74,75,71,69,72,76,73]
    Output: [1,1,4,2,1,1,0,0]

    Input: temperatures = [30,40,50,60]
    Output: [1,1,1,0]

    Input: temperatures = [30,60,90]
    Output: [1,1,0]

    Constraints:

    1 <= temperatures.length <= 105
    30 <= temperatures[i] <= 100

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 13 Nov 2021
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

int* dailyTemperatures(int* temperatures, int temperaturesSize, int* returnSize) {
  int* ans = calloc(temperaturesSize, sizeof(int));
  *returnSize = temperaturesSize;
  int stack[temperaturesSize], top = -1;

  for(int i = 0; i < temperaturesSize; i++) {
    while (top != -1 && temperatures[i] > temperatures[stack[top]]) {
      ans[stack[top]] = i - stack[top];
      top--;
    }
    stack[++top] = i;
  }

  return ans;
}

int main (int argc, char **argv) {
  int *ret;
  int temperatures[] = {30,40,50,60};
  int temperaturesSize = sizeof(temperatures)/sizeof(temperatures[0]);
  int returnSize;

  ret = dailyTemperatures(temperatures, temperaturesSize, &returnSize);
  for (int i=0; i<returnSize; ++i)
    debug("Output = %d", ret[i]);
  return 0;
}

/**
   => ./a.out
   [main] L=82 :Output = 1
   [main] L=82 :Output = 1
   [main] L=82 :Output = 1
   [main] L=82 :Output = 0
**/
