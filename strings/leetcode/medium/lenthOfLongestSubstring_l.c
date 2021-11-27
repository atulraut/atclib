/***
    https://leetcode.com/problems/longest-substring-without-repeating-characters/
    Longest Substring Without Repeating Characters
    Given a string s, find the length of the longest substring
    without repeating characters.

    Input: s = "abcabcbb"
    Output: 3
    Explanation: The answer is "abc", with the length of 3.

    Input: s = "bbbbb"
    Output: 1
    Explanation: The answer is "b", with the length of 1.

    Input: s = "pwwkew"
    Output: 3
    Explanation: The answer is "wke", with the length of 3.
    Notice that the answer must be a substring, "pwke" is a
    subsequence and not a substring.
    Input: s = ""
    Output: 0

    Constraints:
    0 <= s.length <= 5 * 104
    s consists of English letters, digits, symbols and spaces.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 24 Nov 2021
    Folsom, CA.
*/

/*----------------------------------- Header --------------------------------------*/
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

/*----------------------------------- Micro --------------------------------------*/
#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)
#define atsizeof(object) (char *)(&object+1) - (char*)(&object)
#define arrsz(x)  (sizeof(x) / sizeof((x)[0]))
#define max(a,b)               \
  ({ __typeof__ (a) _a = (a);  \
    __typeof__ (b) _b = (b);   \
    _a > _b ? _a : _b; })
#define min(a,b)               \
  ({ __typeof__ (a) _a = (a);  \
    __typeof__ (b) _b = (b);   \
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int lengthOfLongestSubstring(char* s) {
  int counts[512];
  int i, n = strlen(s), win_start = 0;
  int best = 0;

  memset(counts, 0, sizeof(int) * 512);

  for (i = 0; i < n; i++) {
    int c = s[i];
    if (counts[c] >= 1) {
      assert(counts[c] == 1);
      // need to move the window until removing the instance of c
      while (win_start < i) {
       int to_del = s[win_start];
       counts[to_del]--;
       win_start++;
       if (counts[c] == 0)
         break;
      }
    }
    counts[c]++;
    debug ("i=%d c= %c cnt=%d", i, c, counts[c]);
    best = MAX(best, i - win_start + 1);
  }
  return best;
}

int main (int argc, char **argv) {
  int ret = 0;
  char s[] = "abcab";

  ret =  lengthOfLongestSubstring(s);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [lengthOfLongestSubstring] L=83 :i=0 c= a cnt=1
   [lengthOfLongestSubstring] L=83 :i=1 c= b cnt=1
   [lengthOfLongestSubstring] L=83 :i=2 c= c cnt=1
   [lengthOfLongestSubstring] L=83 :i=3 c= a cnt=1
   [lengthOfLongestSubstring] L=83 :i=4 c= b cnt=1
   [main] L=94 :Output = 3
 **/

