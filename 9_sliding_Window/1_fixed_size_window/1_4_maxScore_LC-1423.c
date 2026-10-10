/***

    https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/

    1423. Maximum Points You Can Obtain from Cards

    There are several cards arranged in a row, and each card
    has an associated number of points. The points are given in
    the integer array cardPoints.

    In one step, you can take one card from the beginning or from
    the end of the row. You have to take exactly k cards.

    Your score is the sum of the points of the cards you have taken.

    Given the integer array cardPoints and the integer k, return the
    maximum score you can obtain.

    Input: cardPoints = [1,2,3,4,5,6,1], k = 3
    Output: 12
    Explanation: After the first step, your score will always be 1. However,
    choosing the rightmost card first will maximize your total score.
    The optimal strategy is to take the three cards on the right,
    giving a final score of 1 + 6 + 5 = 12.

    Input: cardPoints = [2,2,2], k = 2
    Output: 4
    Explanation: Regardless of which two cards you take, your score will always be 4.

    Input: cardPoints = [9,7,7,9,7,7,9], k = 7
    Output: 55
    Explanation: You have to take all the cards. Your score is the sum of points of all cards.

    Constraints:
    1 <= cardPoints.length <= 105
    1 <= cardPoints[i] <= 104
    1 <= k <= cardPoints.length

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Sat Oct 10 14:09:55 PDT 2026
    Folsom, CA.
 */

/*----------------------------------- Header --------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h> // va_arg
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */

#define debug(str,args...) printf("L=[%d][%s]->[%s] :| "str"\n",__LINE__,__FILE__, __func__, ##args)

/**
   How to identify the sliding-window pattern
   We must pick exactly k cards, but the cards can come from both ends.
   The key observation is that every valid selection consists of:
   - x cards from the left
   - k - x cards from the right
   We can start by picking all k cards from the left, then gradually
   replace one left card with one right card.
   This is a fixed-size sliding window across the two ends.

   Understand the important two lines
   sum -= cardPoints[k - 1 - i];  // Outgoing
   sum += cardPoints[n - 1 - i];  // Incoming
   -----------------------------------------------
   For k = 3, n = 7:
   -----------------------------------------------
   i	Remove from left	Add from right
   -----------------------------------------------
   0	cardPoints[2] = 3	cardPoints[6] = 1
   1	cardPoints[1] = 2	cardPoints[5] = 6
   2	cardPoints[0] = 1	cardPoints[4] = 5
   -----------------------------------------------
   Notice how we remove the selected left cards in reverse order
   and add the right cards in reverse order.

   Approach	Key idea	Time
   Two-end sliding window	Start with K left cards, replace with right cards	O(k)
   Minimum remaining window	Total sum − minimum subarray of size N−K	O(n)
**/
int maxScore(int* cardPoints, int cardPointsSize, int k) {

  int n = cardPointsSize;
  int sum = 0;
  int maxSum = 0;

  // Step 1: Pick first k cards from left - Calculate first window
  for (int i = 0; i < k; i++)
    sum += cardPoints[i];

  maxSum = sum;

  // Step 2: Replace left cards with right cards
  for (int i = 0; i < k; i++) {

    sum -= cardPoints[k - 1 - i]; // Remove Outgoing left
    sum += cardPoints[n - 1 - i]; // Add Incoming right

    if (sum > maxSum)
      maxSum = sum;
  }

  return maxSum;
}

// Minimum remaining window
int maxScore_o(int* cardPoints, int n, int k) {
  int windowSize = n - k;
  int total = 0;
  int sum = 0;
  int minSum = INT_MAX;

  if (windowSize == 0) {
    for (int i = 0; i < n; i++)
      total += cardPoints[i];
    return total;
  }

  // Total sum and initial window
  for (int i = 0; i < n; i++) {
    total += cardPoints[i];

    if (i < windowSize)
      sum += cardPoints[i];
  }

  minSum = sum;

  // Fixed-size sliding window
  for (int i = windowSize; i < n; i++) {

    sum += cardPoints[i];              // Incoming
    sum -= cardPoints[i - windowSize]; // Outgoing

    if (sum < minSum)
      minSum = sum;
  }
  return total - minSum;
}

void test() {
  int ret = 0;
  int cardPoints[] = {1,2,3,4,5,6,1};
  int k = 3;
  int sz = 7;
  ret = maxScore(cardPoints, sz, k);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   L=[128][9_sliding_Window/1_fixed_size_window/1_4_maxScore_LC-1423.c]->[test] :| Output = 12
**/
