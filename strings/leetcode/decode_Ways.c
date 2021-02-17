/***
    LeetCode: Decod Ways 91 : A message containing letters from A-Z is
    being encoded to numbers using the following mapping:
    'A' -> 1
    'B' -> 2
    ...
    'Z' -> 26
    Given a non-empty string containing only digits, determine the total
     number of ways to decode it.
    Example 1:
    Input: "12"
    Output: 2
    Explanation: It could be decoded as "AB" (1 2) or "L" (12).
    Example 2:
    Input: "226"
    Output: 3
    Explanation: It could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).
    Ref: https://leetcode.com/problems/decode-ways/
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

int numDecodings(char* s) {
  if(s[0] == 48) return 0;
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

int main () {
  char arr[] = "12";
  printf ("o/p --> %d \n", numDecodings(arr));
}
