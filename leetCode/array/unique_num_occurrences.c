/*
  Given an array of integers arr, write a function that returns true
  if and only if the number of occurrences of each value in the array is unique.
  Example 1:
   Input: arr = [1,2,2,1,1,3]
   Output: true
  Explanation: The value 1 has 3 occurrences, 2 has 2 and 3 has 1. No two values have the same number of occurrences.
  Example 2:
   Input: arr = [1,2]
   Output: false
  Example 3:
   Input: arr = [-3,0,1,-3,1,1,1,-3,10,0]
   Output: true
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

struct stateType {
  bool visit:1;
  int freq:31;
};

bool uniqueOccurrences(int *arr, int arrSize) {
  int i = 0, j = 0;
  bool ans = true;

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

  for(i=0; ans && i<arrSize; ++i) {
    if(state[i].freq == 0)
      continue;

    for(j=i+1; ans && j<arrSize; ++j) {
      ans = (state[i].freq != state[j].freq);
      printf ("ans = %d \n", ans);
    } // j for loop ends
  } // i for loop ends

  free(state);
  return ans;
}

int main () {
  int arr[] = {1,2,2,1,1,3};
  //int arr[] = {1,2};
  //int arr[] = {-3,0,1,-3,1,1,1,-3,10,0};
  //int arr[] = {-4, 3, 3};
  int sz = (sizeof(arr))/(sizeof(arr[0]));
  printf ("sz = %d \n", sz);
  bool ans = uniqueOccurrences(arr, sz);
  printf ("--> O/P = %d \n", ans);
}
