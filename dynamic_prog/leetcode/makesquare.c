/***
    Medium: 473. Matchsticks to Square
    https://leetcode.com/problems/matchsticks-to-square/

    You are given an integer array matchsticks where matchsticks[i] is the length
    of the ith matchstick. You want to use all the matchsticks to make one square.
    You should not break any stick, but you can link them up, and each matchstick
    must be used exactly one time.

    Return true if you can make this square and false otherwise.

    Input: matchsticks = [1,1,2,2,2]
    Output: true
    Explanation: You can form a square with length 2, one side of the square came
    two sticks with length 1.

    Input: matchsticks = [3,3,3,3,4]
    Output: false
    Explanation: You cannot find a way to form a square with all the matchsticks.

    Constraints:
    1 <= matchsticks.length <= 15
    0 <= matchsticks[i] <= 109

    Date: 15 June 2021.
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

bool dfs(int* matchsticks, int matchsticksSize, int* sums, int index, int target) {
  int i=0;

  if(index==matchsticksSize)
    if(sums[0] == target&&sums[1] == target&&sums[2] == target&&sums[3] == target)
      return true;
    else
      return false;

  for(i=0; i<4; i++) {
    if(sums[i]+matchsticks[index] <= target) {
      sums[i] += matchsticks[index];
      if(dfs(matchsticks,matchsticksSize,sums,index+1,target))
	return true;
      sums[i] -= matchsticks[index];
    }
  }
  return false;
}

void quicksort(int *matchsticks, int matchsticksSize) {
  int i=0,j = matchsticksSize-1;
  int key = matchsticks[0];
  if(matchsticksSize > 1) {
    while(i != j) {
      for(; i<j; j--)
	if(matchsticks[j]>key) {
	  matchsticks[i] = matchsticks[j];
	  break;
	}
      for(; i<j; i++)
	if(matchsticks[i] < key) {
	  matchsticks[j]=matchsticks[i];
	  break;
	}
      matchsticks[i]=key;
    } // while loop Ends
    quicksort(matchsticks,i);
    quicksort(matchsticks+i+1, matchsticksSize-i-1);
  }
}

bool makesquare(int* matchsticks, int matchsticksSize) {
  int sums[4]={0};
  int i,sum=0;

  for(i=0; i<matchsticksSize; i++)
    sum += matchsticks[i];

  if(sum%4 || matchsticksSize < 4)
    return false;

  for(i=0; i< matchsticksSize; i++)
    if(matchsticks[i] > sum/4)
      return false;

  quicksort(matchsticks,matchsticksSize);
  return dfs(matchsticks,matchsticksSize,sums,0,sum/4);
}

int main () {
  int ret = 0;
  int matchsticks[] = {1,1,2,2,2};
  int matchsticksSize = sizeof(matchsticks)/sizeof(matchsticks[0]);;

  ret = makesquare(matchsticks, matchsticksSize);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=108 :Output = 1
**/
