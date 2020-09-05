/*
* remove duplicates elements from array
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
/***
    LeetCode : Find All Duplicates in an Array
    https://leetcode.com/explore/challenge/card/august-leetcoding-challenge/549/week-1-august-1st-august-7th/3414/
    Note: The returned array must be malloced, assume caller calls free().
 */
int* findDuplicates(int* nums, int numsSize, int* returnSize){
  int i, j;
  printf ("\n[%s] Enter sz=%ld L=%d\n", __func__, sizeof(int [numsSize+1]), __LINE__);

  int *rt=calloc(1,sizeof(int [numsSize+1]));

  for(i=0; i<numsSize; i++){
    printf ("[%s-A] nums[i]= %d rt[nums[i] = %d \n", __func__, nums[i], rt[nums[i]] );
    rt[nums[i]] = (rt[nums[i]] == nums[i]) ? -1 : nums[i];
    printf ("[%s-B] nums[i]= %d rt[nums[i]]=%d\n",__func__, nums[i], rt[nums[i]]);
  }

  for(i=1,j=1; *returnSize=j-1,i<numsSize+1; i++){
    printf ("[%s-C] i=%d j=%d rt[i] = %d \n", __func__, i, j, rt[i] );
    rt[i] == -1 ? rt[j++]=i : 0;
  }

  return rt+1;
}

int del_dup_array (int *arr, int size);
void rev (int x);
//int ar[] = {1, 2, 2, 3, 2, 21};
int ar[] = {2, 4, 3, 2, 7};
int del_dup_array (int arr[], int size) {
  int i, j, k;
  for (i = 0; i < size; i++) {
    for (j = i + 1; j < size;) {
      if (arr[j] == arr[i]) {
for (k=j; k<size; k++) {
  if ((size-1) == k)
    arr[k+1] = 0;
  // printf ("i=%d, j=%d, k=%d, k=[%d], k+1=[%d] size = %d\n",i,j,k,  arr[k], arr[k + 1], size);
  arr[k] = arr[k + 1];
}
size--;
      } else
        j++;
    }
  }
  return size;
}

int main() {
  int i, j, k, size=5;

  size = sizeof(ar) / sizeof(ar[0]);
  printf("Array with Unique list  : %d \n", size);
  size = del_dup_array (ar, size);
  for (i = 0; i < size; i++) {
    printf("->[%d] ", ar[i]);
  }
  int nums[] = {2, 4, 31, 2, 4};
  int sz = sizeof(nums) / sizeof(nums[0]);
  int retSz;
  int*ret =  findDuplicates(nums, sz, &retSz);
  printf ("\n");
  for (i = 0; i <retSz; i++) {
    printf("Removing Duplicate & num is ->[%d] \n", ar[i]);
  }

  //rev (2);
  return (0);
}

/***

 */
