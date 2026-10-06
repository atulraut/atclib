/***
    Medium : 667. Beautiful Arrangement II

    Given two integers n and k, you need to construct a list which
    contains n different positive integers ranging from 1 to n and
    obeys the following requirement:
    Suppose this list is [a1, a2, a3, ... , an], then the list
    [|a1 - a2|, |a2 - a3|, |a3 - a4|, ... , |an-1 - an|] has exactly k distinct integers.

    If there are multiple answers, print any of them.


    Input: n = 3, k = 1
    Output: [1, 2, 3]
    Explanation: The [1, 2, 3] has three different positive integers ranging
    from 1 to 3, and the [1, 1] has exactly 1 distinct integer: 1.


    Input: n = 3, k = 2
    Output: [1, 3, 2]
    Explanation: The [1, 3, 2] has three different positive integers ranging from 1 to 3,
    and the [2, 1] has exactly 2 distinct integers: 1 and 2.

    https://leetcode.com/problems/beautiful-arrangement-ii/submissions/

    04/12/21 April
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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* constructArray(int n, int k, int* returnSize) {
  int *arr = (int *) malloc(sizeof(int) * n);
  *returnSize = n;
  int cnt = 0;

  for (int i = 1, j = n; i <= j;) {
    if (k > 1) {
      arr[cnt++] = (k % 2) ? i++ : j--;
      debug("i=%d arr = %d", i, arr[cnt-1]);
    } else {
      arr[cnt++] = i++;
      debug("i=%d arr = %d", i, arr[cnt-1]);
    }
    k--;
  }

  return arr;
}

int* constructArray2(int n, int k, int* returnSize){
  int *ans = (int*)malloc(sizeof(int)*n);
  int i=0;
  *returnSize=n;
  ans[i] = 1;

  while(k){

    if(!(i%2))
      ans[i+1] = ans[i]+k;

    if(i%2)
      ans[i+1] = ans[i]-k;

    i++;
    k--;

  }

  for(int j=i+1;j<n;j++){
    ans[j] = j+1;
  }

  return ans;
}

int main () {
  int n = 3;
  int k = 2;
  int returnSize;

  int*output = constructArray(n, k, &returnSize);

  for (int i=0; i<returnSize; i++)
    debug("output = %d", output[i]);

  return 0;
}

/**
   Complexity Analysis**
   Time Complexity: O(n). We are making a list of size n\text{n}n.
   Space Complexity: O(n). Our answer has a length equal to n\text{n}n.
**/
