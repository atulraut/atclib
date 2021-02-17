/***
     LeetCode : Combination Sum

     https://leetcode.com/explore/featured/card/october-leetcoding-challenge/559/week-1-october-1st-october-7th/3481/
     Given an array of distinct integers candidates and a target integer target, return a list of
     all unique combinations of candidates where the chosen numbers sum to target. You may return
     the combinations in any order.
     The same number may be chosen from candidates an unlimited number of times. Two combinations
     are unique if the frequency of at least one of the chosen numbers is different.
     It is guaranteed that the number of unique combinations that sum up to target is less than
     150 combinations for the given input.
     Example 1:
     Input: candidates = [2,3,6,7], target = 7
     Output: [[2,2,3],[7]]
     Explanation:
     2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
     7 is a candidate, and 7 = 7.
     These are the only two combinations.
     Example 2:
     Input: candidates = [2,3,5], target = 8
     Output: [[2,2,2,2],[2,3,3],[3,5]]
     Example 3:
     Input: candidates = [2], target = 1
     Output: []
     Example 4:
     Input: candidates = [1], target = 1
     Output: [[1]]
     Example 5:
     Input: candidates = [1], target = 2
     Output: [[1,1]]
     Constraints:
     1 <= candidates.length <= 30
     1 <= candidates[i] <= 200
     All elements of candidates are distinct.
     1 <= target <= 500
     Logic : https://www.youtube.com/watch?v=7IQHYbmuoVU
*/

#include "../../at_lib.h"


void subroutine(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes, int* temp, int step, int start,int** ans){
	if (target == 0){
		ans[*returnSize] = malloc(sizeof(int)*step);
		for (int i = 0; i < step; i++){
			ans[*returnSize][i] = temp[i];
		}
		returnColumnSizes[0][(*returnSize)++] = step;
		return;

	}
	if (start >= candidatesSize ||  target < 0){return;}

	temp[step] = candidates[start];
	if (target - candidates[start] >= 0){

		subroutine(candidates, candidatesSize, target - candidates[start], returnSize, returnColumnSizes, temp, step + 1, start, ans);
	}
	subroutine(candidates, candidatesSize, target , returnSize, returnColumnSizes, temp, step, start + 1, ans);
	if (target - candidates[start] < 0){return;}
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
//int** combinationSum(int* nums, int size, int target, int** colSizes, int* returnSize)
int** combinationSum(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes){
    int* temp = malloc(sizeof(int)*50);
	*returnSize = 0;
	returnColumnSizes[0] = malloc(sizeof(int)*256);
	int** ans = malloc(sizeof(int*)*256);
	subroutine(candidates, candidatesSize, target, returnSize, returnColumnSizes, temp, 0, 0, ans);
	return ans;
}

int main () {
  int nums [] = {2, 3, 6, 7};
  int target = 7;
  //int nums [] = {3, 2, 3};
  int sz = sizeof(nums) / sizeof(nums[0]);
  int retSz;
  int *ret;

  ret = majorityElement(nums, sz, &retSz);

  int** combinationSum(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes){

  for (int i=0; i<retSz; i++)
    printf ("[%s] --> %d \n",__func__,  ret[i]);
}
