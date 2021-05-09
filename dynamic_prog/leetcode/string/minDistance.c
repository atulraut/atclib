/***
    Medium: Delete Operation for Two Strings

    https://leetcode.com/problems/delete-operation-for-two-strings/

    Given two strings word1 and word2, return the minimum number
    of steps required to make word1 and word2 the same.
    In one step, you can delete exactly one character in either string.

    Input: word1 = "sea", word2 = "eat"
    Output: 2
    Explanation: You need one step to make "sea" to "ea" and another step to make "eat" to "ea".

    Input: word1 = "leetcode", word2 = "etco"
    Output: 4

Constraints:
    1 <= word1.length, word2.length <= 500
    word1 and word2 consist of only lowercase English letters.

    Date: 7 May 2021.
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

int minDistance(char* word1, char* word2) {
  int len1 = strlen(word1), len2 = strlen(word2);

  /* Variable-length automatic arrays: introduced in C99 but relegated (made optional) in C11 */

  int dp[len1+1][len2+1];

  for(int i = 0; i <= len1; ++i)
    dp[i][0] = 0;

  for(int j = 0; j <= len2; ++j)
    dp[0][j] = 0;

  for(int i = 1; i <= len1; ++i)
    for (int j = 1; j <= len2; ++j)
      if (word1[i-1] == word2[j-1]) {
	dp[i][j] = dp[i-1][j-1] + 1;
	debug ("i=%d j=%d c[%d][%d] = %d", i, j, i, j, dp[i][j]);
      }
      else {
	int c1 = dp[i][j-1], c2 = dp[i-1][j];
	dp[i][j] = (c1 >= c2 ? c1 : c2);
      }

  debug ("c=%d", dp[len1][len2]);
  return len1 + len2 - 2 * dp[len1][len2];
}

int main () {
  int ret = 0;
  char word1[] = "sea";
  char word2[] = "eat";

  //char word1[] = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdef";
  //char word2[] = "bcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefg";

  ret = minDistance(word1, word2);
  debug("Output = %d", ret);

  return 0;
}

/**
   => ./a.out
   [minDistance] L=55 :i=2 j=1 c[2][1] = 1
   [minDistance] L=55 :i=3 j=2 c[3][2] = 2
   [minDistance] L=62 :c=2
   [main] L=75 :Output = 2
**/
