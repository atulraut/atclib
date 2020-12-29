/*
  673. Number of Longest Increasing Subsequence
  Given an integer array nums, return the number of longest increasing subsequences.
  Notice that the sequence has to be strictly increasing.
  Example 1:
  Input: nums = [1,3,5,4,7]
  Output: 2
  Explanation: The two longest increasing subsequences are [1, 3, 4, 7] and [1, 3, 5, 7].
  Example 2:
  Input: nums = [2,2,2,2,2]
  Output: 5
  Explanation: The length of longest continuous increasing subsequence is 1,
  and there are 5 subsequences' length is 1, so output 5.
  Constraints:
  1 <= nums.length <= 2000
  -106 <= nums[i] <= 106
  Logic : https://www.youtube.com/watch?v=mouCn3CFpgg
  Date : 12/28/2020 Monday, San Diego, CA
***/

#include "../at_lib.h"

int findNumberOfLIS(int* nums, int numsSize){

  int * len = (int *) malloc(sizeof(int) * numsSize);
  int * cnt = (int *) malloc(sizeof(int) * numsSize);

  for (int i = 0; i < numsSize; i++) {
    len[i] = 1;
    cnt[i] = 1;
  }
  int max = 0;
  for (int i = 1; i < numsSize; i++) {
    for (int j = 0; j < i; j++) {
      if (nums[i] > nums[j]) {
	if (len[j]+1 > len[i]) {
	  len[i] = len[j]+1;
	  cnt[i] = cnt[j];
	} else if (len[j]+1 == len[i]) {
	  cnt[i] += cnt[j];
	}
      }
    }
  }

  for (int i = 0; i < numsSize; i++) {
    max = max > len[i] ? max : len[i];
  }

  int ans = 0;
  for (int i = 0; i < numsSize; i++)
    if (len[i] == max)
      ans += cnt[i];
  return ans;
}

int main() {
  int nums[] = {1, 3, 5, 4, 7};
  int numsSize = sizeof(nums) / sizeof (nums[0]);

  printf ("[%s] Op::-> %d L=%d \n", __func__, findNumberOfLIS(nums, numsSize), __LINE__);

  return 0;
}

/***
    => ./a.out
    [main] Op::-> 2 L=59

    Approach 1: Dynamic Programming
    Intuition and Algorithm :
    Suppose for sequences ending at nums[i], we knew the length length[i] of the
    longest sequence, and the number count[i] of such sequences with that length.

    For every i < j with A[i] < A[j], we might append A[j] to a longest subsequence
    ending at A[i]. It means that we have demonstrated count[i] subsequences of length length[i] + 1.

    Now, if those sequences are longer than length[j], then we know we have count[i]
    sequences of this length. If these sequences are equal in length to length[j],
    then we know that there are now count[i] additional sequences to be counted of
    that length (ie. count[j] += count[i]).
*/
