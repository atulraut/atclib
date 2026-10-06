/***
    https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/
    Two Sum II - Input array is sorted

    Given a 1-indexed array of integers numbers that is already
    sorted in non-decreasing order, find two numbers such that they
    add up to a specific target number. Let these two numbers be
    numbers[index1] and numbers[index2]
    where 1 <= first < second <= numbers.length.

    Return the indices of the two numbers, index1 and index2,
    as an integer array [index1, index2] of length 2.

    The tests are generated such that there is exactly
    one solution. You may not use the same element twice.

    Input: numbers = [2,7,11,15], target = 9
    Output: [1,2]
    Explanation: The sum of 2 and 7 is 9. Therefore index1 = 1, index2 = 2.

    Input: numbers = [2,3,4], target = 6
    Output: [1,3]
    Explanation: The sum of 2 and 4 is 6. Therefore index1 = 1, index2 = 3.

    Input: numbers = [-1,0], target = -1
    Output: [1,2]
    Explanation: The sum of -1 and 0 is -1. Therefore index1 = 1, index2 = 2.

    Constraints:

    2 <= numbers.length <= 3 * 104
    -1000 <= numbers[i] <= 1000
    numbers is sorted in non-decreasing order.
    -1000 <= target <= 1000
    The tests are generated such that there is exactly one solution.

    Date: 10182021 Oct
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

/**
 * Optimize version - 4ms
 */
int* twoSum(int* nums, int n, int target, int* returnSize) {
  long long  i = 0, j = n -1, sum = 0;
  int *result = (int *)malloc (sizeof(int) * 2);

  while ( i < j ) {
    sum = nums[i] + nums[j];

    if (sum == target)
      break;
    else if (sum > target)
      j--;
    else
      i++;
  }

  result[0] = i + 1;
  result[1] = j + 1;
  *returnSize = 2;
  return result;
}

/**
 * 600ms
 */
int* __twoSum(int* numbers, int numbersSize, int target, int* returnSize) {
  numbersSize = numbersSize - 1;
  int* ret = (int *)calloc(2, sizeof(int));
  *returnSize = 2;
  for (int i=0; i<numbersSize; ++i) {
    for (int j=i+1; j<=numbersSize; ++j) {
      debug("numbers[%d]=%d  numbers[%d]=%d", i, numbers[i], j, numbers[j]);
      if ( (numbers[i] + numbers[j]) == target ) {
	ret[0] = i+1;
	ret[1] = j+1;
	break;
      }
    }
  }
  return ret;
}

int main (int argc, char **argv) {
  int *ret;
  int numbers1[] = {2,7,11,15};
  int numbers[] = {2,3,4};
  int numbersSize = sizeof(numbers)/sizeof(numbers[0]);
  int target1 = 9;
  int target = 6;
  int returnSize;

  ret = twoSum(numbers, numbersSize, target,&returnSize);
  for (int i=0; i<returnSize; ++i)
    debug("Output = %d", ret[i]);
  free(ret);
  ret = NULL;
  return 0;
}

/**
   => ./a.out
   [main] L=75 :Output = 1
   [main] L=75 :Output = 3
**/
