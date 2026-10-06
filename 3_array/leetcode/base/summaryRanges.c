/**
    https://leetcode.com/problems/summary-ranges/
    Summary Ranges

    You are given a sorted unique integer array nums.

    Return the smallest sorted list of ranges that cover all
    the numbers in the array exactly. That is, each element
    of nums is covered by exactly one of the ranges, and there
    is no integer x such that x is in one of the ranges but not in nums.

    Each range [a,b] in the list should be output as:

    "a->b" if a != b
    "a" if a == b

    Input: nums = [0,1,2,4,5,7]
    Output: ["0->2","4->5","7"]
    Explanation: The ranges are:
    [0,2] --> "0->2"
    [4,5] --> "4->5"
    [7,7] --> "7"

    Input: nums = [0,2,3,4,6,8,9]
    Output: ["0","2->4","6","8->9"]
    Explanation: The ranges are:
    [0,0] --> "0"
    [2,4] --> "2->4"
    [6,6] --> "6"
    [8,9] --> "8->9"

    Constraints:

    0 <= nums.length <= 20
    -231 <= nums[i] <= 231 - 1
    All the values of nums are unique.
    nums is sorted in ascending order.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: <2022-02-27 Sun>
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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** summaryRanges(int* nums, int numsSize, int* returnSize) {
  *returnSize=0;
  if(0 == numsSize) {
    return 0;
  }

  char **ret=malloc(sizeof(char*)*numsSize);
  char buff[265];
  int p1=0;
  int p2=1;

  while(p1 < numsSize) {
    while(p2 < numsSize && nums[p2-1] == nums[p2]-1)
      ++p2;

    if(p1 < p2-1) {
      int isp=sprintf(buff,"%d->%d",nums[p1],nums[p2-1]);
      char *m=malloc(sizeof(char)*(isp+1));
      ret[*returnSize]=strcpy(m,buff);
      ++(*returnSize);
    } else {
      int isp=sprintf(buff,"%d",nums[p1]);
      printf("n:%d,isp:%d\n",nums[p1],isp);
      char *m=malloc(sizeof(char)*(isp+1));
      ret[*returnSize]=strcpy(m,buff);
      ++(*returnSize);
    }
    p1=p2;
    ++p2;
  }
  return ret;
}

void test() {
  char **ret;
  int nums[] = {0, 1, 2, 4, 5, 7};
  int numsSize = 6;
  int returnSize;

  ret = summaryRanges(nums, numsSize, &returnSize);
  for (int i=0; i<returnSize; ++i)
    debug("Output = %s", ret[i]);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   n:7,isp:1
   [test] L=115 :Output = 0->2
   [test] L=115 :Output = 4->5
   [test] L=115 :Output = 7
**/
