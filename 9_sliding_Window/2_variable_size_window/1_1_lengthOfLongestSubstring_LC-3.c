/***

    https://leetcode.com/problems/longest-substring-without-repeating-characters/

    3. Longest Substring Without Repeating Characters

    Given a string s, find the length of the longest substring
    without duplicate characters.

    Input: s = "abcabcbb"
    Output: 3
    Explanation: The answer is "abc", with the length of 3. Note that "bca" and "cab" are also correct answers.

    Input: s = "bbbbb"
    Output: 1
    Explanation: The answer is "b", with the length of 1.

    Input: s = "pwwkew"
    Output: 3
    Explanation: The answer is "wke", with the length of 3.
    Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.

    Constraints:
    0 <= s.length <= 105
    s consists of English letters, digits, symbols and spaces

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Fri Oct  9 22:23:01 PDT 2026
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

int lengthOfLongestSubstring(char* s) {

  int freq[256] = {0};
  int left = 0;
  int maxLen = 0;

  for (int right = 0; s[right] != '\0'; right++) {

    unsigned char incoming = s[right];

    // Step 1: Add incoming
    freq[incoming]++;

    // Step 2: Shrink if duplicate exists
    while (freq[incoming] > 1) {
      unsigned char outgoing = s[left];

      freq[outgoing]--;

      left++;
    }

    // Step 3: Update maximum length
    int len = right - left + 1;

    if (len > maxLen)
      maxLen = len;
  }
  return maxLen;
}

void test() {
  int ret = 0;
  char str[] = "abcabcbb";
  ret = lengthOfLongestSubstring(str);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   L=[81][1_1_lengthOfLongestSubstring_LC-3.c]->[test] :| Output = 3
**/

/**
   Four lines to memorize :
   freq[(unsigned char)s[right]]++;   // Incoming

   while (freq[(unsigned char)s[right]] > 1) {
   freq[(unsigned char)s[left]]--; // Outgoing
   left++;
   }

   maxLen = max(maxLen, right - left + 1);

   For longest unique substring, keep expanding the right pointer.
   Whenever a duplicate appears, shrink from the left until every
   character is unique again.
   Update the maximum length after the window becomes valid.
**/
