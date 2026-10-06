/***
    Merge Sort : IK

    Ref: https://www.youtube.com/watch?v=TzeBrDU-JaY&t=388s
    Ref: https://leetcode.com/problems/sort-an-array/discuss/842439/merge-sort-implementation-in-c
    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Mon Aug 29 08:40:44 PM PDT 2022
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

void merge(int *nums, int start, int end, int *auxilary_array) {
  int mid = (start + end) / 2;

  int i = start;
  int j = mid+1;
  int k = start;

  /* 3_IK: Gather/Merge Phase */
  while(i <= mid && j <= end) {
    if(nums[i] < nums[j])
      auxilary_array[k++] = nums[i++];
    else
      auxilary_array[k++] = nums[j++];
  }

  while(i <= mid)
    auxilary_array[k++] = nums[i++];
  while(j <= end)
    auxilary_array[k++] = nums[j++];

  debug ("Ouput Merge Sort");
  for (int i=start; i<end; ++i)
    debug("auxilary_array[%d] = %d", i, auxilary_array[i]);

  /* Copy auxilary_array to original array */
  for(int i=start; i<=end; i++) {
    nums[i] = auxilary_array[i];
  }
}

void mergeSort(int *nums, int start, int end, int *auxilary_array) {
  /* 1_IK: Leaf Worker */
  if(start >= end)
    return;

  /* 2_IK: Inernal Node Worker */
  //Follow 3 steps
  //1. Divide
  int mid = (start + end) / 2;

  //2. Recursively the arrays start, mid and mid+1, end
  mergeSort(nums, start, mid, auxilary_array);
  mergeSort(nums, mid+1, end, auxilary_array);

  //3. Merge the 2 parts
  merge(nums, start, end, auxilary_array);
}

int* sortArray(int* nums, int numsSize, int* returnSize) {
  int start = 0;
  int end   = numsSize-1;

  int *auxilary_array = (int*)malloc(sizeof(int) * (end+1) );

  mergeSort(nums, start, end, auxilary_array);

  *returnSize = numsSize;
  return nums;
}

void test() {
  int ret = 0;
  int arr[] = {5, 2, 1, 4, 3};
  int start = 0;
  int end = 4;

  int* auxilary_array = (int *)calloc(sizeof(int), (end+1));

  debug ("Input Merge Sort");
  for (int i=0; i<5; ++i)
    debug("arr[%d] = %d", i, arr[i]);

  mergeSort (arr, start, end, auxilary_array);

  debug ("Ouput Merge Sort");
  for (int i=0; i<5; ++i)
    debug("arr[%d] = %d", i, arr[i]);

  free(auxilary_array);
  auxilary_array = NULL;
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [test] L=104 :Input Merge Sort
   [test] L=106 :arr[0] = 5
   [test] L=106 :arr[1] = 2
   [test] L=106 :arr[2] = 1
   [test] L=106 :arr[3] = 4
   [test] L=106 :arr[4] = 3
   [merge] L=56 :Ouput Merge Sort
   [merge] L=58 :auxilary_array[0] = 2
   [merge] L=56 :Ouput Merge Sort
   [merge] L=58 :auxilary_array[0] = 1
   [merge] L=58 :auxilary_array[1] = 2
   [merge] L=56 :Ouput Merge Sort
   [merge] L=58 :auxilary_array[3] = 3
   [merge] L=56 :Ouput Merge Sort
   [merge] L=58 :auxilary_array[0] = 1
   [merge] L=58 :auxilary_array[1] = 2
   [merge] L=58 :auxilary_array[2] = 3
   [merge] L=58 :auxilary_array[3] = 4
   [test] L=110 :Ouput Merge Sort
   [test] L=112 :arr[0] = 1
   [test] L=112 :arr[1] = 2
   [test] L=112 :arr[2] = 3
   [test] L=112 :arr[3] = 4
   [test] L=112 :arr[4] = 5
**/
