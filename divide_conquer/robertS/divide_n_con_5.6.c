/***
    This is Sample code from Algo in C by Robert S. Purchased Legal Copy

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date:
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

static int cnt = 0;

int max_array (int *arr, int l, int r) {
  int u, v;
  ++cnt;
  int m = (l+r)/2;

  debug ("<<<----------  cnt = %d ---------->>>", cnt);
  if (l == r) {
    debug ("Return-> l=%d m=%d r = %d val=%d", l, m, r, arr[l]);
    return arr[l];
  }

  debug ("l = %d r = %d m = %d", l, r, m);
  u = max_array (arr, l, m);
  debug ("l = %d r = %d m = %d u = %d", l, r, m, u);
  v = max_array (arr, m+1, r);
  debug ("l = %d r = %d m = %d u = %d v = %d", l, r, m, u, v);
  if (u>v) {
    debug ("l = %d r = %d m = %d u = %d v = %d", l, r, m, u, v);
    return u;
  } else {
      debug ("l = %d r = %d m = %d u = %d v = %d", l, r, m, u, v);
      return v;
    }
}

void test() {
  int ret = 0;
  // int arr[] = {3, 2, 1};
  int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  ret = max_array(arr, 0, 10);

  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   ~/dev/c/to_push/atclib $ ./a.out
   [max_array] L=42 :<<<----------  cnt = 1 ---------->>>
   [max_array] L=48 :l = 0 r = 2 m = 1
   [max_array] L=42 :<<<----------  cnt = 2 ---------->>>
   [max_array] L=48 :l = 0 r = 1 m = 0
   [max_array] L=42 :<<<----------  cnt = 3 ---------->>>
   [max_array] L=44 :Return-> l=0 m=0 r = 0 val=3
   [max_array] L=50 :l = 0 r = 1 m = 0 u = 3
   [max_array] L=42 :<<<----------  cnt = 4 ---------->>>
   [max_array] L=44 :Return-> l=1 m=1 r = 1 val=2
   [max_array] L=52 :l = 0 r = 1 m = 0 u = 3 v = 2
   [max_array] L=54 :l = 0 r = 1 m = 0 u = 3 v = 2
   [max_array] L=50 :l = 0 r = 2 m = 1 u = 3
   [max_array] L=42 :<<<----------  cnt = 5 ---------->>>
   [max_array] L=44 :Return-> l=2 m=2 r = 2 val=1
   [max_array] L=52 :l = 0 r = 2 m = 1 u = 3 v = 1
   [max_array] L=54 :l = 0 r = 2 m = 1 u = 3 v = 1
   [test] L=67 :Output = 3
   ~/dev/c/to_push/atclib $
**/
