/***
    LeetCode : https://leetcode.com/problems/interleaving-string/
    Given strings s1, s2, and s3, find whether s3 is formed by
    an interleaving of s1 and s2.

    An interleaving of two strings s and t is a configuration where
    they are divided into non-empty substrings such that:

    s = s1 + s2 + ... + sn
    t = t1 + t2 + ... + tm
    |n - m| <= 1
    The interleaving is s1 + t1 + s2 + t2 + s3 + t3 + ... or t1 + s1 + t2 + s2 + t3 + s3 + ...

    Note: a + b is the concatenation of strings a and b.
    Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
    Output: true

    Example 2:
    Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
    Output: false

    Example 3:
    Input: s1 = "", s2 = "", s3 = ""
    Output: true

    Constraints:
    0 <= s1.length, s2.length <= 100
    0 <= s3.length <= 200
    s1, s2, and s3 consist of lower-case English letters.

    Date : 03/03/2021
    San Diego, CA.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

#define MAXN 2048
bool dp[MAXN][MAXN];

bool isInterleave(char * s1, char * s2, char * s3) {
  const int alen = strlen(s1), blen = strlen(s2), clen = strlen(s3);
  if(alen + blen != clen)
    return false;
  dp[0][0] = true;

  for(int i = 1; i <= clen; i++){
    dp[0][i] = (dp[0][i-1] && s3[i-1]==s2[i-1]);
    dp[i][0] = (dp[i-1][0] && s3[i-1]==s1[i-1]);

    for(int j = i > alen ? i - alen:1; j < i && j <= blen; j++)
      dp[i-j][j] = (dp[i-j][j-1] && s3[i-1] == s2[j-1])||(dp[i-j-1][j] && s3[i-1] == s1[i-j-1]);
  }
  return dp[alen][blen];
}

int main() {
  char s1[] = "aabcc";
  char s2[] = "dbbca";
  char s3[] = "aadbbcbcac";
  char s11[] = "aabcc";
  char s22[] = "dbbca";
  char s33[] = "aadbbbaccc";

  bool ret = isInterleave(s1, s2, s3);
  debug("ret = %d", ret);
}

/**
   Complexity Analysis

   Time complexity : O(m⋅n). dp array of size m∗nm*nm∗n is filled.

   Space complexity : O(m⋅n). 2D dp of size (m+1)∗(n+1) is required.
   m and nn are the lengths of strings s1 and s2 respectively.
**/

/**
   => ./a.out
   [main] L=69 :ret = 1
**/
