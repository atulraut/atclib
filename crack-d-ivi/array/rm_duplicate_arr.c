/*
 * remove duplicates elements from array
 */
#include <stdio.h>
#include "../../at_lib.h"
/***
    LeetCode : Find All Duplicates in an Array
    https://leetcode.com/explore/challenge/card/august-leetcoding-challenge/549/week-1-august-1st-august-7th/3414/
    Note: The returned array must be malloced, assume caller calls free().
    Algo :
    A1 : Alloc Big New Array (of size 24 as per below)
    A2 : Copy org array element to new element, check if both are same then copy -1 to new array.
    : Note, for copying value from org[i] to new array, make use of org[i] as  particular index,
    to new array.
    Bug - if duplicates are more than >2 it wont work.
    Below function finds outs duplicate & send you with new array.
*/
int* findDuplicates(int* org, int numsSize, int* returnSize){
  int i, j, temp;
  printf ("\n[%s] Enter sz=%d NewArraySIZE=%ld L=%d\n\n", __func__, numsSize, sizeof(int [numsSize+1]), __LINE__);

  int *new = calloc(1, sizeof(int [numsSize+1]));

  for(i=0; i<numsSize; i++)
    debug ("Init newArray[%d] = %d",i, new[i]);

  for(i=0; i<numsSize; i++) {
    temp = org[i];
    debug ("i=%d, org[i]= %d temp=%d new[nums[i] = %d \n", i, org[i], temp, new[temp] );
    /***
     * if found duplicate/repeatative number in alloc array new & org. then copy -1
     * to new array.
    */
    new[temp] = (new[temp] == org[i]) ? -1 : org[i];

    debug("i=%d org[i]= %d new[org[i]]=%d\n", i, org[i], new[temp]);
  }

  for(i=0; i<numsSize; i++)
    debug ("Post Copy newArray[%d] = %d",i, new[i]);

  for(i=1,j=1; *returnSize=j-1, i<numsSize+1; i++) {
    printf ("[%s-C] i=%d j=%d rt[i] = %d \n", __func__, i, j, new[i] );
    new[i] == -1 ? new[j++] = i : 0;
  }

  for(i=0; i<numsSize; i++)
    debug ("Final Copy newArray[%d] = %d",i, new[i]);

  return new+1;
}

/***
    In-place remove duplicates from orignal Array.
 */
int del_dup_array (int *arr, int size);
void rev (int x);
//int ar[] = {1, 2, 2, 3, 2, 21};
int ar[] = {2, 4, 3, 2, 7, 2};
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
  debug("\n_________________________");
  int nums[] = {2, 4, 391, 2, 4};
  //int nums[] = {3 ,2, 1, 2};
  int sz = sizeof(nums) / sizeof(nums[0]);
  int retSz;
  int*ret =  findDuplicates(nums, sz, &retSz);
  printf ("retSz = %d\n", retSz);
  for (i = 0; i <retSz; i++) {
    printf("Removing Duplicate & num is ->[%d] \n", ar[i]);
  }

  //rev (2);
  return (0);
}

/***
    => ./a.out
    Array with Unique list  : 5
    ->[2] ->[4] ->[3] ->[7] [main] L=84 :
    _________________________

    [findDuplicates] Enter sz=5 NewArraySIZE=24 L=19

    [findDuplicates] L=24 :Init newArray[0] = 0
    [findDuplicates] L=24 :Init newArray[1] = 0
    [findDuplicates] L=24 :Init newArray[2] = 0
    [findDuplicates] L=24 :Init newArray[3] = 0
    [findDuplicates] L=24 :Init newArray[4] = 0

    [findDuplicates] L=28 :i=0, org[i]= 2 temp=2 new[nums[i] = 0
    [findDuplicates] L=35 :i=0 org[i]= 2 new[org[i]]=2

    [findDuplicates] L=28 :i=1, org[i]= 4 temp=4 new[nums[i] = 0
    [findDuplicates] L=35 :i=1 org[i]= 4 new[org[i]]=4

    [findDuplicates] L=28 :i=2, org[i]= 391 temp=391 new[nums[i] = 0
    [findDuplicates] L=35 :i=2 org[i]= 391 new[org[i]]=391

    [findDuplicates] L=28 :i=3, org[i]= 2 temp=2 new[nums[i] = 2
    [findDuplicates] L=35 :i=3 org[i]= 2 new[org[i]]=-1

    [findDuplicates] L=28 :i=4, org[i]= 4 temp=4 new[nums[i] = 4
    [findDuplicates] L=35 :i=4 org[i]= 4 new[org[i]]=-1

    [findDuplicates] L=39 :Post Copy newArray[0] = 0
    [findDuplicates] L=39 :Post Copy newArray[1] = 0
    [findDuplicates] L=39 :Post Copy newArray[2] = -1
    [findDuplicates] L=39 :Post Copy newArray[3] = 0
    [findDuplicates] L=39 :Post Copy newArray[4] = -1

    [findDuplicates-C] i=1 j=1 rt[i] = 0
    [findDuplicates-C] i=2 j=1 rt[i] = -1
    [findDuplicates-C] i=3 j=2 rt[i] = 0
    [findDuplicates-C] i=4 j=2 rt[i] = -1
    [findDuplicates-C] i=5 j=3 rt[i] = 0

    [findDuplicates] L=47 :Final Copy newArray[0] = 0
    [findDuplicates] L=47 :Final Copy newArray[1] = 2
    [findDuplicates] L=47 :Final Copy newArray[2] = 4
    [findDuplicates] L=47 :Final Copy newArray[3] = 0
    [findDuplicates] L=47 :Final Copy newArray[4] = -1

    Removing Duplicate & num is ->[2]
    Removing Duplicate & num is ->[4]
*/
