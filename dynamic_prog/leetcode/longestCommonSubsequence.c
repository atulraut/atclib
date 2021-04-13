/***
    Medium: 1143. Longest Common Subsequence
    https://leetcode.com/problems/longest-common-subsequence/
    Ref: https://www.youtube.com/watch?v=LAKWWDX3sGw

    Given two strings text1 and text2, return the length of their longest
    common subsequence. If there is no common subsequence, return 0.

    A subsequence of a string is a new string generated from the original
    string with some characters (can be none) deleted without changing the
    relative order of the remaining characters.

    For example, "ace" is a subsequence of "abcde".

    A common subsequence of two strings is a subsequence that is common to
    both strings.

    Input: text1 = "abcde", text2 = "ace"
    Output: 3
    Explanation: The longest common subsequence is "ace" and its length is 3.

    Input: text1 = "abc", text2 = "abc"
    Output: 3
    Explanation: The longest common subsequence is "abc" and its length is 3.

    Input: text1 = "abc", text2 = "def"
    Output: 0
    Explanation: There is no such common subsequence, so the result is 0.

    Constraints:
    1 <= text1.length, text2.length <= 1000
    text1 and text2 consist of only lowercase English characters.

    Date: 04/12/2021 April.
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

int longestCommonSubsequence1(char* text1, char* text2) {
  int i, j;
  int x = strlen(text1) + 1;
  int y = strlen(text2) + 1;

  int** matrix = malloc(y * sizeof(int*));
  for (i = 0; i < y; i++) {
    matrix[i] = malloc(x * sizeof(int));
    matrix[i][0] = 0;
  }
  for (i = 0; i < x; i++) {
    matrix[0][i] = 0;
  }

  for (i = 1; i < y; i++){
    for (j = 1; j < x; j++){
      if (text1[j - 1] == text2[i - 1]){
	matrix[i][j] = matrix[i - 1][j - 1] + 1;
      } else if (matrix[i - 1][j] >= matrix[i][j - 1]){
	matrix[i][j] = matrix[i - 1][j];
      } else{
	matrix[i][j] = matrix[i][j - 1];
      }
    }
  }
  return matrix[y - 1][x - 1];
}

int max(int a, int b) {
    return (a > b)? a : b;
}

/**
   LeetCode Optimize
 **/
int longestCommonSubsequence(char* text1, char* text2) {
  int m = strlen(text1);
  int n = strlen(text2);

  /* Returns length of LCS for X[0..m-1], Y[0..n-1] */
  int dpGrid[m+1][n+1];
  int i, j;

  /* Following steps build dpGrid[m+1][n+1] in bottom up fashion. Note
     that dpGrid[i][j] contains length of LCS of X[0..i-1] and Y[0..j-1] */
  for (i=0; i<=m; i++) {
    for (j=0; j<=n; j++) {
      if (i == 0 || j == 0)
	dpGrid[i][j] = 0;
      else if (text1[i-1] == text2[j-1])
	dpGrid[i][j] = dpGrid[i-1][j-1] + 1;
      else
	dpGrid[i][j] = max(dpGrid[i-1][j], dpGrid[i][j-1]);
    }
  }
  /* dpGridm][n] contains length of LCS for X[0..n-1] and Y[0..m-1] */
  return dpGrid[m][n];
}

int main () {
  char text1[] = "abcde";
  char text2[] = "acexx";

  int output = longestCommonSubsequence(text1, text2);

  debug ("output = %d", output);
}

/*
  Complexity Analysis

  Let MMM be the length of the first word, and NNN be the length
  of the second word.
  Time complexity : O(M⋅N).
  Like before, we're solving M⋅Nsubproblems, and each is an
  O(1) operation to solve.
  Space complexity : O(min⁡(M,N)).
*/
