/***

    https://leetcode.com/problems/permutation-in-string/description/

    567. Permutation in String

    Hint
    Given two strings s1 and s2, return true if s2 contains a permutation of s1,
    or false otherwise.
    In other words, return true if one of s1's permutations is the substring of s2.

    Input: s1 = "ab", s2 = "eidbaooo"
    Output: true
    Explanation: s2 contains one permutation of s1 ("ba").

    Input: s1 = "ab", s2 = "eidboaoo"
    Output: false

    Constraints:
    1 <= s1.length, s2.length <= 104
    s1 and s2 consist of lowercase English letters.
    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Fri Oct  9 11:23:57 PDT 2026
    Folsom, CA.
 */

/*----------------------------------- Header --------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h> // va_arg
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */

#define debug(str,args...) printf("L=[%d][%s]->[%s] :| "str"\n",__LINE__,__FILE__, __func__, ##args)

/**
   Fixed-size sliding-window problems:
   // Add incoming
   freq[s[i]]++;

   // Remove outgoing
   freq[s[i - k]]--;

   But instead of calculating a sum, we compare character frequencies.

   The simplest way is to maintain two frequency arrays:
   int patternFreq[26] = {0};
   int windowFreq[26] = {0};

   Assumes both strings contain lowercase English letters (a–z).
**/

bool checkInclusion(char* s1, char* s2) {
  int k = strlen(s1);
  int n = strlen(s2);

  if (k > n)
    return false;

  int freq[26] = {0};
  int window[26] = {0};

  // Step 1: Calcuate First window & build the pattern
  for (int i = 0; i < k; i++) {
    freq[s1[i]   - 'a']++;
    window[s2[i] - 'a']++;
  }
  // Check the first window
  if (memcmp(freq, window, sizeof(freq)) == 0)
    return true;

  // Step 2: Slide the window
  for (int i = k; i < n; i++) {

    window[s2[i]   - 'a']++;     // Add Incoming
    window[s2[i-k] - 'a']--;   // Remove Outgoing
    // Compare frequencies
    if (memcmp(freq, window, sizeof(freq)) == 0)
      return true;
  }

  return false;
}

void test() {

  char* s = "ab";
  char* p = "eidbaooo";

  bool ans = checkInclusion(s, p);
  debug("Output = %d", ans);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   L=[99][1_checkInclusion.c]->[test] :| Output = 1
**/
