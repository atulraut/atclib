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
  int n1 = strlen(word1), n2 = strlen(word2);

  /* Variable-length automatic arrays: introduced in C99 but relegated (made optional) in C11 */

  int c[n1+1][n2+1];

  for(int i = 0; i <= n1; ++i)
    c[i][0] = 0;

  for(int j = 0; j <= n2; ++j)
    c[0][j] = 0;

  for(int i = 1; i <= n1; ++i)
    for (int j = 1; j <= n2; ++j)
      if (word1[i-1] == word2[j-1])
	c[i][j] = c[i-1][j-1] + 1;
      else {
	int c1 = c[i][j-1], c2 = c[i-1][j];
	c[i][j] = (c1 >= c2 ? c1 : c2);
      }

  return n1 + n2 - 2 * c[n1][n2];
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
   [main] L=73 :Output = 2
**/
