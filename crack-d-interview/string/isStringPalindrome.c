#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/***
    LeetCode : https://leetcode.com/problems/valid-palindrome/
    isalphanum() : Function returns a non-zero integer if an argument (character)
    passed to the function is an alphanumeric (alphabet and number) character.
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
  printf ("--> [%d] \n", isStringPalindrome(ar));
  char *str = "race a car";
  printf ("--> [%d] \n", isPalindrome(str));
}
