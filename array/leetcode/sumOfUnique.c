/***
    1748. Sum of Unique Elements
    https://leetcode.com/problems/sum-of-unique-elements/
    You are given an integer array nums. The unique elements of an array are the
    elements that appear exactly once in the array.
    Return the sum of all the unique elements of nums.

    Example 1:
    Input: nums = [1,2,3,2]
    Output: 4
    Explanation: The unique elements are [1,3], and the sum is 4.
    Example 2:
    Input: nums = [1,1,1,1,1]
    Output: 0
    Explanation: There are no unique elements, and the sum is 0.
    Example 3:
    Input: nums = [1,2,3,4,5]
    Output: 15
    Explanation: The unique elements are [1,2,3,4,5], and the sum is 15.

    Constraints:
    1 <= nums.length <= 100
    1 <= nums[i] <= 100
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

struct stateType {
  bool visit:1;
  int freq:31;
};

int sumOfUnique(int* nums, int numsSize) {
  int i=0, j=0, sum = 0;
  bool ans = true;

  struct stateType *state = (struct stateType*)malloc(numsSize * sizeof(struct stateType));
  if (NULL == state)
    return ans;

  for (i=0; i<numsSize; i++) {
    if (state[i].visit == true)
      continue;

    state[i].visit = true;
    state[i].freq = 1;

    for (j=i+1; j<numsSize; j++) {
      if (nums[i] == nums[j]) {
	state[i].freq = state[i].freq+1;
	state[j].visit = true;
	//state[j].freq = state[i].freq;
      }
    }
  } // 1st For Ends

  for (i=0; i<numsSize; i++) {
    if (state[i].freq == 1) {
      debug ("freq=%d, nums[%d]=%d", state[i].freq, i, nums[i]);
      sum = sum + nums[i];
      debug ("sum = %d", sum);
    }
  }
  return sum;
}

int main () {
  int arr[] = {1, 2, 3, 2};
  //int arr[] = {1,1,1,1,1};
  int numsSize = sizeof(arr) / sizeof (arr[0]);

  int op = sumOfUnique(arr, numsSize);
  debug ("Output = %d ", op);

  return 0;
}
