/***
    Medium: 307. Range Sum Query - Mutable

    Given an integer array nums, handle multiple queries of
    the following types:

    Update the value of an element in nums.
    Calculate the sum of the elements of nums between indices
    left and right inclusive where left <= right.

    Implement the NumArray class:

    NumArray(int[] nums) Initializes the object with the integer array nums.
    void update(int index, int val) Updates the value of nums[index] to be val.
    int sumRange(int left, int right) Returns the sum of the elements
    of nums between indices left and right inclusive
    (i.e. nums[left] + nums[left + 1] + ... + nums[right]).

    Input
    ["NumArray", "sumRange", "update", "sumRange"]
    [[[1, 3, 5]], [0, 2], [1, 2], [0, 2]]
    Output
    [null, 9, null, 8]

    Explanation
    NumArray numArray = new NumArray([1, 3, 5]);
    numArray.sumRange(0, 2); // return 1 + 3 + 5 = 9
    numArray.update(1, 2);   // nums = [1, 2, 5]
    numArray.sumRange(0, 2); // return 1 + 2 + 5 = 8

    Constraints:

    1 <= nums.length <= 3 * 104
    -100 <= nums[i] <= 100
    0 <= index < nums.length
    -100 <= val <= 100
    0 <= left <= right < nums.length
    At most 3 * 104 calls will be made to update and sumRange.

    https://leetcode.com/problems/range-sum-query-mutable/

    Date: 19 June 2021
    San Diego, CA.
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
  int size;
  int *tree;
} NumArray;


NumArray* numArrayCreate(int* nums, int numsSize) {
  NumArray *array = (NumArray *)calloc(1, sizeof(NumArray));
  array -> size = numsSize;
  array -> tree = (int *)calloc(2*numsSize, sizeof(int));

  int i, j;
  for(i=numsSize, j=0; i<2*numsSize; i++, j++) {
    array -> tree[i] += nums[j];
  }
  for(i=numsSize-1; i>0; i--){
    array -> tree[i] = array -> tree[2*i] + array -> tree[2*i+1];
  }

  return array;

}

void numArrayUpdate(NumArray* obj, int pos, int val) {
  pos += obj -> size;
  obj -> tree[pos] = val;

  int left, right, middle;
  while(pos > 0) {
    left = pos;
    right = pos;
    if(pos % 2 == 0) right = pos + 1;
    else left = pos - 1;
    middle = pos / 2;
    obj -> tree[middle] = obj -> tree[left] + obj -> tree[right];
    pos /= 2;
  }
}

int numArraySumRange(NumArray* obj, int l, int r) {
  l += obj -> size;
  r += obj -> size;

  int sum_arr = 0;
  while(l <= r) {
    if(l % 2 == 1) {
      sum_arr += obj -> tree[l];
      l ++;
    }
    if(r % 2 == 0) {
      sum_arr += obj -> tree[r];
      r --;
    }

    l /= 2;
    r /= 2;
  }

  return sum_arr;
}

void numArrayFree(NumArray* obj) {
  free(obj -> tree);
  free(obj);
}

/**
 * Your NumArray struct will be instantiated and called as such:
 * NumArray* obj = numArrayCreate(nums, numsSize);
 * numArrayUpdate(obj, index, val);

 * int param_2 = numArraySumRange(obj, left, right);

 * numArrayFree(obj);
 */

int main () {
  int ret = 0;
  //["NumArray","sumRange","update","sumRange"]

  int nums[] = {1, 3, 5};
  int numsSize = sizeof(nums) / sizeof(nums[0]);

  //  [[[1,3,5]],[0,2],[1,2],[0,2]]

  NumArray* obj = numArrayCreate(nums, numsSize);

  ret = numArraySumRange(obj, 0, 2);
  debug("Output = %d", ret);

  numArrayUpdate(obj, 1, 2);

  ret = numArraySumRange(obj, 0, 2);
  debug("Output = %d", ret);

  numArrayFree(obj);

  return 0;
}

/**
   => ./a.out
   [main] L=147 :Output = 9
   [main] L=152 :Output = 8
**/
