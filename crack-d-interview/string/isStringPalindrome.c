#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
  
  while (*ptr2>*ptr1) {
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
}
