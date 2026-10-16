/***
    https://leetcode.com/problems/search-insert-position/

    35. Search Insert Position

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Wed Oct 14 22:10:25 PDT 2026
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

// T - O(log n)
int searchInsert(int* nums, int numsSize, int target) {

  int start = 0;
  int end   = numsSize - 1;
  int mid = 0;

  while(start <= end) {

    mid = start + (end - start) / 2;
    if(nums[mid] == target)
      return mid;
    else if(nums[mid] > target)
      end = mid - 1;
    else
      start = mid + 1;
  }
  return start;
}

void test() {
  int ret = 0;
  int nums[] = {1, 3, 5, 6};
  int numsSize  = 4;
  int target = 5;
  ret = searchInsert(nums, numsSize, target);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   L=[50][2_binary_search_modified/0_searchInsert_LC-35.c]->[test] :| Output = 2
**/
