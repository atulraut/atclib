/***
    Discrete Mathematics and its Applications by Kenneth Rosen
    2.1-Algo 1:
    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Tue Jul 26 05:58:21 AM PDT 2022
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

/* Algo1: Find Max Elements */
void test1 () {
  int ret = 0;
  int arr[] = {1, 3, 4, 7, 2, 9};
  int arrSz = sizeof(arr)/sizeof(arr[0]);
  int max = arr[0];

  for (int i=1; i<arrSz; ++i) {
    if (arr[i] >= max)
      max = arr[i];
  }
  debug("Output ret = %d max = %d", ret, max);
}

/* Algo2: Linear Search */
void test2 () {
  int ret = 0;
  int arr[] = {1, 3, 4, 7, 2, 9};
  int arrSz = sizeof(arr)/sizeof(arr[0]);
  int i = 0;
  int x = 9;

  //  for (int j=0; j<arrSz; ++j) {
    while(i <= arrSz && x != arr[i]) {
      i += 1;
      if (i <= arrSz)
	ret = i;
      else
	ret = 0;
  }
    debug("Output ret = %d i =%d arr[i]=%d", ret, i, arr[i]);
}

int main (int argc, char **argv) {
  test1();
  test2();
  return 0;
}

/**
   [test] L=45 :Output ret = 0 max = 9
**/
