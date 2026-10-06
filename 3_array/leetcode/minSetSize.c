/***
    https://leetcode.com/problems/reduce-array-size-to-the-half/

    Reduce Array Size to The Half

    You are given an integer array arr. You can choose a
    set of integers and remove all the occurrences of these
    integers in the array.

    Return the minimum size of the set so that at least
    half of the integers of the array are removed.

    Input: arr = [3,3,3,3,5,5,5,2,2,7]
    Output: 2
    Explanation: Choosing {3,7} will make the new array [5,5,5,2,2] which has size 5 (i.e equal to half of the size of the old array).
    Possible sets of size 2 are {3,5},{3,2},{5,2}.
    Choosing set {2,7} is not possible as it will make the new array [3,3,3,3,5,5,5] which has a size greater than half of the size of the old array.

    Input: arr = [7,7,7,7,7,7]
    Output: 1
    Explanation: The only possible set you can choose is {7}. This will make the new array empty.

    Constraints:
    2 <= arr.length <= 105
    arr.length is even.
    1 <= arr[i] <= 105

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Wed Aug 17 10:55:25 PM PDT 2022
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
struct am { int i; uint16_t o; };

int cmp(const void *x, const void *y) {
    return ((const struct am *)y)->o - ((const struct am *)x)->o;
}

int minSetSize(int* arr, int arrSize) {
    int i, sz = arrSize, n = 100001;
    struct am *m = calloc(1, sizeof(struct am[n]));
    for (int i = 0 ; i < sz ; m[arr[i]].i = arr[i], m[arr[i++]].o++);
    qsort(m, n, sizeof(struct am), cmp);
    for (int c = i = 0 ; i < n / 2 && sz - c > sz / 2 ; c += m[i++].o);
    return free(m), i;
}
void test() {
  int ret = 0;
  int arr[] = {3,3,3,3,5,5,5,2,2,7};
  int sz = arrsz(arr);
  ret = minSetSize(arr, sz);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   [test] L=90 :Output = 2
**/
