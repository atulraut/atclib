/***
    LeetCode: Kth Largest Element in an Array
    https://leetcode.com/problems/kth-largest-element-in-an-array/
    Find the kth largest element in an unsorted array. Note that it is
    the kth largest element in the sorted order, not the kth distinct element.
    Example 1:
    Input: [3,2,1,5,6,4] and k = 2
    Output: 5
    Example 2:
    Input: [3,2,3,1,2,4,5,5,6] and k = 4
    Output: 4
    Note:
    You may assume k is always valid, 1 ≤ k ≤ array's length.
    Ref: https://www.youtube.com/watch?v=COk73cpQbFQ
    4MS : https://leetcode.com/problems/kth-largest-element-in-an-array/discuss/162504/Standard-C-solution-using-recursion
*/
#include <stdio.h>
#include <string.h>
#define true 1

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

/***
 // Default quick_sort Implementation.
 void quick_sort(int *a, int start, int end) {
 if(start < end) {
 int partitionIndex = partition(a, start, end);
 quick_sort(a, start, partitionIndex-1);
 quick_sort(a, partitionIndex+1, end);
 }
 }
*/

int findKthLargest(int* nums, int numsSize, int k) {
  k = numsSize-k;
  int begin = 0;
  int end = numsSize-1;
  while(true) {
    int partitionIndex = partition(nums, begin, end);
    if(partitionIndex == k)
      return nums[k];
    if(partitionIndex > k)
      end = partitionIndex - 1;
    else
      begin = partitionIndex + 1;
  }
}

int main() {
  //    int arr[] = {12, 3, 5, 7, 19};
  //    int arr[] = {3,2,1,5,6,4};
  int arr[] = {3,5,1,5,6,4};
  int n = sizeof(arr)/sizeof(arr[0]), k = 2;
  printf ("K'th smallest element is --> [%d] \n", findKthLargest(arr, n, k));
  return 0;
}
/***
    => ./a.out
    K'th smallest element is --> [5
*/
