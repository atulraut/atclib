/***

    Insertion Sort

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Thu 13 Mar 2025 05:38:01 PM PDT
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

/*
  AR :
  1. During each iteration first element inthe unsorted set is picked up
  & inserted into the correct position int the sorted set.
  1. Divide Array into 2 like below.
  ----------------------------------
  |  Sorted Array | Unsorted Array  |
  ----------------------------------
*/
void insertionSort(int* arr, int n) {
  // sort list[0] to list[n-1] in ascedning order
  for(int h=1; h<n; h++) {
    int key = arr[h];		/* I */
    int j=h-1; /* start comparing with previous item */
    while(j>=0 && key < arr[j]) { /*Copy Elememnt from Unsorted(list[j]) to Sorted Array (list[j+1])*/
      arr[j+1] = arr[j];	/* II */
      --j;
    }
    arr[j+1] = key; /* III - key will create hole, copy that at last*/
  }//end for
}//end

void test() {

  int ret[] = {3, 5, 4, 2, 1};
  int k=5;

  insertionSort(ret, k);
  for (int i=0; i<k; ++i)
    debug("[%d]->[%d]", i, ret[i]);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   L=[55][1_insertionSort.c]->[test] :| [0]->[1]
   L=[55][1_insertionSort.c]->[test] :| [1]->[2]
   L=[55][1_insertionSort.c]->[test] :| [2]->[3]
   L=[55][1_insertionSort.c]->[test] :| [3]->[4]
   L=[55][1_insertionSort.c]->[test] :| [4]->[5]
**/
