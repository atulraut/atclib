/***
    Sort Array By Parity II

    Given an array of integers nums, half of the
    integers in nums are odd, and the other half are even.

    Sort the array so that whenever nums[i] is odd,
    i is odd, and whenever nums[i] is even, i is even.

    Return any answer array that satisfies this condition.

    Input: nums = [4,2,5,7]
    Output: [4,5,2,7]
    Explanation: [4,7,2,5], [2,5,4,7], [2,7,4,5] would
    also have been accepted.

    Input: nums = [2,3]
    Output: [2,3]

    Constraints:

    2 <= nums.length <= 2 * 104
    nums.length is even.
    Half of the integers in nums are even.
    0 <= nums[i] <= 1000

    https://leetcode.com/problems/sort-array-by-parity-ii/
    Date: 28 Sept 2021
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
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortArrayByParityII(int* nums, int numsSize, int* returnSize) {
  int oddIndex = 1;
  int evenIdex = 0;
  int* output = (int *)calloc(numsSize, sizeof(int));

  for (int index=0; index<numsSize; ++index) {
    if (nums[index] % 2 == 0) {
      output[evenIdex] = nums[index];
      evenIdex += 2;
    } else {
      output[oddIndex] = nums[index];
      oddIndex += 2;
    }
  }
  *returnSize = numsSize;
  return output;
}
int main (int argc, char **argv) {
  int nums[] = {4,2,5,7};
  int numsSize = 4;
  int returnSize;

  int* ret = sortArrayByParityII(nums, numsSize, &returnSize);
  for (int i=0; i<returnSize; ++i)
    debug("Output = %d", ret[i]);

  free(ret);
  ret = NULL;
  return 0;
}

/**
   => ./a.out
   [main] L=72 :Output = 4
   [main] L=72 :Output = 5
   [main] L=72 :Output = 2
   [main] L=72 :Output = 7
**/
