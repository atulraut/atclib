/***
    Find All Duplicates in an Array

    Given an array of integers, 1 ≤ a[i] ≤ n (n = size of array),
    some elements appear twice and others appear once.
    Find all the elements that appear twice in this array.
    Could you do it without extra space and in O(n) runtime?
    Example:
    Input:
    [4,3,2,7,8,2,3,1]
    Output:
    [2,3]
    https://leetcode.com/problems/find-all-duplicates-in-an-array/

*/
#include "../../at_lib.h"

// 96ms
int* findDuplicates(int* nums, int numsSize, int* returnSize){
   int *rt=calloc(1,sizeof(int [numsSize+1]));

    for(int i=0; i<numsSize; i++) {
        rt[nums[i]] = rt[nums[i]] == nums[i] ? -1 : nums[i];
    }

    for(int i=1,j=1; *returnSize=j-1,i<numsSize+1; i++) {
        rt[i] == -1 ? rt[j++]=i : 0;
    }

    return rt+1;
}

/* 186ms */
int* findDuplicates2(int* nums, int numsSize, int* returnSize) {
  int *arr=calloc(numsSize+1,sizeof(int));
  int *ret=calloc(numsSize,sizeof(int));
  int idx=0;

  for(int i=0; i<numsSize; i++) {
    arr[nums[i]]++;
  }
  for(int i=0; i<numsSize; i++) {
    if(arr[nums[i]] == 2) {
      arr[nums[i]]--;
      ret[idx++] = nums[i];
    }
  }
  *returnSize=idx;
  free(arr);
  arr = NULL;
  return ret;
}

int main () {
  int arr[] = {4,3,2,7,8,2,3,1};
  int sz = sizeof(arr) / sizeof(arr[0]);
  int retSz;

  for (int i=0; i<sz; i++) {
    printf ("Input Array = %d \n", arr[i]);
  }

  int *op =  findDuplicates(arr, sz, &retSz);

  printf ("Ret Sz = %d \n", retSz);
  for (int i=0; i<retSz; i++) {
    printf ("Output Array = %d \n", op[i]);
  }
  free(op);
  op = NULL;
  return 0;
}

/**
   => ./a.out
   Input Array = 4
   Input Array = 3
   Input Array = 2
   Input Array = 7
   Input Array = 8
   Input Array = 2
   Input Array = 3
   Input Array = 1
   Ret Sz = 2
   Output Array = 3
   Output Array = 2
**/
