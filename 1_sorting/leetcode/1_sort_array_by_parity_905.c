/***
    https://leetcode.com/problems/sort-array-by-parity/

    905. Sort Array By Parity
Easy

Given an integer array nums, move all the even integers at the beginning of the array followed by all the odd integers.

Return any array that satisfies this condition.

Example 1:

Input: nums = [3,1,2,4]
Output: [2,4,3,1]
Explanation: The outputs [4,2,3,1], [2,4,1,3], and [4,2,1,3] would also be accepted.

Example 2:

Input: nums = [0]
Output: [0]

Constraints:

    1 <= nums.length <= 5000
    0 <= nums[i] <= 5000

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Wed Nov 23 02:01:56 PM PST 2022
    Folsom, CA.

    #Amazon #FB
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

/***
    Problem Reduction :
    1] Start with Quick Sort - O(n log n)
    2] In Place with O(N) Time with below Solution.
 **/
int *sortArrayByParity(int *numbers) {

  // Write your code here.
  int i, tmp, p=0;
  for(i =0; i<4; i++) {
    if(numbers[i]%2 == 0) {
      tmp = numbers[p];
      numbers[p] = numbers[i];
      numbers[i] = tmp;
      p++;
    }
  }
  return numbers;
}

void test() {
  int ret = 0;

  int* items = (int *)malloc(sizeof(int)* 4);
  int length= 4;
  *(op->items+0) = 1;
  *(op->items+1) = 2;
  *(op->items+2) = 3;
  *(op->items+3) = 4;

  op = sortArrayByParity(items);
  for (int i=0; i<length; ++i)
    debug("Output = %d", items[i]);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [test] L=90 :Output = 2
   [test] L=90 :Output = 4
   [test] L=90 :Output = 3
   [test] L=90 :Output = 1
**/

/***
  Complexity Analysis

  Time Complexity: O(N), where N is the length of A.
  Each step of the while loop makes j-i decrease by at least one.
  (Note that while quicksort is O(Nlog⁡N)O(N \log N)O(NlogN) normally,
  this is O(N) because we only need one pass to sort the elements.)

  Space Complexity: O(1) in additional space complexity.
/
