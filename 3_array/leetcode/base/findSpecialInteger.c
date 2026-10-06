/***
    https://leetcode.com/problems/element-appearing-more-than-25-in-sorted-array/
    Element Appearing More Than 25% In Sorted Array

    Given an integer array sorted in non-decreasing order, there
    is exactly one integer in the array that occurs more than 25%
    of the time, return that integer.

    Input: arr = [1,2,2,6,6,6,6,7,10]
    Output: 6

    Input: arr = [1,1]
    Output: 1

    Constraints:
    1 <= arr.length <= 104
    0 <= arr[i] <= 105

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address findSpecialInteger.c -lm

    Date: 27 Oct 2021
    Fair Oaks, CA.
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
  ({ typeof (a) _a = (a);	\
    typeof (b) _b = (b);	\
    _a > _b ? _a : _b; })
#define min(a,b)		\
  ({ typeof (a) _a = (a);	\
    typeof (b) _b = (b);	\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

int findSpecialInteger(int* arr, int arrSize) {
  int result = arr[0];
  int count = 1;
  for(int index = 1; index < arrSize; index++) {
    if(arr[index] != arr[index - 1]) {
      if(((float)count / (float)arrSize) > 0.25f) {
	debug ("More than --> = %f", (float)((float)count / (float)arrSize) );
	break;
      }
      result = arr[index];
      count = 0;
    }
    count++;
  }
  return result;
}

int findSpecialInteger2(int* arr, int arrSize) {
  int step      = arrSize/4 + 1;
  int threshold = arrSize/4;

  for (int i = 0; i < arrSize; i += step) {
    int c = arr[i];

    // Find lower limit
    int l = 0;
    int r = i - 1;

    while (l <= r) {
      int m = (l + r)/2;
      if (arr[m] >= c) r = m - 1;
      else             l = m + 1;
    }

    int lower = l;

    // Find upper limit
    l = i + 1;
    r = arrSize - 1;

    while (l <= r) {
      int m = (l + r)/2;
      if (arr[m] <= c) l = m + 1;
      else             r = m - 1;
    }

    int upper = r;

    // Calculate length
    int len   = upper - lower + 1;

    // If length > 25% return c
    if (len > threshold) return c;
  }

  assert(false);
  return 0;
}

int main (int argc, char **argv) {
  int ret = 0;
  int arr[] = {1,2,2,6,6,6,6,7,10};
  int arrSize = sizeof(arr)/sizeof(arr[0]);;

  ret = findSpecialInteger(arr, arrSize);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [findSpecialInteger] L=57 :More than --> = 0.444444
   [main] L=100 :Output = 6
**/
