/***
    Medium: Palindrome Partitioning
    Given a string s, partition s such that every substring of the partition
    is a palindrome. Return all possible palindrome partitioning of s.

    A palindrome string is a string that reads the same backward as forward.

    Input: s = "aab"
    Output: [["a","a","b"],["aa","b"]]

    Input: s = "a"
    Output: [["a"]]

    Constraints:

    1 <= s.length <= 16
    s contains only lowercase English letters.

    https://leetcode.com/problems/palindrome-partitioning/

    Date: 7 August 2021
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

/***
     Solution: Backtracking
*/
// checks whether s (of length sLen) is a palindrome
bool isPalindrome(char * s, int sLen) {
    if(s == 0)
      return true;
    for(int i = 0; i < sLen/2; i++){
        if(s[i] != s[sLen-1-i]) return false;
    }
    return true;
}

void partitionRecursive(char* s, int sLen, char** currRes, int currResInd,
                        char**** result, int* resultSize,
                        int* returnSize, int** returnColumnSizes) {
    // base
    if(sLen == 0) {
        // add currRes to result
        (*result)[*returnSize] = malloc(sizeof(char *) * currResInd);
        for(int i = 0; i < currResInd; i++){
            int size = strlen(currRes[i]);
            (*result)[*returnSize][i] = malloc(sizeof(char) * (1+size));
            strcpy((*result)[*returnSize][i], currRes[i]);
            (*result)[*returnSize][i][size] = '\0';
        }
        // update returnSize
        (*returnColumnSizes)[*returnSize] = currResInd;
        (*returnSize)++;
        // enough space in result?
        if(*returnSize == *resultSize) {
            *resultSize *= 2;
            *result = realloc(*result, sizeof(char**) * *resultSize);
            *returnColumnSizes = realloc(*returnColumnSizes, sizeof(int) * *resultSize);
        }
    }

    // recursion

    for(int i = 1; i <= sLen; i++) {
        // first make a partition of length i
        // check the partition is palindrome
        if(!isPalindrome(s, i))
            continue;
        // add the partition to currRes
        currRes[currResInd] = malloc(sizeof(char) * (i+1));
        memcpy(currRes[currResInd], s, sizeof(char) * i);
        currRes[currResInd][i] = '\0';
        currResInd++;
        // partition the rest of s
        partitionRecursive(s+i, sLen-i, currRes, currResInd,
                           result, resultSize, returnSize, returnColumnSizes);
        // backtrack
        currResInd--;
    }
}


/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** partition(char* str, int* returnSize, int** returnColumnSizes) {

    int strLen = strlen(str);

    // result
    int resultSize = 100;
    char*** result = malloc(sizeof(char**) * resultSize);
    *returnColumnSizes = malloc(sizeof(int) * resultSize);
    *returnSize = 0;

    // currRes
    char** currRes = malloc(sizeof(char *) * strLen);

    partitionRecursive(str, strLen, currRes, 0, &result, &resultSize, returnSize, returnColumnSizes);

    return result;
}

int main () {
  char s[] = "aab";
  int returnSize;
  int* returnColumnSizes;

  char ***ret =  partition(s, &returnSize, &returnColumnSizes);
  for (int i=0; i<returnSize; ++i) {
    for(int j=0; j<*returnColumnSizes; ++j) {
      debug("Output = %s", ret[i][j]);
    }
  }
      return 0;
}

/**

 **/
