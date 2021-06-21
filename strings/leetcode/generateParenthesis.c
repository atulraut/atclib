/***
    Medium: 22. Generate Parentheses

    Given n pairs of parentheses, write a function to generate all
    combinations of well-formed parentheses.

    Input: n = 3
    Output: ["((()))","(()())","(())()","()(())","()()()"]

    Input: n = 1
    Output: ["()"]

    Constraints:
    1 <= n <= 8

    https://leetcode.com/problems/generate-parentheses/

    Date: 19 June 2021.
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

#define MAX_SIZE 1500

void helper(int n,int left,int right,char*** result,int* resultIdx,char* tempBuffer,int tempIdx,int* space) {
  char** newResult;
  int i;

  if(tempIdx == n*2) {
    if((*resultIdx) == (MAX_SIZE*(*space)-1)) {
      (*space)++;
      newResult = (char**)realloc(*result,MAX_SIZE*(*space)*sizeof(int*));
      for(i=0;i<MAX_SIZE;i++) {
	newResult[MAX_SIZE*(*space - 1) + i] = (char*)malloc((2*n+1)*sizeof(char));
      }
      *result = newResult;
    }
    memcpy((*result)[*resultIdx],tempBuffer,n*2*sizeof(char));
    (*result)[*resultIdx][n*2] = '\0';
    (*resultIdx)++;
  } else {
    if(left<n) {
      tempBuffer[tempIdx] = '(';
      helper(n,left+1,right,result,resultIdx,tempBuffer,tempIdx+1,space);
    }
    if(right<left) {
      tempBuffer[tempIdx] = ')';
      helper(n,left,right+1,result,resultIdx,tempBuffer,tempIdx+1,space);
    }
  }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** generateParenthesis(int n, int* returnSize) {
  char** result = (char**)malloc(MAX_SIZE*sizeof(char*));
  char* tempBuffer = (char*)malloc((2*n+1)*sizeof(char));
  int i;
  int left=0,right=0,resultIdx=0,tempIdx=0;
  int space = 1; // for expand memory

  for(i=0;i<MAX_SIZE;i++) {
    result[i] = (char*)malloc((2*n+1)*sizeof(char));
  }

  helper(n,left,right,&result,&resultIdx,tempBuffer,tempIdx,&space);

  *returnSize = resultIdx;
  return result;
}

int main () {
  int returnSize;
  int n = 3;

  char **ret = generateParenthesis(n, &returnSize);

  for (int i=0; i<returnSize; ++i)
    debug("Output = %s", ret[i]);

    return 0;
  }

/**
   => ./a.out
   [main] L=92 :Output = ((()))
   [main] L=92 :Output = (()())
   [main] L=92 :Output = (())()
   [main] L=92 :Output = ()(())
   [main] L=92 :Output = ()()()
**/
