/***
 * LeetCode : Contiguous Array
 * Given a binary array, find the maximum length of a contiguous subarray
 * with equal number of 0 and 1.
 * Example 1:
 * Input: [0,1]
 * Output: 2
 * Explanation: [0, 1] is the longest contiguous subarray with equal
 * number of 0 and 1.
 * Example 2:
 * Input: [0,1,0]
 * Output: 2
 * Explanation: [0, 1] (or [1, 0]) is a longest contiguous subarray with
 * equal number of 0 and 1.
 * Note: The length of the given binary array will not exceed 50,000.
 * Logic : https://www.youtube.com/watch?v=9ZyLjjk536U
 * Date: 06/20/2020 07:12PM Saturday.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Approch 2: */
int findMaxLength(int* nums, int numsSize) {
  int maxLen = 0;
  printf ("[%s] 1- sizeof(int) = %d Total=%d L=%d \n", __func__, sizeof(int), sizeof(int)*(numsSize*2+1), __LINE__);
  int *tb =(int *)malloc(sizeof(int)*(numsSize*2+1));
  int sum  = 0;
  int tbIdx = 0;
  int i,key;
  int tempLen = 0;

  memset(tb, -2, sizeof(int)*(numsSize*2+1));
  tb[numsSize] = -1;

  printf ("[%s] 2- tb[%d]=%d numsSize=%d, L=%d \n", __func__, numsSize, tb[numsSize], numsSize,  __LINE__);
  for(i=0; i<numsSize; i++) {
    printf ("[%s] 3- tb[%d]=%d L=%d \n", __func__, i, tb[i],  __LINE__);
  }

  for(i=0; i<numsSize; i++) {
    sum += (nums[i] == 0) ? -1 : 1;
    if(tb[sum + numsSize] >= -1) {
      tempLen = i - tb[sum+ numsSize];
      if(maxLen < tempLen)
	maxLen = tempLen;
    } else
      tb[sum + numsSize] = i;
  }
  free(tb);
  return maxLen;
}

int main () {
  int arr[] = {0, 1, 1};
  int sz = sizeof(arr) / sizeof(arr[0]);

  int ret = findMaxLength(arr, sz);
  printf ("[%s] ret=%d L=%d \n", __func__, ret,  __LINE__);

  return 0;
}
