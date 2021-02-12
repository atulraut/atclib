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

/**
   LeetCode Solution : 0ms
*/
bool isPalindrome(char * s){
  if(s==NULL || !strcmp(s,""))
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
  debug ("[%d]", isPalindrome(str));
}

/***
    => ./a.out
    [isStringPalindrome.c] [main()] L=63 :[1]

    AR--> s=0x400b76 d=0x400b6d
    AR--> s=r d=r *p=8 *s=8

    AR--> s=0x400b75 d=0x400b6e
    AR--> s=a d=a *p=8 *s=8

    AR--> s=0x400b74 d=0x400b6f
    AR--> s=c d=c *p=8 *s=8

    AR--> s=0x400b72 d=0x400b70
    AR--> s=a d=e *p=8 *s=8
    [isStringPalindrome.c] [main()] L=65 :[0]
*/

/**
   Complexity Analysis

   Time complexity : O(n), in length nnn of the string. We traverse over each
   character at-most once, until the two pointers meet in the middle,
   or when we break and return early.

   Space complexity : O(1). No extra space required, at all.
**/

