/***
    Radix Sort Algorithm
    Ref: DS by R. Thareja
    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Sun Sep  4 05:00:23 PM PDT 2022
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

int largest(int* arr, int n) {
  int large = arr[0];

  for (int i=1; i<n; ++i) {
    if (arr[i] > large)
      large = arr[i];
  }
  return large;
}

void radix_sort(int* arr, int n) {
  int bucket[10][10];
  int bucket_count[10];
  int i, j, k, remainder, NOP=0, divisor=1, large, pass;

  large = largest(arr, n);
  while (large>0) {
    ++NOP;
    large /= 10;
  }

  for (pass=0; pass<NOP; ++pass) {
    for (i=0; i<10; ++i)
      bucket_count[i] = 0;

    for (i=0; i<n; ++i) {
      remainder = (arr[i]/divisor) % 10;
      bucket[remainder][bucket_count[remainder]] = arr[i];
      bucket_count[remainder] += 1;
    }
    i = 0;
    for (k=0; k<10; ++k) {
      for (j=0; j<bucket_count[k]; ++j) {
	arr[i] = bucket[k][j];
	++i;
      }
    }
    divisor *= 10;
  } // First For Loops Ends
} // radix_sort Ends

void test() {
  int ret = 0;
  int arr[] = {345, 654, 924, 123, 567, 472, 555, 808, 911};
  int n = sizeof(arr)/sizeof(arr[0]);
  radix_sort(arr, n);

  for (int i=0; i<n; ++i)
    debug("Output = %d", arr[i]);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [test] L=84 :Output = 123
   [test] L=84 :Output = 345
   [test] L=84 :Output = 472
   [test] L=84 :Output = 555
   [test] L=84 :Output = 567
   [test] L=84 :Output = 654
   [test] L=84 :Output = 808
   [test] L=84 :Output = 911
   [test] L=84 :Output = 924
**/
