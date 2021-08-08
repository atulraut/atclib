/***
    Hard: iven a string s, partition s such that every substring of
    the partition is a palindrome.
    Return the minimum cuts needed for a palindrome partitioning of s.

    Input: s = "aab"
    Output: 1
    Explanation: The palindrome partitioning ["aa","b"] could be produced
    using 1 cut.

    Input: s = "a"
    Output: 0

    Input: s = "ab"
    Output:

    Constraints:
    1 <= s.length <= 2000
    s consists of lower-case English letters only.

    https://leetcode.com/problems/palindrome-partitioning-ii/
    Status : Issue - Time Limit Exceeded

    Date: 7 Augst 2021
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

#define min(x, y) (((x) < (y)) ? (x) : (y))

bool isPalindrome(char *s, int start, int end) {
  while (start < end) {
    if (s[start++] != s[end--]) {
      return false;
    }
  }
  return true;
}

int findMinimumCut(char* str, int start, int end, int minimumCut) {
  // base condition, no cut needed for an empty substring or palindrome substring.
  if (start == end || isPalindrome(str, start, end)) {
    return 0;
  }
  for (int currentEndIndex = start; currentEndIndex <= end; currentEndIndex++) {
    // find result for substring (start, currentEnd) if it is palindrome
    if (isPalindrome(str, start, currentEndIndex)) {
      minimumCut = min(minimumCut,
       1 + findMinimumCut(str, currentEndIndex + 1, end, minimumCut));
    }
  }
  return minimumCut;
}

int minCut(char* s){
  int strLen = strlen(s);
  return findMinimumCut(s, 0, strLen - 1, strLen - 1);
}

int main () {
  int ret = 0;
  char str[] = "aab";

  debug("Output = %d", minCur(str));
  return 0;
}

/**

 **/
