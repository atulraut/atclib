/***

    Quick Sort
    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Thu 13 Mar 2025 06:17:31 PM PDT
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

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

int partition(int *arr, int start, int end) {

  int pivot = arr[end];
  // int pivot = (rand() % (end - start + 1)) + start; // NOT Working

  int partitionIndex = start; // set partition index as start initially
  for (int i=start; i<end; i++) {
    if (arr[i] <= pivot) {
      swap(arr+i, arr+partitionIndex);
      partitionIndex++;
    }
  }
  swap(&arr[partitionIndex], &arr[end]); // swap pivot with element as partition index
  return partitionIndex;
}

void quick_sort_atclib(int *arr, int start, int end) {
  if(start < end) {
    int partitionIndex = partition(arr, start, end);
    quick_sort_atclib(arr, start, partitionIndex-1);
    quick_sort_atclib(arr, partitionIndex+1, end);
  }
}

int *quick_sort(int *arr, int end) {

  int start = 0;
  quick_sort_atclib(arr, start, end);
  return arr;
}

void test() {

  int arr[] = {3, 5, 2, 1, 4};
  int k = 5;
  int *ret = quick_sort(arr, k);
  for (int i=0; i<k; ++i)
    debug("[%d]->[%d]", i, arr[i]);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   L=[68][1_quickSort.c]->[test] :| [0]->[1]
   L=[68][1_quickSort.c]->[test] :| [1]->[2]
   L=[68][1_quickSort.c]->[test] :| [2]->[3]
   L=[68][1_quickSort.c]->[test] :| [3]->[4]
   L=[68][1_quickSort.c]->[test] :| [4]->[5]
**/
