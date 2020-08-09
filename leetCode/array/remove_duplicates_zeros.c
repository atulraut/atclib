/***
 * LeetCode :  https://leetcode.com/problems/duplicate-zeros/
 * Given a fixed length array arr of integers, duplicate each occurrence of
 * zero, shifting the remaining elements to the right.
 * Note that elements beyond the length of the original array are not written.
 * Do the above modifications to the input array in place, do not return
 * anything from your function.
 * Example 1:
 * Input: [1,0,2,3,0,4,5,0]
 * Output: null
 * Explanation: After calling your function, the input array is
 * modified to: [1,0,0,2,3,0,0,4]
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void duplicateZeros(int* arr, int arrSize){
  int temp = 0;
  int i = 0;
  while(i < arrSize) {
    if(arr[i] == 0) {
      for(int j = arrSize - 2; j > i; j--) {
        printf ("j=%d i=%d \n", j, i);
        arr[j + 1] = arr[j];
      }
      if(i == arrSize - 1) {
        break;
      }
      arr[i + 1] = 0;
      i += 2;
      continue;
    }
    i++;
  }
}

int main() {
  int arr[] = {1,0,2,3,0,4,5,0};
  int asz = sizeof(arr)/sizeof(arr[0]);
  duplicateZeros(arr, asz);

  for (int i=0; i<8; i++) {
    printf ("-> %d\n", arr[i]);
  }
}
