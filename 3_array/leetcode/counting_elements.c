/*
Given an integer array arr, count element x such that x + 1
is also in arr.
If there're duplicates in arr, count them seperately.
Input: arr = [1,2,3]
Output: 2
Explanation: 1 and 2 are counted cause 2 and 3 are in arr.
Ref:
https://leetcode.com/explore/featured/card/30-day-leetcoding-challenge/528/week-1/3289/
https://www.youtube.com/watch?v=GmHengYK3Nk
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  Approch 2: Use hashset to store all elements.
*/

void insertionSort(int list[], int n) {
  // sort list[0] to list[n-1] in ascedning order
  for(int h=1; h<n; h++) {
    int key = list[h];
    int j=h-1; /* start comparing with previous item */
    while(j>=0 && key < list[j]) { /*Copy Elememnt from Unsorted(list[j]) to Sorted Array (list[j+1])*/
      list[j+1] = list[j];
      --j;
    }
    list[j+1] = key; /* key will create hole, copy that at last*/
  }//end for
}//end insertionSort


/*
   Approch 1: Loop again to count all valid elements.
*/
int countElements(int* arr, int arrSize){
  int left = 0, right = 1;
  int count = 0;

  if (arrSize <= 1)
    return 0;

  insertionSort(arr, arrSize);

  while (right < arrSize) {
    if (arr[right] == 1+arr[left]) {
      count += (right - left);
      left = right;
      right += 1;
    } else if (arr[right] == arr[left]) {
      right += 1;
    } else {
      left = right;
      right += 1;
    }
  }
  return count;
}

int main() {
  //int arr[] = {1,2,3};   /*O/P = 2*/
  //int arr[] = {1,1,3,3,5,5,7,7};  /*O/P = 0*/
  int arr[] = {1,1,2,2}; /*O/P = 2*/
  int arrSize = sizeof(arr) / sizeof(arr[0]);
  int ret =  countElements(arr, arrSize);
  printf ("[%s] o/p = %d L=%d \n", __func__, ret, __LINE__);
  return 0;
}
