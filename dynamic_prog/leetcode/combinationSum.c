/***
    39. Combination Sum -Medium
    https://leetcode.com/problems/combination-sum/

    Given an array of distinct integers candidates and a target integer target,
    return a list of all unique combinations of candidates where the chosen
    numbers sum to target. You may return the combinations in any order.

    The same number may be chosen from candidates an unlimited number
    of times. Two combinations are unique if the frequency of at least
    one of the chosen numbers is different.

    It is guaranteed that the number of unique combinations that sum up
    to target is less than 150 combinations for the given input.

    Input: candidates = [2,3,6,7], target = 7
    Output: [[2,2,3],[7]]
    Explanation:
    2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
    7 is a candidate, and 7 = 7.
    These are the only two combinations.

    Input: candidates = [2,3,5], target = 8
    Output: [[2,2,2,2],[2,3,3],[3,5]]

    Input: candidates = [2], target = 1
    Output: []

    Input: candidates = [1], target = 1
    Output: [[1]]

    Input: candidates = [1], target = 2
    Output: [[1,1]]

    Constraints:
    1 <= candidates.length <= 30
    1 <= candidates[i] <= 200
    All elements of candidates are distinct.
    1 <= target <= 500

    Ref: https://www.youtube.com/watch?v=oBt53YbR9Kk&t=4398s - Seek:- 1:22:00-1:29:29

    Status : Partial Fixed.
    Date: June 5, 2021, 4:55AM.
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

static int cnt = 0;

bool canSum(int targetSum, int *candidates, int candidatesSize, int *memo) {
  debug("[XX] targetSum=%d", targetSum);
  if (memo[targetSum]) {
    debug("[ZZ] memo[%d] = %d", targetSum, memo[targetSum]);
    //++cnt;
    return memo[targetSum];
  }

  if (targetSum == 0)
    return true;
  if (targetSum < 0)
    return false;

  for (int i=0; i<candidatesSize; ++i) {
    int remainder = targetSum - candidates[i];
    if (canSum(remainder, candidates, candidatesSize, memo) == true) {
      debug("[AR]  candidates[%d] = %d remainder=%d memo[%d]=%d", i, candidates[i], remainder,  targetSum, memo[targetSum]);
      memo[targetSum] = true;
      //++cnt;
      return true;
    }
  }
  memo[targetSum] = false;
  return false;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** combinationSum(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes) {
  int **op;
  int *memo = (int *)calloc(500, sizeof(int));
  //  memo[candidatesSize-1] = {0};
  bool ret = canSum(target, candidates, candidatesSize, memo);
  debug ("return = %d cnt = %d", ret, cnt);
  return op;
}

int main () {
  int ret = 0;
  int candidates1[] = {1};
  int candidates[] = {2, 3, 5};
  int candidates2[] = {7, 14};
  int candidatesSize = sizeof(candidates) / sizeof(candidates[0]);
  int target1 = 2;
  int target = 8;
  int target2 = 300; // Seg fault - FixME
  int returnSize = 0;
  int* returnColumnSizes;

  int **op = combinationSum(candidates, candidatesSize, target, &returnSize, &returnColumnSizes);
  debug("Output = %d", ret);
  return 0;
}

/**

 **/
