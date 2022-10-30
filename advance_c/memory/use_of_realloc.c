/***
    https://www.geeksforgeeks.org/g-fact-66/

    Size of dynamically allocated memory can be changed by using realloc().

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Sat Oct 29 07:14:30 AM PDT 2022
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

void test_realloc1() {

  int *ptr = (int *)malloc(sizeof(int)*2);
  int *ptr_new;

  *ptr = 10;
  *(ptr + 1) = 20;

  // Same Object allocate again
  ptr = (int *)realloc(ptr, sizeof(int)*3);
  *(ptr + 2) = 30;

  debug("Test Init!");
  for(int i = 0; i < 3; i++)
    debug("%d ", *(ptr + i));
}

void test_realloc0() {

  int *ptr = (int *)malloc(sizeof(int)*2);
  int *ptr_new;

  *ptr = 10;
  *(ptr + 1) = 20;

  // New Object to allocate
  ptr_new = (int *)realloc(ptr, sizeof(int)*3);
  *(ptr_new + 2) = 30;

  debug("Test Init!");
  for(int i = 0; i < 3; i++)
    debug("%d ", *(ptr_new + i));
}

int main (int argc, char **argv) {
  test_realloc1();
  return 0;
}

/**
   [Test_realloc] L=54 :Test Init!                                                                      [test_realloc] L=56 :10                                                                              [test_realloc] L=56 :20                                                                              [test_realloc] L=56 :30
**/
