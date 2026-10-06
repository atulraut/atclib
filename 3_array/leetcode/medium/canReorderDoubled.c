/***
    Array of Doubled Pairs

    Given an array of integers arr of even length, return true if and
    only if it is possible to reorder it such that
    arr[2 * i + 1] = 2 * arr[2 * i] for every 0 <= i < len(arr) / 2.

    Input: arr = [3,1,3,6]
    Output: false

    Input: arr = [2,1,2,6]
    Output: false

    Input: arr = [4,-2,2,-4]
    Output: true
    Explanation: We can take two groups, [-2,-4] and [2,4] to form [-2,-4,2,4] or [2,4,-2,-4].

    Input: arr = [1,2,4,16,8,4]
    Output: false

    Constraints:

    0 <= arr.length <= 3 * 104
    arr.length is even.
    -105 <= arr[i] <= 105

    https://leetcode.com/problems/array-of-doubled-pairs/
    Date: 11 August 2021
    Fair Oaks, CA.
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

int cmp(void* a,void* b) {
  return *(int*)a - *(int*)b;
}

bool helper(int* A, int ASize) {
  if(ASize%2 != 0) {
    return false;
  }

  qsort(A, ASize, sizeof(A[0]), (void *)cmp);

  int* stack=(int*)calloc(ASize,sizeof(int));
  int left=0;
  int right=0;

  for(int i=0; i < ASize; i++) {
    if(left == right) {
      stack[right++] = A[i];
      if(right-left > ASize-i-1) {
	return
	  false;
      }
      continue;
    }
    if(A[i] == 2*stack[left]) {
      left++;
    } else if(A[i] < 2*stack[left]) {
      stack[right++]=A[i];
      if(right-left > ASize-i-1) {
	return false;
      }
    } else {
      return false;
    }
  }
  return left==right;
}

bool canReorderDoubled(int* A, int ASize) {
  int* array1=(int*)calloc(ASize,sizeof(int));
  int count1=0;
  int* array2=(int*)calloc(ASize,sizeof(int));
  int count2=0;

  for(int i=0; i < ASize; i++){
    if(A[i] <= 0){
      array1[count1++] =- A[i];
    } else {
      array2[count2++] = A[i];
    }
  }
  return helper(array1, count1) && helper(array2, count2);
}

int main (int argc, char **argv) {
  bool ret = 0;
  int A[]= {4,-2,2,-4};
  int ASize = sizeof(A)/sizeof(A[0]);

  ret = canReorderDoubled(A, ASize);
  debug("Output = %d", ret);
  return 0;
}

/**

 **/
