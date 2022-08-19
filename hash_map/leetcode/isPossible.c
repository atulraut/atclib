/***
    https://leetcode.com/problems/split-array-into-consecutive-subsequences/

    Split Array into Consecutive Subsequences

    You are given an integer array nums that is sorted in
    non-decreasing order.

    Determine if it is possible to split nums into one or more
    subsequences such that both of the following conditions are true:

    Each subsequence is a consecutive increasing sequence (i.e. each
    integer is exactly one more than the previous integer).
    All subsequences have a length of 3 or more.
    Return true if you can split nums according to the above conditions,
    or false otherwise.

    A subsequence of an array is a new array that is formed from the
    original array by deleting some (can be none) of the elements without
    disturbing the relative positions of the remaining elements.
    (i.e., [1,3,5] is a subsequence of [1,2,3,4,5] while [1,3,2] is not).

    Input: nums = [1,2,3,3,4,5]
    Output: true
    Explanation: nums can be split into the following subsequences:
    [1,2,3,3,4,5] --> 1, 2, 3
    [1,2,3,3,4,5] --> 3, 4, 5

    Input: nums = [1,2,3,3,4,4,5,5]
    Output: true
    Explanation: nums can be split into the following subsequences:
    [1,2,3,3,4,4,5,5] --> 1, 2, 3, 4, 5
    [1,2,3,3,4,4,5,5] --> 3, 4, 5

    Input: nums = [1,2,3,4,4,5]
    Output: false
    Explanation: It is impossible to split nums into consecutive increasing
    subsequences of length 3 or more.

    Constraints:
    1 <= nums.length <= 104
    -1000 <= nums[i] <= 1000
    nums is sorted in non-decreasing order.
    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Thu Aug 18 09:18:44 PM PDT 2022
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

typedef struct heap_s {
  int capacity;
  int size;
  // arr[size][0] max value of sequence
  // arr[size][1] length of sequence
  int** arr;
} heap_t;

heap_t* init(int);
void insert(heap_t*, int, int);
int* top(heap_t*);
void pop(heap_t*);
bool empty(heap_t*);

bool isPossible(int* nums, int numsSize) {
  heap_t* heap = init(numsSize);
  for (int i = 0; i < numsSize; i++) {
    // can't put value to the sequence any more
    while (!empty(heap) && nums[i] - top(heap)[0] > 1) {
      // find invalid sequence, return false
      if (top(heap)[1] < 3)
         return false;
      pop(heap);
    }

    if (empty(heap) || nums[i] == top(heap)[0]) {
      // add a new sequence
      insert(heap, nums[i], 1);
    } else {
      // update the old sequence's value and length
      int length = top(heap)[1] + 1;
      pop(heap);
      insert(heap, nums[i], length);
    }
  }

  while (!empty(heap)) {
    // find invalid sequence, return false
    if (top(heap)[1] < 3)
      return false;
    pop(heap);
  }

  return true;
}

heap_t* init(int max) {
  heap_t* heap = (heap_t*)malloc(sizeof(heap_t));
  heap->capacity = max;
  heap->size = 0;
  heap->arr = (int**)malloc(sizeof(int*) * (max + 1));
  return heap;
}

// if a < b
bool cmp(int* a, int* b) {
  return a[0] == b[0] ? b[1] > a[1] : b[0] > a[0];
}

void swap(int** a, int i, int j) {
  int* tmp = a[i];
  a[i] = a[j];
  a[j] = tmp;
}

void insert(heap_t* heap, int val, int length) {
  int* node = (int*)malloc(sizeof(int) * 2);
  node[0] = val, node[1] = length;
  heap->arr[++heap->size] = node;
  for (int i = heap->size; i > 1 && cmp(heap->arr[i], heap->arr[i / 2]); i /= 2) {
    swap(heap->arr, i, i / 2);
  }
}

int* top(heap_t* heap) {
  return heap->arr[1];
}

void pop(heap_t* heap) {
  heap->arr[1] = heap->arr[heap->size--];
  for (int i = 1; i * 2 <= heap->size;) {
    // find smaller child to compare with the current node
    int child = cmp(heap->arr[i * 2], heap->arr[i * 2 + 1]) ? i * 2 : i * 2 + 1;
    if (cmp(heap->arr[child], heap->arr[i])) {
      // swap if child is smaller
      swap(heap->arr, child, i);
      i = child;
    } else
      break;
  }
}

bool empty(heap_t* heap) {
  return heap->size == 0;
}

void test() {
  bool ret = 0;
  int nums[] = {1, 2, 3, 3, 4, 5};
  int numsSize = sizeof(nums)/sizeof(nums[0]);

  ret = isPossible(nums, numsSize);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   test] L=178 :Output = 1
**/
