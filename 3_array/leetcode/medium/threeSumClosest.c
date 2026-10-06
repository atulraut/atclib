/***
    3Sum Closest
    https://leetcode.com/problems/3sum-closest/

    Given an array nums of n integers and an integer target, find three
    integers in nums such that the sum is closest to target.
    Return the sum of the three integers. You may assume that
    each input would have exactly one solution.

    Input: nums = [-1,2,1,-4], target = 1
    Output: 2
    Explanation: The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).

    Constraints:
    3 <= nums.length <= 10^3
    -10^3 <= nums[i] <= 10^3
    -10^4 <= target <= 10^4

    Date: July 29, 2021.
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
}//end

int threeSumClosest23(int* nums, int numsSize, int target){
  int diff = INT_MAX, sz = numsSize;

  insertionSort(nums, sz);
  for (int i=0; i<sz; ++i)
    printf ("--> %d\n", nums[i]);

  for (int i = 0; i < sz && diff != 0; ++i) {
    int lo = i + 1, hi = sz - 1;
    debug ("FOR i=%d lo=%d hi=%d",i, lo, hi);
    while (lo < hi) {
      int sum = nums[i] + nums[lo] + nums[hi];
      debug ("sum=%d lo=%d hi=%d", sum, lo, hi);
      if (abs(target - sum) < abs(diff)) {
	diff = target - sum;
	debug ("target=%d sum=%d, diff=%d",target, sum, diff);
      }
      if (sum < target)
	++lo;
      else
	--hi;
    }
  }
  return target - diff;
}

#define ABS(x) ((x)<0?-(x):(x))

int comparefn( const void* a, const void* b) {
  int int_a = * ( (int*) a );
  int int_b = * ( (int*) b );

  if ( int_a == int_b ) return 0;
  else if ( int_a < int_b ) return -1;
  else return 1;
}

int threeSumClosest(int* nums, int numsSize, int target) {
  // sort the array
  qsort(nums, numsSize, sizeof(int), comparefn);

  int i, j, k, diff, min_diff = INT_MAX;

  for(i = 0 ; i < numsSize ; i++) {
    j = i + 1;
    k = numsSize - 1;
    while(j < k) {
      diff = nums[i] + nums[j] + nums[k] - target;

      if(diff == 0) {
	return target;
      } else {
	if(ABS(diff) < ABS(min_diff)) {
	  min_diff = diff;
	}
	if(diff < 0) {
	  j++;
	} else {
	  k--;
	}
      }
    }
  }
  return target + min_diff;
}
int main () {
  int ret = 0;

  int nums[] = {-1 ,2 ,1, -4};
  int numsSize = sizeof(nums)/sizeof(nums[0]);
  int target = 1;

  ret = threeSumClosest23(nums, numsSize, target);
  printf("\n");
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=114 :Output = 2
**/
