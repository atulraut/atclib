/***
    https://leetcode.com/problems/find-peak-element/description/

    162. Find Peak Element

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Wed Oct 14 20:19:04 PDT 2026

    Folsom, CA.
 */

/*----------------------------------- Header --------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h> // va_arg
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */

#define debug(str,args...) printf("L=[%d][%s]->[%s] :| "str"\n",__LINE__,__FILE__, __func__, ##args)

int findPeak(int* nums, int start, int end) {
  while (start < end) {
    int mid = start + (end - start) / 2;

    if (nums[mid] > nums[mid + 1]) {
      // Descending slope: peak exists on left,
      // possibly at mid itself.
      end = mid;
    } else {
      // Ascending slope: peak exists on right.
      start = mid + 1;
    }
  }

  return start;
}

/* Compiler error
int findPeak_Error(int* nums, int start, int end) {

  int mid = 0;
  while (start <= end) {

    mid = start + (end - start) / 2;
    if (nums[mid-1] < nums[mid] > nums[mid+1])
      return mid;
    else if(nums[mid-1] < nums[mid] > nums[mid+1]) // peak is either side
      end = mid -1;
    else if(nums[mid-1] < nums[mid] < nums[mid+1]) // peak is rhs
      start = mid+1;
    else
      start = mid + 1;
  }
  return -1;
}
*/
int findPeakElement(int* nums, int numsSize) {
  return findPeak(nums, 0, numsSize-1);
}

void test() {
  int ret = 0;
  int nums[]= {1, 2, 3, 1};
  int numsSize = 4;
  ret = findPeakElement(nums, numsSize);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   L=[73][2_binary_search_modified/2_find_peak_element_LC-162.c]->[test] :| Output = 2
**/
