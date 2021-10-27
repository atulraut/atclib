/***
    LeetCode : https://leetcode.com/problems/valid-palindrome/
    isalphanum() : Function returns a non-zero integer if an argument (character)
    passed to the function is an alphanumeric (alphabet and number) character.

    Valid Palindrome :

    Given a string, determine if it is a palindrome, considering only alphanumeric
    characters and ignoring cases.
    Note: For the purpose of this problem, we define empty string as valid palindrome.

    Example 1:
    Input: "A man, a plan, a canal: Panama"
    Output: true

    Example 2:
    Input: "race a car"
    Output: false

    Constraints:
    s consists only of printable ASCII characters.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "../../at_lib.h"

bool _isPalindrome(char* s, int i, int j) {
  debug ("i=%d j=%d", i,j);
    while(i < j) {
        if(s[i] != s[j])
            return 0;
        i++;
	j--;
    }
    return 1;
}

/**
 * https://leetcode.com/problems/valid-palindrome-ii/
 * Valid Palindrome II
 * Given a string s, return true if the s can be palindrome
 * after _DELETING_ at most _ONE_ character from it.
 *
 * Input: s = "aba"
 * Output: true
 *
 * Input: s = "abca"
 * Output: true
 * Explanation: You could delete the character 'c'.
 *
 * Input: s = "abc"
 * Output: false
 * Date : Oct 20, 2021
*/
bool validPalindrome(char* s) {
  int i = 0;
  int j = strlen(s)-1;
    while(i < j) {
      debug ("i=%d j=%d", i, j);
        if(s[i] != s[j]) {
            return _isPalindrome(s, i+1, j) || _isPalindrome(s, i, j-1);
        }
        i++;
	j--;
    }
    return 1;
}

/**
   LeetCode Solution : 0ms
*/
bool isPalindrome(char* s) {
  if(s == NULL || !strcmp(s,""))
    return true;
  char *p = s + (strlen(s) -1);

  while(p>s) {
    printf ("\n AR--> s=%p d=%p \t", p, s);
    printf ("\n AR--> s=%c d=%c *p=%d *s=%d \n", *p, *s, isalnum(*p), isalnum(*s));
    if(isalnum(*s) && isalnum(*p) && tolower(*(s++)) != tolower(*(p--)))
      return false;
    else if(!isalnum(*s))
      s++;
    else if(!isalnum(*p))
      p--;
  }
  return true;
}

int isStringPalindrome2 (char str[]) {
  int l = 0;
  int h = strlen(str) -1;
  while (h>l) {
    if (str[h] != str[l]) {
      return -1;
    }
    h--; l++;
  }
  return 1;
}

int isStringPalindrome (char str[]) {
  char *ptr1 = str;
  char *ptr2 = str + strlen(str) -1;

  if (strlen(str) ==1 || strlen(str) == 0)
    return 1;

  while (*ptr2 > *ptr1) {
    if (!isalpha(*ptr2))
      continue;
    if (!isalpha(*ptr1))
      continue;
    if (tolower(*ptr1) != tolower(*ptr2))
      return -1;
    ptr1++; ptr2--;
  }
  return 1;
}

int main () {
  char ar [] = "IT !I";
  debug ("[%d]", isStringPalindrome(ar));
  char *str = "race a car";
  debug ("isPalindrome = [%d]", isPalindrome(str));

  debug ("validPalindrom = [%d]", validPalindrome(str));
}

/**
   Complexity Analysis

   Time complexity : O(n), in length nnn of the string. We traverse over each
   character at-most once, until the two pointers meet in the middle,
   or when we break and return early.

   Space complexity : O(1). No extra space required, at all.
**/

/**
   => ./a.out
   [main] L=127 :[1]

   AR--> s=0x400cea d=0x400ce1
   AR--> s=r d=r *p=8 *s=8

   AR--> s=0x400ce9 d=0x400ce2
   AR--> s=a d=a *p=8 *s=8

   AR--> s=0x400ce8 d=0x400ce3
   AR--> s=c d=c *p=8 *s=8

   AR--> s=0x400ce6 d=0x400ce4
   AR--> s=a d=e *p=8 *s=8
   [main] L=129 :isPalindrome = [0]
   [validPalindrome] L=63 :i=0 j=9
   [validPalindrome] L=63 :i=1 j=8
   [validPalindrome] L=63 :i=2 j=7
   [validPalindrome] L=63 :i=3 j=6
   [_isPalindrome] L=32 :i=4 j=6
   [main] L=131 :validPalindrom = [1]
**/
