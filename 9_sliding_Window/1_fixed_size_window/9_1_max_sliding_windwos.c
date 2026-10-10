/***
    Hard: 239. Sliding Window Maximum
    Max value in window of size K.
    e.g. 1 3 -1 max is 3.

    https://leetcode.com/problems/sliding-window-maximum/
    Ref: https://www.youtube.com/watch?v=LiSdD3ljCIE&t=12s
    No. of Windows = N-K+1

    You are given an array of integers nums, there is a sliding
    window of size k which is moving from the very left of the
    array to the very right. You can only see the k numbers in
    the window. Each time the sliding window moves right by
    one position.

    Return the max sliding window.

    Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
    Output: [3,3,5,5,6,7]
    Explanation:
    Window position                Max
    ---------------               -----
    [1  3  -1] -3  5  3  6  7       3
    1 [3  -1  -3] 5  3  6  7       3
    1  3 [-1  -3  5] 3  6  7       5
    1  3  -1 [-3  5  3] 6  7       5
    1  3  -1  -3 [5  3  6] 7       6
    1  3  -1  -3  5 [3  6  7]      7

    Input: nums = [1], k = 1
    Output: [1]

    Input: nums = [1,-1], k = 1
    Output: [1,-1]

    Input: nums = [9,11], k = 2
    Output: [11]

    Input: nums = [4,-2], k = 2
    Output: [4]

    Constraints:
    1 <= nums.length <= 105
    -104 <= nums[i] <= 104
    1 <= k <= nums.length

    Date: 04/18/2020, April.
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
/**
   Pattern: Fixed-size Sliding Window + Monotonic Deque
   Difficulty: Hard
   Optimal Time: O(n) | Space: O(k)

   This problem is different from the previous fixed-size sliding-window problems
   because we need to find the maximum element in every window, not the sum.

   The deque is represented using a simple array and two indices:
   int front = 0;
   int back = 0;

   Here, front is the first valid element, and back is the position where
   the next element will be inserted.
**/

int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
  *returnSize = 0;

  if (numsSize == 0 || k <= 0 || k > numsSize)
    return NULL;

  int *result = malloc((numsSize - k + 1) * sizeof(int));
  int *dq = malloc(numsSize * sizeof(int));

  if (!result || !dq) {
    free(result);
    free(dq);
    return NULL;
  }

  int front = 0;
  int back = 0;
  int count = 0;

  for (int i = 0; i < numsSize; i++) {

    // 1. Remove outgoing index
    if (front < back && dq[front] <= i - k)
      front++;

    // 2. Remove smaller values from the back
    while (front < back && nums[dq[back - 1]] <= nums[i])
      back--;

    // 3. Add incoming index
    dq[back++] = i;

    // 4. Record maximum when window is full
    if (i >= k - 1)
      result[count++] = nums[dq[front]];
  }

  free(dq);
  *returnSize = count;
  return result;
}

int main() {
  int nums[] = {1,3,-1,-3,5,3,6,7};
  int numsSize = sizeof(nums)/ sizeof(nums[0]);
  int k = 3;
  int returnSize;

  int* result = maxSlidingWindow(nums, numsSize, k, &returnSize);
  for(int i=0; i<returnSize; i++)
    debug("Output = %d", result[i]);

  if(result)
    free(result);
  return 0;
}

/**
   [main] L=128 :Output = 3
   [main] L=128 :Output = 3
   [main] L=128 :Output = 5
   [main] L=128 :Output = 5
   [main] L=128 :Output = 6
   [main] L=128 :Output = 7
**/
