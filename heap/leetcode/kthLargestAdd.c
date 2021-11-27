/***
    https://leetcode.com/problems/kth-largest-element-in-a-stream/
    Kth Largest Element in a Stream

    Design a class to find the kth largest element in a stream.
    Note that it is the kth largest element in the sorted order,
    not the kth distinct element.

    Implement KthLargest class:

    KthLargest(int k, int[] nums) Initializes the object with
    the integer k and the stream of integers nums.
    int add(int val) Appends the integer val to the stream and
    returns the element representing the kth largest element in
    the stream.

    Input
    ["KthLargest", "add", "add", "add", "add", "add"]
    [[3, [4, 5, 8, 2]], [3], [5], [10], [9], [4]]
    Output
    [null, 4, 5, 5, 8, 8]

    Explanation
    KthLargest kthLargest = new KthLargest(3, [4, 5, 8, 2]);
    kthLargest.add(3);   // return 4
    kthLargest.add(5);   // return 5
    kthLargest.add(10);  // return 5
    kthLargest.add(9);   // return 8
    kthLargest.add(4);   // return 8

    Constraints:
    1 <= k <= 104
    0 <= nums.length <= 104
    -104 <= nums[i] <= 104
    -104 <= val <= 104

    At most 104 calls will be made to add.
    It is guaranteed that there will be at least k elements in the array when you search for the kth element.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 27 Nov  2021
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

typedef struct {
  int* arr;
  int top;
  int heap_size;
} KthLargest;

void heapify_bottom_top(int* arr,int index) {
  int parent =(index-1) / 2;

  if(parent >= 0 && arr[index] < arr[parent]) {
    int temp = arr[index];
    arr[index] = arr[parent];
    arr[parent] = temp;
    heapify_bottom_top(arr,parent);
  }
}

void heapify_top_bottom(int* arr,int parent,int size) {
  int left = (2*parent) + 1;
  int right = (2*parent) + 2;

  int min = parent;

  if(left <= size && arr[left] < arr[min])
    min = left;

  if(right <= size && arr[right] < arr[min])
    min = right;

  if(min != parent) {
    int temp = arr[min];
    arr[min] = arr[parent];
    arr[parent] = temp;
    heapify_top_bottom(arr,min,size);
  }
}

KthLargest* kthLargestCreate(int k, int* nums, int numsSize) {
  KthLargest* obj = (KthLargest*)malloc(sizeof(KthLargest));
  obj->top =- 1;
  obj->heap_size = k;
  obj->arr = (int*)calloc(k,sizeof(int));

  //add stream elements to the heap till its capacity
  //then only insert if val > root_val
  for(int i=0; i<numsSize; i++) {
    if(i < k) {
      obj->arr[++(obj->top)] = nums[i];
      heapify_bottom_top(obj->arr, obj->top);
    } else {
      if(obj->arr[0] < nums[i]) {
	obj->arr[0] = nums[i];
	heapify_top_bottom(obj->arr,0, obj->top);
      }
    }
  }
  return obj;
}

int kthLargestAdd(KthLargest* obj, int val) {
  //if the heap is empty or not filled to its capacity, populate first with incoming elements
  if(obj->top < 0 || obj->top < (obj->heap_size)-1) {
    obj->arr[++(obj->top)] = val;
    heapify_bottom_top(obj->arr, obj->top);
  } else if(obj->arr[0] < val){
    obj->arr[0] = val;
    heapify_top_bottom(obj->arr,0, obj->top);
  }
  return obj->arr[0];
}

void kthLargestFree(KthLargest* obj) {
  free(obj->arr);
  free(obj);
}

int main (int argc, char **argv) {
  int ret = 0;
  int arr[] = {4, 5, 8, 2};
  int k = 3;
  int numsSize = 4;

  KthLargest* kthLargest = kthLargestCreate(k, arr, numsSize);
  ret = kthLargestAdd(kthLargest, 3);   // return 4
  debug("Output = %d", ret);
  ret = kthLargestAdd(kthLargest, 5);   // return 5
  debug("Output = %d", ret);
  ret = kthLargestAdd(kthLargest, 10);  // return 5
  debug("Output = %d", ret);
  ret = kthLargestAdd(kthLargest, 9);   // return 8
  debug("Output = %d", ret);
  ret = kthLargestAdd(kthLargest, 4);   // return 8
  debug("Output = %d", ret);

  kthLargestFree(kthLargest);
  return 0;
}

/**
   => ./a.out
   [main] L=119 :Output = 4
   [main] L=121 :Output = 5
   [main] L=123 :Output = 5
   [main] L=125 :Output = 8
   [main] L=127 :Output = 8
**/
