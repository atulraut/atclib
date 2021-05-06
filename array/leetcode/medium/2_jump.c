/***
    Jump Game II
    Given an array of non-negative integers nums, you are initially
    positioned at the first index of the array.

    Each element in the array represents your maximum jump length
    at that position.
    Your goal is to reach the last index in the minimum number of jumps.

    You can assume that you can always reach the last index.

    Input: nums = [2,3,1,1,4]
    Output: 2
    Explanation: The minimum number of jumps to reach the last index is 2.
    Jump 1 step from index 0 to 1, then 3 steps to the last index.

    Input: nums = [2,3,0,1,4]
    Output: 2

    Constraints:
    1 <= nums.length <= 1000
    0 <= nums[i] <= 105
    https://leetcode.com/problems/jump-game-ii/

    Date: 5/5/2021
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
#define max(x, y) (((x) > (y)) ? x : y)

int jump(int* nums, int numsSize) {
int jumps = 0, currentJumpEnd = 0, farthest = 0;

for (int i = 0; i < numsSize - 1; i++) {
  // we continuously find the how far we can reach in the current jump
  farthest = max(farthest, i + nums[i]);
  // if we have come to the end of the current jump,
  // we need to make another jump
  if (i == currentJumpEnd) {
    jumps++;
    currentJumpEnd = farthest;
  }
 }
return jumps;
}

int jump2(int* nums, int numsSize) {
  int last = 0;
  int max = nums[0];
  int new_max;
  int new_last;
  int step = 1;

  if (numsSize == 1)
    return 0;

  while (max < numsSize - 1) {
    new_max = 0;
    for (int i = last + 1; i <= max; ++i) {
      if (i + nums[i] > new_max) {
	new_max = i + nums[i];
	new_last = i;
      }
    }

    max = new_max;
    last = new_last;
    step++;
  }

  return step;
}


int main () {
  int ret = 0;
  int arr[] = {2,3,1,1,4};
  int sz = 5;

  ret= jump2(arr, sz);

  debug("Output = %d", ret);
  return 0;
}

/**
   Algorithm

   Initialize three integer variables: jumps to count the number of jumps,
   currentJumpEnd to mark the end of the range that we can jump to, and
   farthest to mark the farthest place that we can reach. Set each
   variable to zero.
   Iterate over nums. Note that we exclude the last element from our
   iteration because as soon as we reach the last element, we do not
   need to jump anymore.
   Update farthest to i + nums[i] if the latter is larger.
   If we reach currentJumpEnd, it means we finished the current jump,
   and can begin checking the next jump by setting currentJumpEnd = farthest.

   Return jumps.
**/

/**
   => ./a.out
   [main] L=94 :Output = 2
**/
