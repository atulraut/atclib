/*
  Given an array of 2n integers, your task is to group these integers
  into n pairs of integer, say (a1, b1), (a2, b2), ..., (an, bn) which
  makes sum of min(ai, bi) for all i from 1 to n as large as possible.
  */
#include <stdio.h>
#include <stdlib.h>

void swap(int *i, int *j) {
  int temp = *i;
  *i = *j;
  *j = temp;
}

int partition(int *a, int start, int end) {
  int pivot = a[end];
  int partitionIndex = start; // set partition index as start initially
  for (int i=start; i<end; i++) {
    if (a[i] <= pivot) {
      swap(&a[i], &a[partitionIndex]);
      partitionIndex++;
    }
  }
  swap(&a[partitionIndex], &a[end]); // swap pivot with element as partition index
  return partitionIndex;
}

void quick_sort(int *a, int start, int end) {
  if(start < end) {
    int partitionIndex = partition(a, start, end);
    quick_sort(a, start, partitionIndex-1);
    quick_sort(a, partitionIndex+1, end);
  }
}

int arrayPairSum(int* nums, int numsSize) {
   quick_sort(nums,0, numsSize-1);
    int sum = 0;
    for(int i = 0; i < numsSize; i = i + 2) {
        sum = sum + nums[i];
    }
    return sum;
}

int main() {
  int arr[] = {1,3,2,4};
  int sz = sizeof(arr)/sizeof(arr[0]);
  int ans = arrayPairSum(arr, sz);
  printf ("ans = %d \n", ans);
}
