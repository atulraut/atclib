/***
    Hard: Given two strings s and t, return the number of
    distinct subsequences of s which equals t.

    A string's subsequence is a new string formed from the
    original string by deleting some (can be none) of the
    characters without disturbing the remaining characters'
    relative positions. (i.e., "ACE" is a subsequence
    of "ABCDE" while "AEC" is not).

    It is guaranteed the answer fits on a 32-bit signed integer.

    Input: s = "rabbbit", t = "rabbit"
    Output: 3
    Explanation:
    As shown below, there are 3 ways you can generate "rabbit" from S.
    rabbbit
    rabbbit
    rabbbit

    Input: s = "babgbag", t = "bag"
    Output: 5
    Explanation:
    As shown below, there are 5 ways you can generate "bag" from S.
    babgbag
    babgbag
    babgbag
    babgbag
    babgbag

    Constraints:

    1 <= s.length, t.length <= 1000
    s and t consist of English letters.

    https://leetcode.com/problems/distinct-subsequences/

    Date: 19 Sept 2021
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

/**
   Approach 3: Space optimized Dynamic Programming
 **/
int numDistinct(char* s, char* t){
  int M = strlen(s);
  int N = strlen(t);

  int* dp = (int*)calloc(N, sizeof(int));

  unsigned int prev = 1;

  // Iterate over the strings in reverse so as to
  // satisfy the way we've modeled our recursive solution
  for (int i = M - 1; i >= 0; i--) {

    // At each step we start with the last value in
    // the row which is always 1. Notice how we are
    // starting the loop from N - 1 instead of N like
    // in the previous solution.
    prev = 1;

    for (int j = N - 1; j >= 0; j--) {

      // Record the current value in this cell so that
      // we can use it to calculate the value of dp[j - 1]
      int old_dpj = dp[j];

      // If the characters match, we add the
      // result of the next recursion call (in this
      // case, the value of a cell in the dp table
      if (s[i] == t[j]) {
	dp[j] += prev;
      }

      // Update the prev variable
      prev = old_dpj;
    }
  }

  return dp[0];
}
/**
   Complexity Analysis
   Time Complexity: O(M×N)
   Space Complexity:O(N) since we are using a single array which is the
   size of the string T. This is a major size reduction over the
   previous solution and this is a much more elegant solution
   than the initial recursive solution we saw earlier on.
 **/
int main (int argc, char **argv) {
  int ret = 0;

  debug("Output = %d", ret);
  return 0;
}

/**

 **/
