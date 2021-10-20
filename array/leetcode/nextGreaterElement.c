/***
    https://leetcode.com/problems/next-greater-element-i/
    Next Greater Element I

    The next greater element of some element x in an array is
    the first greater element that is to the right of x in the same array.

    You are given two distinct 0-indexed integer arrays nums1
    and nums2, where nums1 is a subset of nums2.

    For each 0 <= i < nums1.length, find the index j such that
    nums1[i] == nums2[j] and determine the next greater element
    of nums2[j] in nums2. If there is no next greater element,
    then the answer for this query is -1.

    Return an array ans of length nums1.length such that ans[i]
    is the next greater element as described above.

    Input: nums1 = [4,1,2], nums2 = [1,3,4,2]
    Output: [-1,3,-1]
    Explanation: The next greater element for each value of nums1 is as follows:
    - 4 is underlined in nums2 = [1,3,4,2]. There is no next greater element, so the answer is -1.
    - 1 is underlined in nums2 = [1,3,4,2]. The next greater element is 3.
    - 2 is underlined in nums2 = [1,3,4,2]. There is no next greater element, so the answer is -1.

    Input: nums1 = [2,4], nums2 = [1,2,3,4]
    Output: [3,-1]
    Explanation: The next greater element for each value of nums1 is as follows:
    - 2 is underlined in nums2 = [1,2,3,4]. The next greater element is 3.
    - 4 is underlined in nums2 = [1,2,3,4]. There is no next greater element, so the answer is -1.

    Constraints:
    1 <= nums1.length <= nums2.length <= 1000
    0 <= nums1[i], nums2[i] <= 104
    All integers in nums1 and nums2 are unique.
    All the integers of nums1 also appear in nums2.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings nextGreaterElement.c -lm

    Date:  20 Oct 2021
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
 * : nums1 = [4,1,2], nums2 = [1,3,4,2]
 */
int* nextGreaterElement(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
  int*vgreaters = malloc(sizeof(int) * nums1Size);

  for(int i=0; i<nums1Size; ++i) {
    int cur = nums1[i];
    int greaterNum = -1;
    int j=0;
    for(; j<nums2Size; ++j) {
      if(nums2[j] == cur)
	break;
    }
    for(; j<nums2Size; ++j) {
      if(nums2[j]>cur) {
	greaterNum = nums2[j];
	break;
      }
    }
    greaters[i] = greaterNum;
  }

  *returnSize = nums1Size;
  return greaters;
}

int main (int argc, char **argv) {
  int* ret;
  int nums1[] = {4,1,2};
  int nums1Size= sizeof(nums1)/sizeof(nums1[0]);
  int nums2[] = {1,3,4,2};
  int nums2Size = sizeof(nums2)/sizeof(nums2[0]);;
  int returnSize;

  ret = nextGreaterElement(nums1, nums1Size, nums2, nums2Size, &returnSize);
  for (int i=0; i<returnSize; ++i)
    debug("Output = %d", ret[i]);
  free(ret);
  return 0;
}

/**
   => ./a.out
   [main] L=95 :Output = -1
   [main] L=95 :Output = 3
**/
