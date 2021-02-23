/***
    LeetCode : Sort Integers by The Number of 1 Bits
    https://leetcode.com/problems/sort-integers-by-the-number-of-1-bits/
    Given an integer array arr. You have to sort the integers in the array
    in ascending order by the number of 1's in their binary representation
    and in case of two or more integers have the same number of 1's you
    have to sort them in ascending order.
    Return the sorted array.

    Example 1:
    Input: arr = [0,1,2,3,4,5,6,7,8]
    Output: [0,1,2,4,8,3,5,6,7]
    Explantion: [0] is the only integer with 0 bits.
    [1,2,4,8] all have 1 bit.
    [3,5,6] have 2 bits.
    [7] has 3 bits.
    The sorted array by bits is [0,1,2,4,8,3,5,6,7]

    Example 2:
    Input: arr = [1024,512,256,128,64,32,16,8,4,2,1]
    Output: [1,2,4,8,16,32,64,128,256,512,1024]
    Explantion: All integers have 1 bit in the binary representation, you should
    just sort them in ascending order.

    Example 3:
    Input: arr = [10000,10000]
    Output: [10000,10000]

    Example 4:
    Input: arr = [2,3,5,7,11,13,17,19]
    Output: [2,3,5,17,7,11,13,19]

    Example 5:
    Input: arr = [10,100,1000,10000]
    Output: [10,100,10000,1000]

    Date : 20 Feb 2021
    San Diego, CA
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

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

int countBits (int num) {
  int cnt = 0;
  while (num) {
    num = num & (num - 1);
    cnt++;
  }
  return cnt;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 * Using Bubble Sort
 */
int* sortByBits(int* arr, int arrSize, int* returnSize){
  int* bitSizeArr = malloc(sizeof(int) * arrSize);

  for(int i=0; i<arrSize; i++) {
    bitSizeArr[i] = countBits(arr[i]);
  }

  for(int i=0; i<(arrSize); i++) {
    for(int y=0; y<arrSize-1; y++) {
      if(bitSizeArr[y] > bitSizeArr[y+1]) {
	int temp = bitSizeArr[y];
	bitSizeArr[y] = bitSizeArr[y+1];
	bitSizeArr[y+1] = temp;

	temp = arr[y];
	arr[y] = arr[y + 1];
	arr[y + 1] = temp;

      }
    }
  }

  debug (" arr = %d bit = %d ", arr[0], bitSizeArr[0]);
  for (int i=0; i<arrSize; i++)
    debug ("arr[%d] arr = %d bit = %d ", i, arr[i], bitSizeArr[i]);

  //1 bit
  for(int i=0; i<(arrSize); i++) {
    for(int y=0; y<arrSize-1; y++) {
      if(bitSizeArr[y] == bitSizeArr[y+1]) {
	if(arr[y] > arr[y+1]) {
	  int temp = arr[y];
	  arr[y] = arr[y + 1];
	  arr[y + 1] = temp;
	}
      }
    }
  }

  *returnSize = arrSize;
  free(bitSizeArr);
  bitSizeArr = NULL;
  return arr;
}

int main () {
  int arr[] = {0,1,2,3,4,5,6,7,8};
  int arrSize = sizeof(arr) / sizeof(arr[0]);
  int returnSize = 0;
  int* ret =  sortByBits(arr, arrSize, &returnSize);
  for (int i=0; i<returnSize; i++)
    debug ("arr[%d] = %d", i, ret[i]);

  return 0;
}

/**
   => ./a.out
   [sortByBits] L=88 : arr = 0 bit = 0
   [sortByBits] L=90 :arr[0] arr = 0 bit = 0
   [sortByBits] L=90 :arr[1] arr = 1 bit = 1
   [sortByBits] L=90 :arr[2] arr = 2 bit = 1
   [sortByBits] L=90 :arr[3] arr = 4 bit = 1
   [sortByBits] L=90 :arr[4] arr = 8 bit = 1
   [sortByBits] L=90 :arr[5] arr = 3 bit = 2
   [sortByBits] L=90 :arr[6] arr = 5 bit = 2
   [sortByBits] L=90 :arr[7] arr = 6 bit = 2
   [sortByBits] L=90 :arr[8] arr = 7 bit = 3
   [main] L=117 :arr[0] = 0
   [main] L=117 :arr[1] = 1
   [main] L=117 :arr[2] = 2
   [main] L=117 :arr[3] = 4
   [main] L=117 :arr[4] = 8
   [main] L=117 :arr[5] = 3
   [main] L=117 :arr[6] = 5
   [main] L=117 :arr[7] = 6
   [main] L=117 :arr[8] = 7
**/

/** More Optimized
int cmp(const void *a, const void *b){
    int aa = *(int*)a;
    int bb = *(int*)b;
    int cmd = __builtin_popcount(aa)-__builtin_popcount(bb);
    return cmd==0?aa-bb:cmd;
}
int* sortByBits(int* arr, int arrSize, int* returnSize){
    int i,count=0;
    qsort(arr, arrSize, sizeof(arr[0]), cmp);
    *returnSize=arrSize;
    return arr;
}
**/
