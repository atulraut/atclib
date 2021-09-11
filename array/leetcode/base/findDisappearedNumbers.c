/***
    Given an array nums of n integers where nums[i] is
    in the range [1, n], return an array of all the
    integers in the range [1, n] that do not appear in nums.

    Input: nums = [4,3,2,7,8,2,3,1]
    Output: [5,6]

    Input: nums = [1,1]
    Output: [2]

    Constraints:
    n == nums.length
    1 <= n <= 105
    1 <= nums[i] <= n

    Follow up: Could you do it without extra space and in
    O(n) runtime? You may assume the returned list does not
    count as extra space.

    https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/

    Date: 10 Sept 2021
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

int* findDisappearedNumbers(int* nums, int numsSize, int* returnSize) {
  char * temp = (char *)malloc(numsSize*sizeof(char));
  int * result = (int *)malloc(numsSize*sizeof(int));
  int count = 0;
  for(int i=0; i<numsSize; i++)
    temp[nums[i]-1] = 1;
  for(int i=1; i<=numsSize; i++)
    if(temp[i-1] != 1)
      result[count++] = i;
  *returnSize = count;
  return result;
}

int main (int argc, char **argv) {
  int *ret = 0;
  int nums[] = {4,3,2,7,8,2,3,1};
  int numsSize = sizeof(nums)/sizeof(nums[0]);
  int returnSize

  ret = findDisappearedNumbers(nums, numsSize, &returnSize);
  for (int i=0; i<returnSize; ++i)
    debug("Output = %d", ret[i]);
  return 0;
}

/**
   => ./a.out
   [main] L=61 :Output = 5
   [main] L=61 :Output = 6
**/
