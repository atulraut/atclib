/*
  bubble sort : Compair two consecutive element for every
  pass & if greater the first element than previous swap it.
  Fix bubble sort.
  Date: Sat Aug 27 12:17:05 PM PDT 2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

/***
 * Algorithm : The Bubble Sort
 * for i:= 1 to n-1
 *     for j:= 1 to n-1
 *         if aj > aj+1 then interchange(swap) aj and aj+1
 * {a1,.....,an is in increasing order}
 */

void swap (int* a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

int bubble_sort (int* arr, int sz) {
  for (int i=0; i<sz; ++i) {
    for (int red=sz-1; red>=i+1; --red) {
      if (arr[red-1] > arr[red]) {
	debug ("A: arr[%d]=%d arr[%d]=%d ", red-1, *(arr+red-1), red, *(arr+red));
	swap((arr+red-1), (arr+red));
	debug ("B: arr[%d]=%d arr[%d]=%d ", red-1, *(arr+red-1), red, *(arr+red));
      }
    }
  }
}

int bubble_sort2 (int* arr, int sz) {
  for (int i=0; i<sz; ++i) {
    for (int j=0; j<sz-i; ++j) {
      if (arr[j] > arr[j+1]) {
	swap((arr+j), (arr+j+1));
      }
    }
  }
}

void bubble_sort1 (int arr[], int sz) {
  int i = 0, j = 0;
  int temp = 0;
  int flag = 0; // if sorted array dont do computing.

  for (i=0; i<sz-1; i++) {
    flag = 0;
    for (j=0; j<sz-1; j++) {
      if (arr[j] > arr[j+1]) {
	flag = 1;
	temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
      }
    }
    if (0 == flag)
      break;
  }
}

int main () {
  int i = 0;
  int arr1[] = {9, 4, 8, 3, 1};
  int arr[] = {5, 1, 3, 4, 7, 8, 9};
  int sz = sizeof(arr)/sizeof(arr[0]);
  for (i=0; i<sz; i++) {
    debug ("->[%d]", arr[i]);
  }
  printf ("\n");
  bubble_sort (arr, sz);
  for (i=0; i<sz; i++) {
    debug ("->[%d]", arr[i]);
  }
  printf ("\n");
}

/***
    => ./a.out
    [main] L=73 :->[9]
    [main] L=73 :->[4]
    [main] L=73 :->[8]
    [main] L=73 :->[3]
    [main] L=73 :->[1]

    [bubble_sort] L=30 :A: arr[3]=3 arr[4]=1
    [bubble_sort] L=32 :B: arr[3]=1 arr[4]=3
    [bubble_sort] L=30 :A: arr[2]=8 arr[3]=1
    [bubble_sort] L=32 :B: arr[2]=1 arr[3]=8
    [bubble_sort] L=30 :A: arr[1]=4 arr[2]=1
    [bubble_sort] L=32 :B: arr[1]=1 arr[2]=4
    [bubble_sort] L=30 :A: arr[0]=9 arr[1]=1
    [bubble_sort] L=32 :B: arr[0]=1 arr[1]=9
    [bubble_sort] L=30 :A: arr[3]=8 arr[4]=3
    [bubble_sort] L=32 :B: arr[3]=3 arr[4]=8
    [bubble_sort] L=30 :A: arr[2]=4 arr[3]=3
    [bubble_sort] L=32 :B: arr[2]=3 arr[3]=4
    [bubble_sort] L=30 :A: arr[1]=9 arr[2]=3
    [bubble_sort] L=32 :B: arr[1]=3 arr[2]=9
    [bubble_sort] L=30 :A: arr[2]=9 arr[3]=4
    [bubble_sort] L=32 :B: arr[2]=4 arr[3]=9
    [bubble_sort] L=30 :A: arr[3]=9 arr[4]=8
    [bubble_sort] L=32 :B: arr[3]=8 arr[4]=9
    [main] L=78 :->[1]
    [main] L=78 :->[3]
    [main] L=78 :->[4]
    [main] L=78 :->[8]
    [main] L=78 :->[9]
**/
