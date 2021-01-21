/***
    Ref : https://leetcode.com/problems/longest-palindromic-substring/
    Longest Palindromic Substring in C using Manacher's Algorithm :
    https://gist.github.com/koww/be85e893c804f1a7ccd8
*/
#include <stdio.h>
#include "../../at_lib.h"

char* longestPalindrome(char* s) {
  char *start, *end;
  char *p = s, *subStart = s;
  int maxLen = 1;
  while(*p) {
    start = p; end = p;

    while(*(end+1) && *(end+1) == *end) {
      end++; // skip duplicates
    }
    p = end + 1;

    debug ("p=%s start=%p start=%s p=%p", p, start, start, s);

    while(*(end + 1) && (start > s) && *(end + 1) == *(start - 1)){
      printf ("[%s] end+1=%c, start=%s, s=%s *start-1=%c \n",__func__, *(end + 1), start, s, *(start - 1));
      start--;
      end++;
    }
    if(end - start + 1 > maxLen) {
      maxLen = end - start + 1;
      subStart = start;
    }
  }
  char *rst = (char *) calloc(maxLen + 1, sizeof(char));
  strncpy(rst, subStart, maxLen);
  return rst;
}

int main () {
  char str[] = "babad";

  debug("%s", longestPalindrome(str));

  return 0;
}

/***
=> ./a.out
[longestPalindrome] L=21 :p=abad start=0x7ffd24b40a60 start=babad p=0x7ffd24b40a60
[longestPalindrome] L=21 :p=bad start=0x7ffd24b40a61 start=abad p=0x7ffd24b40a60
[longestPalindrome] end+1=b, start=abad, s=babad *start-1=b
[longestPalindrome] L=21 :p=ad start=0x7ffd24b40a62 start=bad p=0x7ffd24b40a60
[longestPalindrome] end+1=a, start=bad, s=babad *start-1=a
[longestPalindrome] L=21 :p=d start=0x7ffd24b40a63 start=ad p=0x7ffd24b40a60
[longestPalindrome] L=21 :p= start=0x7ffd24b40a64 start=d p=0x7ffd24b40a60
[main] L=41 :bab
*/
