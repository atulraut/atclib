/***
    Intersection of Two Arrays II

    Given two integer arrays nums1 and nums2, return
    an array of their intersection. Each element in
    the result must appear as many times as it shows
    in both arrays and you may return the result in
    any order.

    Input: nums1 = [1,2,2,1], nums2 = [2,2]
    Output: [2,2]
    Example 2:

    Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
    Output: [4,9]
    Explanation: [9,4] is also accepted.

    Constraints:

    1 <= nums1.length, nums2.length <= 1000
    0 <= nums1[i], nums2[i] <= 1000

    Follow up:
    What if the given array is already sorted? How
    would you optimize your algorithm?
    What if nums1's size is small compared to nums2's
    size? Which algorithm is better?
    What if elements of nums2 are stored on disk, and
    the memory is limited such that you cannot load
    all elements into the memory at once?

    https://leetcode.com/problems/intersection-of-two-arrays-ii/

    Date: 17 Sept 2021
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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int comp(const void *a, const void *b) {
  /* to prevent overflow */
  if(*(int *)a > *(int *)b) return 1;
  else if(*(int *)a < *(int *)b) return -1;
  return 0;
}

int* intersect(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
  int *ret = (int *)malloc(sizeof(int));
  *returnSize = 0;
  qsort(nums1, nums1Size, sizeof(int), comp);
  qsort(nums2, nums2Size, sizeof(int), comp);

  int i = 0, j =0;
  while(i < nums1Size && j < nums2Size) {
    if(nums1[i] < nums2[j])
      i++;
    else if(nums1[i] > nums2[j])
      j++;
    else {
      *returnSize = *returnSize + 1;
      ret = realloc(ret, sizeof(int) * (*returnSize));
      ret[*returnSize - 1] = nums1[i];
      i++;
      j++;
    }
  }
  return ret;
}

int main (int argc, char **argv) {
  int *ret = 0;

  int nums1[] = {1, 2, 2, 1};
  int nums1Size = 4;
  int nums2[] = {2, 2};
  int nums2Size = 2;
  int returnSize;

  ret = intersect(nums1, nums1Size, nums2, nums2Size, &returnSize);
  for (int i=0; i<returnSize; ++i)
    debug("Output = %d", ret[i]);

  return 0;
}

/**
   => ./a.out
   [main] L=95 :Output = 2
   [main] L=95 :Output = 2
**/
