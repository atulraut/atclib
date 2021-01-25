/***
    One Edit Distance :

    https://www.youtube.com/watch?v=grsuvoUOA0I

    Given two strings s and t, return true if they are both one edit
    distance apart, otherwise return false.

    A string s is said to be one distance apart from a string t if you can:

    Insert exactly one character into s to get t.
    Delete exactly one character from s to get t.
    Replace exactly one character of s with a different character to get t.

    Example 1:
    Input: s = "ab", t = "acb"
    Output: true
    Explanation: We can insert 'c' into s to get t.

    Example 2:
    Input: s = "", t = ""
    Output: false
    Explanation: We cannot get t from s by only one step.

    Example 3:
    Input: s = "a", t = ""
    Output: true

    Example 4:
    Input: s = "", t = "A"
    Output: true

    Constraints:
    0 <= s.length <= 104
    0 <= t.length <= 104
    s and t consist of lower-case letters, upper-case letters and/or digits.

    Date : 1-24-21 (Palindrome)
    San Diego, CA
*/

#include <stdio.h>
#include "../../at_lib.h"

#define MIN(a, b)   (a < b ? a : b)

bool isOneEditDistance(char * s, char * t){
  int m = strlen(s);
  int n = strlen(t);

  if (abs(m-n) > 1)
    return false;

  int k = MIN(m, n);
  int i = 0, j = 0;

  while (i < k && s[i] == t[i])
    ++i;

  while (j < k - i && s[m - 1 - j] == t[n - 1 - j])
    ++j;

  return m + n - k - 1 == i + j;

}

bool isOneEditDistance2(char * s, char * t){

  if (abs(strlen(s) - strlen(t)) > 1 || strcmp(s, t) == 0) return false;

  int i = 0, j = 0;

  bool foundOneDiff = false;
  while (i < strlen(s) && j < strlen(t)) {
      if (s[i] != t[j]) {
	  if (foundOneDiff)
	    return false;

	  foundOneDiff = true;

	  if (strlen(s) < strlen(t)) {
	      i--;
          } else if (strlen(t) < strlen(s)) {
	      j--;
          }
      }
      i++;
      j++;
    }

  return true;
}

int main() {
  char s[] = "ab";
  char t[] = "acb";
  bool ret =  isOneEditDistance(s, t);
  debug ("O/P = %d", ret);

  return 0;
}

/***
    Approach 1: One pass algorithm

    First of all, let's ensure that the string lengths are not too far
    from each other. If the length difference is 2 or more characters,
    then s and t couldn't be one edit away strings.

    For the next let's assume that s is always shorter or the same
    length as t. If not, one could always call isOneEditDistance(t, s)
    to inverse the string order.

    Now it's time to pass along the strings and to look for the first
    different character.

    If there is no differences between the first len(s) characters,
    only two situations are possible :

    I]The strings are equal.
    II]The strings are one edit away distance.

    Now what if there is a different character so that s[i] != t[i].

    If the strings are of the same length, all next characters should be
    equal to keep one edit away distance. To verify it, one has to
    compare the substrings of s and t both starting from the i + 1th character.

    If t is one character longer than s, the additional character t[i] should
    be the only difference between both strings. To verify it, one has to
    compare a substring of s starting from the ith character and a substring
    of t starting from the i + 1th character.

    Complexity Analysis

    Time complexity : O(N)\mathcal{O}(N)O(N) in the worst case when string
    lengths are close enough abs(ns - nt) <= 1, where N is a number of
    characters in the longest string. O(1)\mathcal{O}(1)O(1) in the
    best case when abs(ns - nt) > 1.

    Space complexity : O(N)\mathcal{O}(N)O(N) because strings are immutabl
    in Python and Java and to create substring costs O(N)\mathcal{O}(N)O(N) space.

    => ./a.out
    [main] L=96 :O/P = 1
*/
