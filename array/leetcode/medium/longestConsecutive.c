/***
    https://leetcode.com/problems/longest-consecutive-sequence/

    Longest Consecutive Sequence

    Given an unsorted array of integers nums, return the
    length of the longest consecutive elements sequence.
    You must write an algorithm that runs in O(n) time.

    Input: nums = [100,4,200,1,3,2]
    Output: 4
    Explanation: The longest consecutive elements sequence
    is [1, 2, 3, 4]. Therefore its length is 4.

    Input: nums = [0,3,7,2,5,8,4,6,0,1]
    Output: 9

    Constraints:
    0 <= nums.length <= 105
    -109 <= nums[i] <= 109

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Wed Jul  6 08:55:43 AM PDT 2022
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

#define arrsz(x)  (sizeof(x) / sizeof((x)[0]))
#define max(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a > _b ? _a : _b; })

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

int longestConsecutive_(int* nums, int numsSize) {
  if (0 == numsSize)
    return 0;

  quick_sort(nums, 0, numsSize-1);


  int longestStreak = 1;
  int currentStreak = 1;

  for (int i=1; i<numsSize; ++i)
    printf ("-> %d", nums[i]);

  for (int i=1; i<numsSize; ++i) {
    if ((nums[i] != nums[i-1])) {
      if (nums[i] == nums[i-1] + 1) {
	currentStreak += 1;
      } else {
	longestStreak = max(longestStreak, currentStreak);
	currentStreak = 1;
      }
    }
  }
  return max(longestStreak, currentStreak);
}


int MAX(int a, int b){
  return a > b ? a : b;
}

int cmp(const void *a, const void *b){
  return *(int*)a - *(int*)b;
}

int longestConsecutive(int* nums, int numsSize){
  qsort(nums, numsSize, sizeof(int), cmp);
  int currentStreak = 1;
  int longestStreak = 1;
  if (numsSize == 0 || numsSize == 1){
    return numsSize;
  }
  for(int i = 1; i < numsSize; i++){
    if(nums[i] != nums[i-1]){
      if(nums[i] - nums[i-1] == 1 ){
	currentStreak++;
	longestStreak = MAX(longestStreak, currentStreak);
      }else{
	longestStreak = MAX(longestStreak, currentStreak);
	currentStreak = 1;
      }
    }
  }
  return longestStreak;
}

void test() {
  int ret = 0;
  int nums[] = {100,4,200,1,3,2};
  int sz = sizeof(nums)/sizeof(nums[0]);
  ret = longestConsecutive(nums, sz);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [test] L=148 :Output = 4
**/
