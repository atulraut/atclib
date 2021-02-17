/***
    https://leetcode.com/problems/longest-palindromic-substring/
    Longest Palindromic Substring
    Given a string s, return the longest palindromic substring in s.

    Example 1:
    Input: s = "babad"
    Output: "bab"
    Note: "aba" is also a valid answer.

    Example 2:
    Input: s = "cbbd"
    Output: "bb"

    Example 3:
    Input: s = "a"
    Output: "a"

    Example 4:
    Input: s = "ac"
    Output: "a"

    Constraints:
    1 <= s.length <= 1000
    s consist of only digits and English letters (lower-case and/or upper-case),
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/***
    LeetCode Accepted : 4ms
 */
char * longestPalindrome(char * s) {
  char *start, *end;
  char *p = s, *subStart = s;
  int maxLen = 1;
  while(*p){
    start = p; end = p;

    while(*(end+1) && *(end+1) == *end) {
      end++; // skip duplicates
    }
    p = end + 1;

    while(*(end + 1) && (start > s) && *(end + 1) == *(start - 1)){
      start--;
      end++;
    }
    if(end - start + 1 > maxLen){
      maxLen = end - start + 1;
      subStart = start;
    }
  }
  char *rst = (char *) calloc(maxLen + 1, sizeof(char));
  strncpy(rst, subStart, maxLen);
  return rst;
}

int str_long_palindrome (char *str) {
  int strL = 0;
  int i,j,strOne, strTwo, lim, result, flag;
  j = 0;
  char *newStr = NULL;
  char *newStrNext = NULL;
  lim = strlen(str);
  for (strOne=0; strOne<lim; strOne++) {
    for(strTwo=strOne+1; strTwo<=lim; strTwo++) {
      strL = (strTwo-strOne); // used to allocate memory
      newStr = (char*)malloc(sizeof(strL));
      j=0;
      for(i=strOne; i<=strTwo; i++) {
newStr[j++] = str[i];
      } // 3rd for end
      newStr[j] = '\0';
      j = 0; i=0;
      printf ("newStr= %s, strOne=%d, strTwo=%d, strL=%d\n", newStr,strOne,strTwo,strL);
      strL = strlen(newStr);
      result = str_word_palindrome(newStr);
      if (result == 0) {
 if (NULL == newStr || NULL == newStrNext) {
    newStrNext = (char*)malloc(sizeof(strL));
    strncpy(newStrNext, newStr, strL); // dest,src,num
  } else {
		  //printf ("old strlen(newStrNext)= %d\n", strlen(newStrNext));
	 }
	 if (strlen(newStrNext) < strlen(newStr)) {
            newStrNext = (char*)malloc(strlen(newStr));
	      strncpy(newStrNext, newStr, strL); // dest,src,num
	 } else { // free memory
		 if (newStr) {
			 free(newStr);
			 newStr = NULL;
		 }
	 }
	 strL = 0;
      }
    } // 2nd for end
  } // 1st for end
  printf ("\nFinal : newStrNext = %s\n\n", newStrNext);
  if(newStrNext)
    return 0;
  else
    return 1;
}

/*<Routine to check word is palindrome or not>*/
int str_word_palindrome (char *str) {
  char arr[50];
  int len, i, j;
  j = 0;
  len = strlen (str);
  for(i=len-1; i>=0; i--) {
     arr[j] = str[i];
     j++;
  }
  arr[j] = '\0';
  i = strcmp (str, arr);
  return i;
}

int main () {
  int ret = 0;
  char *fstr = NULL;
  char *nstr = "ASARMANAMRAUT"; //rotavatorR"; 9
  ret = str_word_palindrome (nstr);
  if (ret == 0)
    printf ("String is Palindrome !\n");
  else
    printf ("String is NOT Palindrome\n");
  ret = str_long_palindrome (nstr);
  if (ret == 0)
      printf ("String is Palindrome !\n");
    else
      printf ("String is NOT Palindrome\n");
}

/**
   Time complexity : O(n2). Since expanding a palindrome around its
   center could take O(n) time, the overall complexity is O(n2)O(n^2)O(n2).

   Space complexity : O(1).
**/
