/***
    Hard: 239. Sliding Window Maximum
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
 * Note: The returned array must be malloced, assume caller calls free().
 */

#if 0

int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
  debug("Enter!");
  if (nums == NULL || numsSize < k) return NULL;
  *returnSize = numsSize - k + 1;
  int *res = (int *) malloc(*returnSize * sizeof(int));

  int deque[numsSize];
  int head = 0;
  int tail = -1;
  int size = 0;

  for (int i = 0; i < numsSize; i++) {
    int tmp = nums[i];
    while (size > 0 && tmp >= nums[deque[tail]]) {
      tail--;
      size--;
    }
    deque[++tail] = i;
    size++;
    while (size > 0 && i - deque[head] + 1 > k) {
      head++;
      size--;
    }
    if (i >= k - 1) {
      res[i - k + 1] = nums[deque[head]];
    }
  }

  return res;
}

#else

struct window_seq{
  int *valSeq;
  int *posSeq;
  int head;
  int tail;
  int size;
  int isEmpty;
};

void addValToWinSeq(struct window_seq *winSeq, int val, int pos) {
  if (winSeq->isEmpty) {
    winSeq->valSeq[0] = val;
    winSeq->posSeq[0] = pos;
    winSeq->head = 0;
    winSeq->tail = 0;
    winSeq->isEmpty = 0;
  } else {
    int idx;

    for (idx = winSeq->tail; idx != winSeq->head; idx = (idx + winSeq->size - 1) % winSeq->size) {
      if (winSeq->valSeq[idx] > val) {
	break;
      }
    }

    int nextIdx;

    if (idx == winSeq->head) {
      if (winSeq->valSeq[idx] <= val) {
	nextIdx = idx;
      } else {
	nextIdx = (idx + 1) % winSeq->size;
      }
    } else {
      nextIdx = (idx + 1) % winSeq->size;
    }

    winSeq->valSeq[nextIdx] = val;
    winSeq->posSeq[nextIdx] = pos;
    winSeq->tail = nextIdx;
  }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
  assert(numsSize >= k);

  debug("Enter!");
  int *result = malloc(sizeof(int) * (numsSize - k + 1));
  struct window_seq winSeq;
  int i;

  winSeq.valSeq = malloc(sizeof(int) * k);
  winSeq.posSeq = malloc(sizeof(int) * k);
  winSeq.head = 0;
  winSeq.tail = 0;
  winSeq.size = k;
  winSeq.isEmpty = 1;
  *returnSize = 0;

  for (i = 0; i < k; i++) {
    addValToWinSeq(&winSeq, nums[i], i);
  }

  while(1) {
    result[*returnSize] = winSeq.valSeq[winSeq.head];
    *returnSize = *returnSize + 1;

    if (winSeq.posSeq[winSeq.head] + k <= i) {
      if (winSeq.tail == winSeq.head) {
	winSeq.head = 0;
	winSeq.tail = 0;
	winSeq.isEmpty = 1;
      } else
	winSeq.head = (winSeq.head + 1) %  winSeq.size;
    }

    if (i >= numsSize)
      break;
    addValToWinSeq(&winSeq, nums[i], i);
    i++;
  }

  free(winSeq.valSeq);
  free(winSeq.posSeq);
  return result;
}
#endif

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
   => ./a.out
   [maxSlidingWindow] L=66 :Enter!
   [main] L=209 :Output = 3
   [main] L=209 :Output = 3
   [main] L=209 :Output = 5
   [main] L=209 :Output = 5
   [main] L=209 :Output = 6
   [main] L=209 :Output = 7
**/
