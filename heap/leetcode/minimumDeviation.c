/***
    https://leetcode.com/problems/minimize-deviation-in-array/
    Hard:Minimize Deviation in Array

    You are given an array nums of n positive integers.

    You can perform two types of operations on any element of
    the array any number of times:

    If the element is even, divide it by 2.
    For example, if the array is [1,2,3,4], then you can do
    this operation on the last element, and the array will be [1,2,3,2].

    If the element is odd, multiply it by 2.
    For example, if the array is [1,2,3,4], then you can do
    this operation on the first element, and the array will be [2,2,3,4].

    The deviation of the array is the maximum difference
    between any two elements in the array.

    Return the minimum deviation the array can have after
    performing some number of operations.

    Input: nums = [1,2,3,4]
    Output: 1
    Explanation: You can transform the array to [1,2,3,2], then to [2,2,3,2],
    then the deviation will be 3 - 2 = 1.

    Input: nums = [4,1,5,20,3]
    Output: 3
    Explanation: You can transform the array after two operations
    to [4,2,5,5,3], then the deviation will be 5 - 2 = 3.

    Input: nums = [2,10,8]
    Output: 3

    Constraints:
    n == nums.length
    2 <= n <= 105
    1 <= nums[i] <= 109
    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Sat Feb 19 13:16:27 PST 2022
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
//#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)
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

#define SWAP(x, y) (x ^= y ^= x ^= y)
#define MIN(a,b) ((a<b)? a:b)

void checkBigger(int *h, int posi) {
  for(int comp; posi >= 4; posi = comp) {
    comp = (posi>>2<<1)+1;
    if(h[posi] > h[comp])
      SWAP(h[posi], h[comp]);
    else
      break;
  }
}

void checkSmaller(int *h, int posi) {
  for(int comp; posi >= 4; posi = comp) {
    comp = posi>>2<<1;
    if(h[posi] < h[comp])
      SWAP(h[posi], h[comp]);
    else
      break;
  }
}

void insert(int *h, int top, int data) {
  h[top] = data;

  if(!(top&1)) {           //is left
    if(h[top] > h[top>>1])
      checkBigger(h,top);
    else
      checkSmaller(h,top);
  }
  else {                       //is right
    if(h[top] < h[top-1]) {
      SWAP(h[top], h[top-1]);
      checkSmaller(h,top-1);
    }
    else  checkBigger(h,top);
  }
}

void deleteMax(int *h, int *top) {
  h[3] = h[(*top)--];
  int par = 3, chi = 5;

  while (chi <= (*top)) {
    if(chi+2 <= (*top) && h[chi+2]>h[chi])
      chi += 2;
    if(h[chi] > h[par]){
      SWAP(h[chi], h[par]);
      par = chi;
      chi = (chi<<1)-1;
    }
    else
      break;
  }
  if(h[par] < h[par-1])
    SWAP(h[par], h[par-1]);
}

int minimumDeviation(int* nums, int size) {
  int h[size+2], top=1, ans;  //h, the h[0] & h[1] is no number
  for(int i=0; i<size; i++){
    if(nums[i]&1)    //is odd
      nums[i] <<= 1;
    insert(h, ++top, nums[i]);
  }

  ans = h[3]-h[2];
  while (!(h[3]&1)){    //while the max value is even
    int t = h[3]>>1;
    deleteMax(h, &top);
    insert(h, ++top, t);
    ans = MIN(ans, h[3]-h[2]);
  }
  return ans;
}

void test() {
  int ret = 0;

  int arr[] = {1,2,3,4};
  int size = sizeof(arr)/sizeof(arr[0]);
  ret =  minimumDeviation(arr, size);
  printf("Output = %d\n\n", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   Input  = 1 2 3 3
   Output = 1
**/
