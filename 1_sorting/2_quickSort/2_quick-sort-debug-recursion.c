/***
    quick_sort with added debug logs to understand recursion.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Sun Mar 15 20:37:07 PDT 2026
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

static int cnt=0;
void display_array(int *arr) {
  cnt++;
  for (int i=0; i<8; ++i)
    debug ("cnt->[%d] [%d]->[%d]",cnt, i, arr[i]);
  debug("--------------------");
}

void swap (int* a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

int partition(int* arr, int start, int end) {

  int pivot = arr[end]; // start from last
  int pIndex = start;

  for (int i=start; i<end; ++i) {
    if (arr[i] <= pivot) {
      swap(&arr[i], &arr[pIndex]);
      ++pIndex;
    }
  }
  swap(&arr[pIndex], &arr[end]);
  return pIndex;
}

int quick_sort_atclib(int* arr, int start, int end) {

  if (start < end) {
    int pIndex = partition(arr, start, end);
    display_array(arr);
    quick_sort_atclib(arr, start, pIndex-1);
    quick_sort_atclib(arr, pIndex+1,   end);
  }
  return 0;
}

void quick_sort(int* arr, int sz) {

  int start = 0;
  int end   = sz-1;
  quick_sort_atclib(arr, start, end);
}

void test() {
  int arr[] = {7, 2, 1, 6, 8, 5, 3, 4};
  int sz = sizeof(arr)/sizeof(arr[0]);
  debug ("Size of array = %d", sz);
  quick_sort(arr, sz);
  for (int i=0; i<sz; ++i)
    debug("Output = %d", arr[i]);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   rt.c]->[display_array] :| cnt->[2] [6]->[7]

   L=[29][2_quick-sort.c]->[display_array] :| cnt->[2] [7]->[6]
   L=[30][2_quick-sort.c]->[display_array] :| --------------------
   L=[29][2_quick-sort.c]->[display_array] :| cnt->[3] [0]->[1]
   L=[29][2_quick-sort.c]->[display_array] :| cnt->[3] [1]->[2]
   L=[29][2_quick-sort.c]->[display_array] :| cnt->[3] [2]->[3]
   L=[29][2_quick-sort.c]->[display_array] :| cnt->[3] [3]->[4]
   L=[29][2_quick-sort.c]->[display_array] :| cnt->[3] [4]->[8]
   L=[29][2_quick-sort.c]->[display_array] :| cnt->[3] [5]->[5]
   L=[29][2_quick-sort.c]->[display_array] :| cnt->[3] [6]->[7]
   L=[29][2_quick-sort.c]->[display_array] :| cnt->[3] [7]->[6]
   L=[30][2_quick-sort.c]->[display_array] :| --------------------
   L=[29][2_quick-sort.c]->[display_array] :| cnt->[4] [0]->[1]
   L=[29][2_quick-sort.c]->[display_array] :| cnt->[4] [1]->[2]
   L=[29][2_quick-sort.c]->[display_array] :| cnt->[4] [2]->[3]
   L=[29][2_quick-sort.c]->[display_array] :| cnt->[4] [3]->[4]
   L=[29][2_quick-sort.c]->[display_array] :| cnt->[4] [4]->[5]
   L=[29][2_quick-sort.c]->[display_array] :| cnt->[4] [5]->[6]
   L=[29][2_quick-sort.c]->[display_array] :| cnt->[4] [6]->[7]
   L=[29][2_quick-sort.c]->[display_array] :| cnt->[4] [7]->[8]
   L=[30][2_quick-sort.c]->[display_array] :| --------------------
   L=[29][2_quick-sort.c]->[display_array] :| cnt->[5] [0]->[1]
   L=[29][2_quick-sort.c]->[display_array] :| cnt->[5] [1]->[2]
   L=[29][2_quick-sort.c]->[display_array] :| cnt->[5] [2]->[3]
   L=[29][2_quick-sort.c]->[display_array] :| cnt->[5] [3]->[4]
   L=[29][2_quick-sort.c]->[display_array] :| cnt->[5] [4]->[5]
   L=[29][2_quick-sort.c]->[display_array] :| cnt->[5] [5]->[6]
   L=[29][2_quick-sort.c]->[display_array] :| cnt->[5] [6]->[7]
   L=[29][2_quick-sort.c]->[display_array] :| cnt->[5] [7]->[8]
   L=[30][2_quick-sort.c]->[display_array] :| --------------------

   L=[78][2_quick-sort.c]->[test] :| Output = 1
   L=[78][2_quick-sort.c]->[test] :| Output = 2
   L=[78][2_quick-sort.c]->[test] :| Output = 3
   L=[78][2_quick-sort.c]->[test] :| Output = 4
   L=[78][2_quick-sort.c]->[test] :| Output = 5
   L=[78][2_quick-sort.c]->[test] :| Output = 6
   L=[78][2_quick-sort.c]->[test] :| Output = 7
   L=[78][2_quick-sort.c]->[test] :| Output = 8
**/
