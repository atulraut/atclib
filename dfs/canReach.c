/***
    https://leetcode.com/problems/jump-game-iii/
    Jump Game III

    Given an array of non-negative integers arr, you are initially positioned
    at start index of the array. When you are at index i, you can
    jump to i + arr[i] or i - arr[i], check if you can reach to any index with value 0.

    Notice that you can not jump outside of the array at any time.

    Input: arr = [4,2,3,0,3,1,2], start = 5
    Output: true
    Explanation:
    All possible ways to reach at index 3 with value 0 are:
    index 5 -> index 4 -> index 1 -> index 3
    index 5 -> index 6 -> index 4 -> index 1 -> index 3

    Input: arr = [4,2,3,0,3,1,2], start = 0
    Output: true
    Explanation:
    One possible way to reach at index 3 with value 0 is:
    index 0 -> index 4 -> index 1 -> index 3

    Input: arr = [3,0,2,1,2], start = 2
    Output: false
    Explanation: There is no way to reach at index 1 with value 0.

    Constraints:
    1 <= arr.length <= 5 * 104
    0 <= arr[i] < arr.length
    0 <= start < arr.length
    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 12/9/2021
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


void DFS(int* arr, int arrSize, int start, int *reach) {
  if(start < 0 || start >= arrSize || reach[start] == 1)
    return;
  reach[start] = 1;
  DFS(arr, arrSize, start+arr[start], reach);
  DFS(arr, arrSize, start-arr[start], reach);
}

bool canReach(int* arr, int arrSize, int start) {
  int reach[arrSize];
  for(int i = 0; i < arrSize; i++) {
    reach[i] = 0;
  }

  DFS(arr, arrSize, start, reach);

  for(int i = 0; i < arrSize; i++) {
    if(arr[i] == 0 && reach[i] == 1)
      return true;
  }

  return false;
}

bool canReach2(int* arr, int arrSize, int start) {
  if(start>arrSize-1 || start<0)
    return false;
  if(arr[start] == -1)
    return false;
  int diff = arr[start];

  // if(start+arr[start] > arrSize-1 && start-arr[start] < 0) return false;
  if(arr[start] ==0)
    return true;

  arr[start] = -1;
  if(canReach(arr,arrSize,start+diff)) {
    return true;
  }

  if(canReach(arr,arrSize,start-diff)) {
    return true;
  }

  return false;
}

bool check(int* arr, int arrSize, int start) {
  if(start < 0 || start >= arrSize)
    return false;
  if(arr[start] < 0)//if index is already visited
    return false;
  if(arr[start] == 0)//final destination
    return true;

  arr[start] =- arr[start];//to mark a visited index
  int k = (check(arr,arrSize,start+arr[start])||check(arr,arrSize,start-arr[start]));//will check in left and right index with respect to start index ,there is no effect of making the arr[start] negative
  arr[start] =- arr[start];//to get the original value back
  return k;
}

bool canReach1(int* arr, int arrSize, int start) {
  int k = check(arr,arrSize,start);
  for(int i=0; i< arrSize;i++)// to show that array values are not changed
    printf("%d ",arr[i]);
  return k;
}

int main (int argc, char **argv) {
  int ret = 0;
  int arr[] = {4,2,3,0,3,1,2};
  int arrSize = arrsz(arr);
  int start   = 5;

  debug ("Array Siz = %d", arrSize);
  ret = canReach(arr, arrSize, start);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=110 :Array Siz = 7
   [main] L=112 :Output = 1
**/
