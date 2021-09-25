/***
    Break a Palindrome
    Given a palindromic string of lowercase English letters palindrome,
    replace exactly one character with any lowercase English
    letter so that the resulting string is not a palindrome
    and that it is the lexicographically smallest one possible.

    Return the resulting string. If there is no way to replace
    a character to make it not a palindrome, return an empty string.

    A string a is lexicographically smaller than a string b
    (of the same length) if in the first position where a
    and b differ, a has a character strictly smaller than
    the corresponding character in b. For example, "abcc"
    is lexicographically smaller than "abcd" because the first
    position they differ is at the fourth character, and 'c'
    is smaller than 'd'.

    Input: palindrome = "abccba"
    Output: "aaccba"
    Explanation: There are many ways to make "abccba" not a
    palindrome, such as "zbccba", "aaccba", and "abacba".
    Of all the ways, "aaccba" is the lexicographically smallest.

    Input: palindrome = "a"
    Output: ""
    Explanation: There is no way to replace a single character to
    make "a" not a palindrome, so return an empty string.

    Input: palindrome = "aa"
    Output: "ab"

    Input: palindrome = "aba"
    Output: "abb"

    https://leetcode.com/problems/break-a-palindrome/
    Date: 24 Spet 2021
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

char* breakPalindrome(char* palindrome) {
  int length = strlen(palindrome);

  if (length == 1) {
    return "";
  }

  for (int i = 0; i < length / 2; i++) {
    if (palindrome[i] != 'a') {
      palindrome[i] = 'a';
      return palindrome;
    }
  }

  palindrome[length - 1] = 'b';
  return palindrome;
}

int main (int argc, char **argv) {
  char* ret;
  char palindrome[] = "aba";
  ret = breakPalindrome(palindrome);
  debug("Output = %s", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=76 :Output = abb
**/
