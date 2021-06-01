/***
    Medium: 462. Minimum Moves to Equal Array Elements II
    https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/

    Given an integer array nums of size n, return the minimum number
    of moves required to make all array elements equal.

    In one move, you can increment or decrement an element of the array by 1.


    Input: nums = [1,2,3]
    Output: 2
    Explanation:
    Only two moves are needed (remember each move increments or decrements one element):
    [1,2,3]  =>  [2,2,3]  =>  [2,2,2]

    Input: nums = [1,10,2,9]
    Output: 16

    Constraints:
    n == nums.length
    1 <= nums.length <= 105
    -109 <= nums[i] <= 109

    Date: 19 May 2021.
    San Diego, CA.
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

void insertionSort(int list[], int n) {
  // sort list[0] to list[n-1] in ascedning order
  for(int h=1; h<n; h++) {
    int key = list[h];		/* I */
    int j=h-1; /* start comparing with previous item */
    while(j>=0 && key < list[j]) { /*Copy Elememnt from Unsorted(list[j]) to Sorted Array (list[j+1])*/
      list[j+1] = list[j];	/* II */
      --j;
    }
    list[j+1] = key; /* III - key will create hole, copy that at last*/
  }//end for
}

int minMoves2(int* nums, int numsSize) {
  insertionSort(nums, numsSize);

  int sum = 0;
  for (int i=0; i<numsSize; i++) {
    sum += abs(nums[numsSize / 2] - nums[i]);
  }
  return sum;
}

int main () {
  int ret = 0;
  int nums[] = {1, 2, 3};
  int nums1[] = {1, 10, 2, 9};
  int numsSize = sizeof(nums) / sizeof(nums[0]);

  ret = minMoves2(nums, numsSize);
  debug("Output = %d", ret);

  return 0;
}

/**
   => ./a.out
   [main] L=72 :Output = 2
**/
