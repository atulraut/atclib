/***
    https://leetcode.com/problems/largest-component-size-by-common-factor
    Hard: Largest Component Size by Common Factor

    You are given an integer array of unique positive integers nums.
    Consider the following graph:

    There are nums.length nodes, labeled nums[0] to nums[nums.length - 1],
    There is an undirected edge between nums[i] and nums[j] if nums[i]
    and nums[j] share a common factor greater than 1.
    Return the size of the largest connected component in the graph.

    Input: nums = [4,6,15,35]
    Output: 4

    Input: nums = [20,50,9,63]
    Output: 2

    Input: nums = [2,3,6,7,4,12,21,39]
    Output: 8

    Constraints:
    1 <= nums.length <= 2 * 104
    1 <= nums[i] <= 105
    All the values of nums are unique.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 27 Nov 2021
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
#define max(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a > _b ? _a : _b; })
#define min(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

int parent[100001];

int find(int x) {
  if(parent[x] == -1)
    return x;
  else
    return parent[x] = find(parent[x]);
}

bool uni(int a, int b) {
  int x = find(a);
  int y = find(b);
  if(x != y)
    parent[y] = x;
  else
    return false;
  return true;
}

int largestComponentSize(int* nums, int numsSize) {
  int temp[100001] = {0};
  int ret = 0;
  for(int i = 0; i < 100001; i++)
    parent[i] = -1;
  for(int i = 0; i < numsSize; i++)
    for(int j = 2; j*j <= nums[i]; j++)
      if(nums[i] % j == 0) {
	uni(j, nums[i]);
	uni(nums[i], nums[i]/j);
      }
  for(int i = 0; i < numsSize; i++)
    ret = ret > ++temp[find(nums[i])] ? ret : temp[find(nums[i])];
  return ret;
}

int main (int argc, char **argv) {
  int ret = 0;
  int nums[] = {4,6,15,35};
  int sz = 4;

  ret =  largestComponentSize(nums, sz);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=100 :Output = 4
**/
