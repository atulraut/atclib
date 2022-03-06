/***
    https://leetcode.com/problems/delete-and-earn/
    Delete and Earn

    You are given an integer array nums. You want to maximize
    the number of points you get by performing the following
    operation any number of times:

    Pick any nums[i] and delete it to earn nums[i] points.
    Afterwards, you must delete every element equal to nums[i] - 1
    and every element equal to nums[i] + 1.
    Return the maximum number of points you can earn by applying
    the above operation some number of times.

    Input: nums = [3,4,2]
    Output: 6
    Explanation: You can perform the following operations:
    - Delete 4 to earn 4 points. Consequently, 3 is also deleted. nums = [2].
    - Delete 2 to earn 2 points. nums = [].
    You earn a total of 6 points.

    Input: nums = [2,2,3,3,3,4]
    Output: 9
    Explanation: You can perform the following operations:
    - Delete a 3 to earn 3 points. All 2's and 4's are also deleted. nums = [3,3].
    - Delete a 3 again to earn 3 points. nums = [3].
    - Delete a 3 once more to earn 3 points. nums = [].
    You earn a total of 9 points.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date:
    Folsom, CA.
*/

/*----------------------------------- Header --------------------------------------*/
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

/*----------------------------------- Micro --------------------------------------*/
#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)
#define atsizeof(object) (char *)(&object+1) - (char*)(&object)
#define arrsz(x)  (sizeof(x) / sizeof((x)[0]))
#define max(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a > _b ? _a : _b; })
#define min(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

int deleteAndEarn(int* nums, int numsSize) {
  int temp[10001] = {0};

  for(int i=0; i<numsSize; i++)
    temp[nums[i]]++;

  int dp[10001] = {0};

  dp[0] = temp[0];
  dp[1] = temp[0] < temp[1] ? temp[1] : temp[0];

  for(int i=2; i<10001; i++)
    dp[i] = dp[i-1] < dp[i-2] + i*temp[i] ? dp[i-2] + i*temp[i] : dp[i-1];

  return dp[10000];
}

int deleteAndEarn2(int* nums, int numsSize){
  //     int temp[numsSize] = {0};
  int* temp = (int *)malloc(numsSize * numsSize);
  memset(temp, 0, numsSize * numsSize);
  int* dp = (int *)malloc(numsSize * numsSize);
  memset(dp, 0, numsSize * numsSize);

  for(int i=0; i<numsSize; i++)
    temp[nums[i]]++;
  dp[0] = temp[0];
  dp[1] = temp[0] < temp[1] ? temp[1] : temp[0];
  for(int i=2; i<numsSize; i++)
    dp[i] = dp[i-1] < dp[i-2] + i*temp[i] ? dp[i-2] + i*temp[i] : dp[i-1];
  return dp[numsSize];
}
void test() {
  int ret = 0;
  int arr[] = {3, 4, 2};

  ret = deleteAndEarn(arr, 3);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [test] L=72 :Output = 6
**/
