/***
    https://leetcode.com/problems/permutation-in-string/
    Permutation in String

    Given two strings s1 and s2, return true if s2
    contains a permutation of s1, or false otherwise.

    In other words, return true if one of s1's
    permutations is the substring of s2.

    Input: s1 = "ab", s2 = "eidbaooo"
    Output: true
    Explanation: s2 contains one permutation of s1 ("ba").

    Input: s1 = "ab", s2 = "eidboaoo"
    Output: false

    Constraints:
    1 <= s1.length, s2.length <= 104
    s1 and s2 consist of lowercase English letters.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 2/10/2022 Feb
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
#define max(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a > _b ? _a : _b; })
#define min(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

bool matches(int* s1map, int* s2map) {
  for (int i = 0; i < 26; i++) {
    if (s1map[i] != s2map[i])
      return false;
  }
  return true;
}

bool checkInclusion(char * s1, char * s2) {
  if (strlen(s1) > strlen(s2))
    return false;
  int s1map[26] = {0};
  int s2map[26] = {0};
  for (int i = 0; i < strlen(s1); i++) {
    s1map[s1[i] - 'a']++;
    s2map[s2[i] - 'a']++;
  }
  for (int i = 0; i < strlen(s2) - strlen(s1); i++) {
    if (matches(s1map, s2map))
      return true;
    s2map[s2[(i + strlen(s1))] - 'a']++;
    s2map[s2[i] - 'a']--;
  }
  return matches(s1map, s2map);
}

void test() {
  int ret = 0;
  char s1[] = "ab";
  char s2[] = "eidbaooo";
  ret = checkInclusion(s1, s2);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [test] L=85 :Output = 1
**/
