/***
    LeetCode: Decod Ways 91 : A message containing letters from A-Z is
    being encoded to numbers using the following mapping:
    'A' -> 1
    'B' -> 2
    ...
    'Z' -> 26
    Given a non-empty string containing only digits, determine the total
    number of ways to decode it.

    Input: "12"
    Output: 2
    Explanation: It could be decoded as "AB" (1 2) or "L" (12).

    Input: "226"
    Explanation: It could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).

    Ref: https://leetcode.com/problems/decode-ways/

    Date: August 25, 2020
    San Diego, CA
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

int numDecodings(char* s) {
  if(s[0] == 48)
    return 0;

  int len = strlen(s);
  int* dp = calloc(len, sizeof(int));
  dp[0] = 1;

  for(int i = 1; i < len; i++) {
    if(s[i] >= 49)
      dp[i] = dp[i - 1]; // If the current digit is not '0', add dp[i - 1]
    if(s[i - 1] == 49 || (s[i - 1] == 50 && s[i] <= 54))
      dp[i] += i >= 2 ? dp[i - 2] : 1;
    // If the previous digit is 1 or 2, and in the second case the current digit
    // is less than or equal to 6, add dp[i - 2]
  }
  return dp[len - 1];
}

int numDecodings_debug(char* s) {
  if(s[0] == 48)
    return 0;
  int len = strlen(s);
  int* dp = calloc(len, sizeof(int));
  dp[0] = 1;
  for(int i = 1; i < len; i++) {
    debug("Test i = %d", i);
    if(s[i] >= 49)
      dp[i] = dp[i - 1]; // If the current digit is not '0', add dp[i - 1]
    if(s[i - 1] == 49 || (s[i - 1] == 50 && s[i] <= 54)) {  // 54 == '6', 'Z' == 26 thats why
      debug("dp[%d]=%d", i, dp[i]);
      dp[i] += (i >= 2) ? dp[i - 2] : 1;
      debug("i=%d dp[%d] dp[%d-2]=%d",i, dp[i], i, dp[i-2]);
      debug("dp[%d]=%d", i, dp[i]);
      // If the previous digit is 1 or 2, and in the second case the current digit
      // is less than or equal to 6, add dp[i - 2]
    }
  }
  return dp[len - 1];
}

int main () {
  char arr1[] = "12";
  char arr[] = "226";
  printf ("o/p --> %d \n", numDecodings_debug(arr));
}

/**
   => ./a.out
   [numDecodings_debug] L=57 :Test i = 1
   [numDecodings_debug] L=61 :dp[1]=1
   [numDecodings_debug] L=63 :i=1 dp[2] dp[1-2]=0
   [numDecodings_debug] L=64 :dp[1]=2
   [numDecodings_debug] L=57 :Test i = 2
   [numDecodings_debug] L=61 :dp[2]=2
   [numDecodings_debug] L=63 :i=2 dp[3] dp[2-2]=1
   [numDecodings_debug] L=64 :dp[2]=3
   o/p --> 3
**/

