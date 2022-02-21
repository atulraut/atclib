/***
    https://leetcode.com/problems/majority-element/
    Majority Element

    Given an array nums of size n, return the majority element.
    The majority element is the element that appears more than ⌊n/2⌋ times.
    You may assume that the majority element always exists in the array.

    Input: nums = [3,2,3]
    Output: 3

    Input: nums = [2,2,1,1,1,2,2]
    Output: 2

    Constraints:
    n == nums.length
    1 <= n <= 5 * 104
    -231 <= nums[i] <= 231 - 1

    Follow-up: Could you solve the problem in linear time and in O(1) space?

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Sun Feb 20 21:55:30 PST 2022
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

int majorityElement1 (int* nums, int numsSize) {
  int i=0,j=0;
  int count = 0;

  for(i=0; i<numsSize; i++) {
    if(count == 0)
      j = nums[i];
    if(nums[i] == j)
      count++;
    else
      count--;
    debug("i=%d count=%d nums[i]=%d", i, count, nums[i]);
  }
  return j;
}

struct hashMap {
  int key;
  int value;
  struct hashMap *next;
};

#define MAXSIZE 100
int getIndex(long i) {
  if(i<0)
    i=-i;

  return i%MAXSIZE;
}

int majorityElement (int* nums, int numsSize) {
  struct hashMap **hashM=calloc(MAXSIZE, sizeof(struct hashMap *));
  for(int i=0;i<numsSize;i++){
    int index=getIndex(nums[i]);
    struct hashMap *iter=hashM[index];
    struct hashMap *prev=iter;
    while(iter!=NULL){
      if(iter->key==nums[i]) {
	iter->value++;
	break;
      }
      prev=iter;
      iter=iter->next;
    }
    if(iter==NULL){
      struct hashMap *tmp=malloc(sizeof(struct hashMap));
      tmp->key=nums[i];
      tmp->value=1;
      tmp->next=NULL;
      if(hashM[index]==NULL)
	hashM[index]=tmp;
      else
	prev->next=tmp;
    }
  }

  for(int j=0;j<MAXSIZE;j++){
    struct hashMap *iter=hashM[j];
    while(iter!=NULL){
      if(iter->value > numsSize/2)
	return iter->key;
      iter=iter->next;
    }
  }

  return -1;
}

void test() {
  int ret = 0;
  int arr[] = {3,2,3};
  ret = majorityElement1(arr, 3);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [majorityElement1] L=65 :i=0 count=1 nums[i]=3
   [majorityElement1] L=65 :i=1 count=0 nums[i]=2
   [majorityElement1] L=65 :i=2 count=1 nums[i]=3
   [test] L=126 :Output = 3
*/
/**
   => ./a.out
   [test] L=127 :Output = 3
**/
