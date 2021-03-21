/***
    645. Set Mismatch, Easy

    You have a set of integers s, which originally contains all the numbers
    from 1 to n. Unfortunately, due to some error, one of the numbers in s
    got duplicated to another number in the set, which results in repetition
    of one number and loss of another number.

    You are given an integer array nums representing the data status of
    this set after the error.

    Find the number that occurs twice and the number that is missing and
    return them in the form of an array.

    Example 1:
    Input: nums = [1,2,2,4]
    Output: [2,3]

    Example 2:
    Input: nums = [1,1]
    Output: [1,2]

    Constraints:
    2 <= nums.length <= 104
    1 <= nums[i] <= 104
    Date : 21 March 2021 Saturday.
    San Diego, CA.
 */
#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

/**
 * Note: The returned array must be malloced, assume caller calls free().
 * 20ms
 */
int* findErrorNums(int* nums, int numsSize, int* returnSize){
  int a[10001]={0};
  int *result=(int*)malloc(sizeof(int)*2);
  *returnSize=2;

  for(int i=0; i< numsSize; i++) {
    debug ("--> nums[%d] = %d a[nums[i]] = %d", i, nums[i],  a[nums[i]] );
    if(++a[nums[i]] == 2) {
      //debug ("--> nums[%d] = %d a[nums[i]] = %d", i, nums[i],  a[nums[i]] );
      result[0] = nums[i];
    }
    debug ("--> a[%d] = %d a[nums[i]])=%d", i, a[i], a[nums[i]]);
  }

  debug ("a[4]=%d", a[4]);

  for(int i=1; i <= numsSize; i++) {
    debug ("a[%d] = %d", i, a[i]);
    if(a[i] == 0) {
      result[1] = i;
      return result;
    }
  }
  return result;
}

/*
 * 24ms by leetcode
 */
int* findErrorNums2(int* nums, int numsSize, int* returnSize){
  int * ans = (int*)malloc(sizeof(int)*2);
  int data[10001] = {0};
  int sum = (1+numsSize) * numsSize/2;
  for(int i = 0; i < numsSize; i += 1) {
    if(data[nums[i]] == 1) {
      ans[0] = nums[i];
      sum += nums[i];
    }
    data[nums[i]] += 1;
    sum -= nums[i];
  }
  ans[1] = sum;
  *returnSize = 2;
  return ans;
}

int main () {
  int nums[] = {1,2,2,4};
  int numsSize = sizeof(nums)/sizeof(nums[0]);
  int returnSize;

  int*ret = findErrorNums(nums, numsSize, &returnSize);

  for (int i=0; i<returnSize; i++) {
    debug ("output = %d ", ret[i]);
  }

  free(ret);
  return 0;
}

/**
   => ./a.out
   [findErrorNums] L=45 :--> nums[0] = 1 a[nums[i]] = 0
   [findErrorNums] L=50 :--> a[0] = 0 a[nums[i]])=1
   [findErrorNums] L=45 :--> nums[1] = 2 a[nums[i]] = 0
   [findErrorNums] L=50 :--> a[1] = 1 a[nums[i]])=1
   [findErrorNums] L=45 :--> nums[2] = 2 a[nums[i]] = 1
   [findErrorNums] L=50 :--> a[2] = 2 a[nums[i]])=2
   [findErrorNums] L=45 :--> nums[3] = 4 a[nums[i]] = 0
   [findErrorNums] L=50 :--> a[3] = 0 a[nums[i]])=1
   [findErrorNums] L=53 :a[4]=1
   [findErrorNums] L=56 :a[1] = 1
   [findErrorNums] L=56 :a[2] = 2
   [findErrorNums] L=56 :a[3] = 0
   [main] L=93 :output = 2
   [main] L=93 :output = 3
**/
