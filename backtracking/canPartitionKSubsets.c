/***
    https://leetcode.com/problems/partition-to-k-equal-sum-subsets/
    Partition to K Equal Sum Subsets

    Given an integer array nums and an integer k,
    return true if it is possible to divide thi
    array into k non-empty subsets whose sums are
    all equal.

    Input: nums = [4,3,2,3,5,2,1], k = 4
    Output: true
    Explanation: It's possible to divide it into
    4 subsets (5), (1, 4), (2,3), (2,3) with equal sums.

    Input: nums = [1,2,3,4], k = 3
    Output: false

    Constraints:
    1 <= k <= nums.length <= 16
    1 <= nums[i] <= 104
    The frequency of each element is in the range [1, 4].

    Date: 30 Sept 2021
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

bool can_partition_subset(int* nums, int nums_size, int k,
			  int from, int bitset, int cur_sum,
			  int target)
{
  if( k <= 1 )
    return true;

  if( cur_sum == target )
    return can_partition_subset( nums, nums_size, k - 1, 0, bitset, 0, target );

  for( int i = from; i < nums_size; ++i ) {
    int bit = 1 << i;

    if( ( bitset & bit ) == 0 ) {
      int n = nums[ i ];

      if( cur_sum + n > target ) {
	break;
      }

      if( can_partition_subset( nums, nums_size, k, i + 1, bitset | bit, cur_sum + n, target ) ) {
	return true;
      }
    }
  }

  return false;
}

void insert_sort(int* nums, int nums_size) {
  for( int i = 1; i < nums_size; ++i ) {
    int j = i;
    int target = nums[ j ];

    while( j > 0 && nums[ j - 1 ] > target ) {
      nums[ j ] = nums[ j - 1 ];
      --j;
    }
    nums[ j ]  = target;
  }
}

/* Backtracking */
bool canPartitionKSubsets(int* nums, int numsSize, int k) {
  int sum = 0;
  for( int i = 0; i < numsSize; ++i ) {
    sum += nums[ i ];
  }
  if( sum % k != 0 ) {
    return false;
  }

  insert_sort( nums, numsSize );
  return can_partition_subset( nums, numsSize, k, 0, 0, 0, sum / k );   ;
}

int main (int argc, char **argv) {
  int ret = 0;
  int nums[] ={4,3,2,3,5,2,1};
  int numsSize = 7;
  int k = 4;

  ret = canPartitionKSubsets(nums, numsSize, k);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=102 :Output = 1
**/
