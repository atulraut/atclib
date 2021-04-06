/*
  Largest Unique Number
  Given an array of integers A, return the largest integer that
  only occurs once.
  If no integer occurs once, return -1.

  Input: [5,7,3,9,4,9,8,3,1]
  Output: 8
  Explanation:
  The maximum integer in the array is 9 but it is repeated.
  The number 8 occurs only once, so it's the answer.

  Input: [9,9,8,8]
  Output: -1
  Explanation:
  There is no number that occurs only once.

  Note:
  1 <= A.length <= 2000
  0 <= A[i] <= 1000

  Date: 3/4/21
  San Diego, CA
  Author : Atul Raut
*/
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

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

struct stateType {
  bool visit:1;    /* visit has value between less than 10, so 1 bits is used to store value in memory */
  int freq:31;     /* 2^31 - Holds value 2,147,483,648 so 31 bits is used to store value in memory */
};

void insertionSort(int list[], int n) {
  // sort list[0] to list[n-1] in ascedning order
  for(int h=1; h<n; h++) {
    int key = list[h];		/* I */
    int j=h-1; /* start comparing with previous item */
    while(j>=0 && key < list[j]) { /*Copy Elememnt from Unsorted(list[j]) to Sorted Array (list[j+1])*/
      list[j+1] = list[j];	/* II */
      --j;
    }
    list[j+1] = key; /* III - key will create hole, copy that at last*/
  }//end for
}//end insertionSort

/**
   Algo :
   I: Sort list
   II: Get Freq. for Each index
   III : Check Last Index whose
**/
int largestUniqueNumber(int* arr, int arrSize){
  int i = 0, j = 0, index = 0;
  int ans = -1;

  insertionSort(arr, arrSize);
  struct stateType *state = (struct stateType *)malloc(arrSize * sizeof(struct stateType));
  if(NULL == state)
    return ans;

  for (i=0; i<arrSize; ++i) {
    if(state[i].visit == true)
      continue;
    state[i].visit = true;
    state[i].freq  = 1;

    for(j=i+1; j<arrSize; ++j) {
      if(arr[i] == arr[j]) {
	state[i].freq = state[i].freq+1;
	state[j].visit= true;
      } // if ends
    } // j for loop ends

  } // i for loop ends

  for(i=arrSize-1; i>=0; --i) {
    debug("i=%d arr[%d] freq=%d", i, arr[i], state[i].freq);
    if(state[i].freq == 0)
      continue;
    if(state[i].freq == 1) {
      ans = arr[i];
      debug("index=%d, arr[%d], ans=%d", i, arr[i], ans);
      break;
    }
  } // i for loop ends

  free(state);
  return ans;
}

int main () {
  int arr1[] = {5,7,3,9,4,9,8,3,1};
  int arr[] = {9, 9, 8, 8};
  //int arr[] = {-3,0,1,-3,1,1,1,-3,10,0};
  //int arr[] = {2, 2, 3};
  int sz = (sizeof(arr))/(sizeof(arr[0]));
  printf ("sz = %d \n", sz);
  int ans = largestUniqueNumber(arr, sz);
  printf ("--> O/P = %d \n", ans);
}

/***
    => ./a.out
    sz = 9
    [largestUniqueNumber] L=88 :i=8 arr[9] freq=0
    [largestUniqueNumber] L=88 :i=7 arr[9] freq=2
    [largestUniqueNumber] L=88 :i=6 arr[8] freq=1
    [largestUniqueNumber] L=93 :index=6, arr[8], ans=8
    --> O/P = 1
*/
