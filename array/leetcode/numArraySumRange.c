/***
    Easy: 303. Range Sum Query - Immutable

    Given an integer array nums, handle multiple queries of the following type:

    Calculate the sum of the elements of nums between indices left and right
    inclusive where left <= right.

    Implement the NumArray class:

    NumArray(int[] nums) Initializes the object with the integer array nums.
    int sumRange(int left, int right) Returns the sum of the elements of n
    ums between indices left and right inclusive
    (i.e. nums[left] + nums[left + 1] + ... + nums[right]).

    Input
    ["NumArray", "sumRange", "sumRange", "sumRange"]
    [[[-2, 0, 3, -5, 2, -1]], [0, 2], [2, 5], [0, 5]]
    Output
    [null, 1, -1, -3]

    Explanation
    NumArray numArray = new NumArray([-2, 0, 3, -5, 2, -1]);
    numArray.sumRange(0, 2); // return (-2) + 0 + 3 = 1
    numArray.sumRange(2, 5); // return 3 + (-5) + 2 + (-1) = -1
    numArray.sumRange(0, 5); // return (-2) + 0 + 3 + (-5) + 2 + (-1) = -3

    https://leetcode.com/problems/range-sum-query-immutable/

    Date: 17 August 2021
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

typedef struct {
  int* arr;
} NumArray;

NumArray* numArrayCreate(int* nums, int numsSize) {
  NumArray *obj;
  int i;

  obj = (NumArray*)calloc(1, sizeof(NumArray));
  obj->arr = (int *) calloc(numsSize+1, sizeof(int));
  //obj->size = numsSize;
  obj->arr[0] = 0;
  for(i = 0; i < numsSize; i++){
    obj->arr[i+1] = nums[i] + obj->arr[i];
    debug ("-> nums[%d]=%d obj->arr[%d]=%d obj->arr[%d]=%d", i, nums[i], i, obj->arr[i], i+1, obj->arr[i+1] );
  }
  return obj;
}

int numArraySumRange(NumArray* obj, int left, int right) {
  int sum = 0;
  if(!obj)
    return 0;
  sum = obj->arr[right+1] - obj->arr[left];
  return sum;
}

void numArrayFree(NumArray* obj) {
  free(obj->arr);
  free(obj);
}

/**
 * Your NumArray struct will be instantiated and called as such:
 * NumArray* obj = numArrayCreate(nums, numsSize);
 * int param_1 = numArraySumRange(obj, left, right);

 * numArrayFree(obj);
*/

int main (int argc, char **argv) {
  int ret = 0;
  int arr[] = {-2, 0, 3, -5, 2, -1};
  int sz = sizeof(arr) / sizeof(arr[0]);

  /* Step I :*/
  NumArray* obj = numArrayCreate(arr, sz);

  /* Step II :*/
  //ret =  numArraySumRange(obj, 0, 2);
  ret =  numArraySumRange(obj, 2, 5);

  /* Step III :*/
  numArrayFree(obj);

  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [numArrayCreate] L=34 :-> nums[0]=-2 obj->arr[0]=0 obj->arr[1]=-2
   [numArrayCreate] L=34 :-> nums[1]=0 obj->arr[1]=-2 obj->arr[2]=-2
   [numArrayCreate] L=34 :-> nums[2]=3 obj->arr[2]=-2 obj->arr[3]=1
   [numArrayCreate] L=34 :-> nums[3]=-5 obj->arr[3]=1 obj->arr[4]=-4
   [numArrayCreate] L=34 :-> nums[4]=2 obj->arr[4]=-4 obj->arr[5]=-2
   [numArrayCreate] L=34 :-> nums[5]=-1 obj->arr[5]=-2 obj->arr[6]=-3
   [main] L=75 :Output = -1
**/

/**
   Complexity analysis

   Time complexity : O(1) time per query, O(n)
   time pre-computation. Since the cumulative sum is cached, each sumRange
   query can be calculated in O(1) time.

   Space complexity : O(n).
**/
