/***
    https://leetcode.com/problems/median-of-two-sorted-arrays/
    Hard : Median of Two Sorted Arrays

    Given two sorted arrays nums1 and nums2 of size m and n
    respectively, return the median of the two sorted arrays.

    The overall run time complexity should be O(log (m+n)).

    Input: nums1 = [1,3], nums2 = [2]
    Output: 2.00000
    Explanation: merged array = [1,2,3] and median is 2.
    Example 2:

    Input: nums1 = [1,2], nums2 = [3,4]
    Output: 2.50000
    Explanation: merged array = [1,2,3,4] and median
    is (2 + 3) / 2 = 2.5.

    Input: nums1 = [0,0], nums2 = [0,0]
    Output: 0.00000

    Input: nums1 = [], nums2 = [1]
    Output: 1.00000

    Input: nums1 = [2], nums2 = []
    Output: 2.00000

    Constraints:

    nums1.length == m
    nums2.length == n
    0 <= m <= 1000
    0 <= n <= 1000
    1 <= m + n <= 2000
    -106 <= nums1[i], nums2[i] <= 106

    Date: 17102021 - Oct
    Fair Oaks, CA.
*/

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

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
  int i=0,j=0,k=0;
  int totalSize = nums1Size+nums2Size;
  int result[totalSize];

  while(i < nums1Size && j < nums2Size) {
    if(nums1[i] <= nums2[j]) {
      result[k] = nums1[i];
      i++;
    } else {
      result[k] = nums2[j];
      j++;
    }
    k++;
  }
  while(i < nums1Size) {
    result[k] = nums1[i];
    i++;
    k++;
  }
  while(j < nums2Size) {
    result[k] = nums2[j];
    j++;
    k++;
  }

  double median = 0.0;
  if (((totalSize) % 2) == 0)
    median = (result[(totalSize/2)-1]+result[(totalSize/2)])/2.0;
  else
    median = result[(totalSize/2)];
  return median;

}

/**
   Algo : Wrong Answer wont pass all test cases
   Get Total array Size, should gives you median Index as well.
   Allocate new array of new size.
   Merge Sort
   return median Index.
**/
double findMedianSortedArrays2(int* nums1, int nums1Size, int* nums2, int nums2Size) {
  int newSz = nums1Size + nums2Size;
  int median = newSz/2;
  double* final = (double *)malloc(sizeof(double) * newSz);
  int i = 0,  j = 0, k = 0; // Index of 2 arrays to be sorted

  debug("median = %d", median);
  /* Merge Sort */
  while (i < nums1Size && j < nums2Size) {
    if (nums1[i] < nums2[j])
      final[k++] = nums1[i++];
    else
      final[k++] = nums2[j++];
  } // for ends

  if (i == nums1Size) { // nums1 ended, copy remain nums2 to final
    for (; j<nums2Size; ++j)
      final[k++] = nums2[j];
  } else {
    final[k++] = nums1[i];
  }
  for (int i=0; i<newSz; ++i) {
    debug("-- %f", final[i]);
  }
  return final[median-1];
}

int main (int argc, char **argv) {
  double ret = 0;
  int nums1[] = {1, 3, 5};
  int nums1Size = 3;
  int nums2[] = {2, 4, 6};
  int nums2Size = 3;

  ret = findMedianSortedArrays(nums1, nums1Size, nums2, nums2Size);
  debug("Output = %f", ret);
  return 0;
}

/**

 **/
