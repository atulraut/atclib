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
#define max(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a > _b ? _a : _b; })
#define min(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

/**
   wrong_use_of_realloc.c:47:20: warning: ‘realloc’ called on
   unallocated object ‘arr’ [-Wfree-nonheap-object]
**/
void test_wrong_realloc() {
  int arr[2], i;
  int *ptr = arr;
  int *ptr_new;

  arr[0] = 10;
  arr[1] = 20;

  // incorrect use of new_ptr: undefined behaviour
  ptr_new = (int *)realloc(ptr, sizeof(int)*3);
  *(ptr_new + 2) = 30;

  debug("Test Init!");
  for(i = 0; i < 3; i++)
    debug("%d ", *(ptr_new + i));
}

int main (int argc, char **argv) {
  test_wrong_realloc();
  return 0;
}

/**
   ~/dev/c/atclib/advance_c/memory $ ./a.out
   realloc(): invalid old size
   aborted (core dumped
**/
